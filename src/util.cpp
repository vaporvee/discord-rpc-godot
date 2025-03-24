#include "util.h"

DiscordUtil *DiscordUtil::singleton = nullptr;

void DiscordUtil::_bind_methods()
{
    BIND_METHOD(DiscordUtil, debug);
    BIND_METHOD(DiscordUtil, run_callbacks);
    BIND_METHOD(DiscordUtil, save_tokens, "access_token", "refresh_token", "expires_in", "encryption_key");
    BIND_METHOD(DiscordUtil, generate_encryption_key);
}

DiscordUtil::DiscordUtil()
{
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
}

DiscordUtil::~DiscordUtil()
{
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

DiscordUtil *DiscordUtil::get_singleton()
{
    return singleton;
}

void DiscordUtil::run_callbacks()
{
    discordpp::RunCallbacks();
}
void DiscordUtil::debug()
{
    auto client = std::make_shared<discordpp::Client>();

    client->AddLogCallback([](auto message, auto severity)
                           { UtilityFunctions::print("[" + String(EnumToString(severity)) + "] " + message.c_str()); }, discordpp::LoggingSeverity::Info);

    client->SetStatusChangedCallback([client](discordpp::Client::Status status, discordpp::Client::Error error, int32_t errorDetail)
                                     {
        UtilityFunctions::print(String("Status changed: ") + discordpp::Client::StatusToString(status).c_str());
        if (status == discordpp::Client::Status::Ready) {
          UtilityFunctions::print("Client is ready!\n");
          UtilityFunctions::print("Friends Count: " + String::num_int64(client->GetRelationships().size()));
          discordpp::Activity activity;
          activity.SetType(discordpp::ActivityTypes::Playing);
          activity.SetState("Debug mode");
          activity.SetDetails("Godot -> Discord Social SDK");
          discordpp::ActivityAssets assets;
          assets.SetSmallImage("boss");
          assets.SetSmallText("Fighting the boss D:");
          assets.SetLargeImage("example_game");
          assets.SetLargeText("Example");
          activity.SetAssets(assets);

          // Update rich presence
          client->UpdateRichPresence(activity, [](discordpp::ClientResult result) {
          if(result.Successful()) {
              UtilityFunctions::print("Rich Presence updated successfully!");
          } else {
              UtilityFunctions::push_error("Rich Presence update failed");
          }
          });

          
        } else if (error != discordpp::Client::Error::None) {
          UtilityFunctions::push_error("Connection Error: " + String(discordpp::Client::ErrorToString(error).c_str()) + " - Details: " + String::num_int64(errorDetail));
        } });

    // Generate OAuth2 code verifier for authentication
    UtilityFunctions::print("Trying to authenticate...");
    UtilityFunctions::print("Generating code verifier...");
    auto codeVerifier = client->CreateAuthorizationCodeVerifier();

    // Set up authentication arguments
    discordpp::AuthorizationArgs args{};
    args.SetClientId(1099618430065324082);
    args.SetScopes(discordpp::Client::GetDefaultPresenceScopes());
    args.SetCodeChallenge(codeVerifier.Challenge());

    // Begin authentication process // TODO: option to open browser
    client->Authorize(args, [client, codeVerifier](auto result, auto code, auto redirectUri)
                      {
      if (!result.Successful()) {
        UtilityFunctions::push_error("Authentication Error: " + String(result.Error().c_str()));
        return;
      } else {
        UtilityFunctions::print("Authorization successful! Getting access token...");

        client->GetToken(1099618430065324082, code, codeVerifier.Verifier(), redirectUri,
          [client](discordpp::ClientResult result,
          std::string accessToken, // needs to be stored securely
          std::string refreshToken, // needs to be stored securely
          discordpp::AuthorizationTokenType tokenType,
          int32_t expiresIn,
          std::string scope) {
            UtilityFunctions::print("Access token received! Establishing connection...");
            client->UpdateToken(discordpp::AuthorizationTokenType::Bearer, accessToken, [client](discordpp::ClientResult result) {
                if(result.Successful()) {
                  UtilityFunctions::print("Token updated, connecting to Discord...");
                  client->Connect();
                } else {
                  UtilityFunctions::push_error("Token update error: " + String(result.Error().c_str()));
                }
              });
        });
      } });
}

Dictionary DiscordUtil::user2dict(discordpp::UserHandle user)
{
    Dictionary userdict;
    /*userdict["avatar"] = user.GetAvatar(); // can be empty when user has no avatar
    userdict["is_bot"] = user.GetBot();
    userdict["discriminator"] = user.GetDiscriminator();
    userdict["id"] = user.GetId();
    userdict["username"] = user.GetUsername();
    if (String(userdict["avatar"]).is_empty())
        userdict["avatar_url"] = String(std::string("https://cdn.discordapp.com/embed/avatars/" + std::to_string((userdict["discriminator"].INT % 5) - 1) + ".png").c_str());
    else
        userdict["avatar_url"] = String(std::string("https://cdn.discordapp.com/avatars/" + std::to_string(user.GetId()) + "/" + user.GetAvatar() + ".png").c_str());
    userdict.make_read_only();*/
    return userdict;
}

Dictionary DiscordUtil::relationship2dict(discordpp::RelationshipHandle relationship)
{
    Dictionary dict_relationship;
    Dictionary presence;
    Dictionary presence_activity;
    /*switch (static_cast<int>(relationship.GetPresence().GetStatus()))
    {
    case 0:
        presence["status"] = "Offline";
        break;
    case 1:
        presence["status"] = "Online";
        break;
    case 2:
        presence["status"] = "Idle";
        break;
    case 3:
        presence["status"] = "DoNotDisturb";
        break;
    default:
        presence["status"] = "NotAvailable";
        break;
    }
    presence_activity["application_id"] = relationship.GetPresence().GetActivity().GetApplicationId();
    presence_activity["name"] = relationship.GetPresence().GetActivity().GetName();
    presence_activity["state"] = relationship.GetPresence().GetActivity().GetState();
    presence_activity["details"] = relationship.GetPresence().GetActivity().GetDetails();
    presence_activity["large_image"] = relationship.GetPresence().GetActivity().GetAssets().GetLargeImage();
    presence_activity["large_text"] = relationship.GetPresence().GetActivity().GetAssets().GetLargeText();
    presence_activity["small_image"] = relationship.GetPresence().GetActivity().GetAssets().GetSmallImage();
    presence_activity["small_text"] = relationship.GetPresence().GetActivity().GetAssets().GetSmallText();
    presence_activity["timestamps_start"] = relationship.GetPresence().GetActivity().GetTimestamps().GetStart();
    presence_activity["timestamps_end"] = relationship.GetPresence().GetActivity().GetTimestamps().GetEnd();
    presence_activity["instance"] = relationship.GetPresence().GetActivity().GetInstance();
    presence_activity["party_id"] = relationship.GetPresence().GetActivity().GetParty().GetId();
    presence_activity["current_party_size"] = relationship.GetPresence().GetActivity().GetParty().GetSize().GetCurrentSize();
    presence_activity["max_party_size"] = relationship.GetPresence().GetActivity().GetParty().GetSize().GetMaxSize();
    presence_activity["join_secret"] = relationship.GetPresence().GetActivity().GetSecrets().GetJoin();
    presence_activity["spectate_secret"] = relationship.GetPresence().GetActivity().GetSecrets().GetSpectate();
    presence_activity["match_secret"] = relationship.GetPresence().GetActivity().GetSecrets().GetMatch();
    presence["activity"] = presence_activity;
    presence.make_read_only();
    switch (relationship.GetType())
    {
    case discordpp::RelationshipType::None:
        dict_relationship["type"] = "None";
        break;
    case discordpp::RelationshipType::Friend:
        dict_relationship["type"] = "Friend";
        break;
    case discordpp::RelationshipType::Blocked:
        dict_relationship["type"] = "Blocked";
        break;
    case discordpp::RelationshipType::PendingIncoming:
        dict_relationship["type"] = "PendingIncoming";
        break;
    case discordpp::RelationshipType::PendingOutgoing:
        dict_relationship["type"] = "PendingOutgoing";
        break;
    case discordpp::RelationshipType::Implicit:
        dict_relationship["type"] = "Implicit";
        break;
    default:
        dict_relationship["type"] = "NotAvailable";
        break;
    }
    dict_relationship["user"] = user2dict(relationship.GetUser());
    dict_relationship["presence"] = presence;
    dict_relationship.make_read_only();*/
    return dict_relationship;
}

String DiscordUtil::generate_encryption_key()
{
    const char *charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"$%&/()=?*+#-.,;:_'";
    String key;
    for (int i = 0; i < 50; i++)
    {
        key += charset[rand() % strlen(charset)];
    }
    return key;
}

void DiscordUtil::save_tokens(String access_token, String refresh_token, int64_t expires_in, String encryption_key)
{
    ConfigFile config;
    config.set_value("tokens", "access_token", access_token);
    config.set_value("tokens", "refresh_token", refresh_token);
    config.set_value("tokens", "expires_in", expires_in);
    config.save_encrypted_pass("user://discord_data.binary", encryption_key);
}

void DiscordUtil::delete_tokens()
{
    ConfigFile config;
    config.save("user://discord_data.binary");
}

ConfigFile DiscordUtil::get_tokens(String encryption_key)
{
    ConfigFile config;
    Error err = config.load_encrypted_pass("user://discord_data.binary", encryption_key);
    if (err != OK)
    {
        config.save("user://discord_data.binary");
        return ConfigFile();
    }
    return config;
}