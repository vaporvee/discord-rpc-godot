#include "discord_connector.h"

DiscordConnector *DiscordConnector::singleton = nullptr;

void DiscordConnector::_bind_methods()
{
    BIND_SET_GET(DiscordConnector, auto_connect, Variant::BOOL);
    BIND_SET_GET(DiscordConnector, app_id, Variant::STRING, godot::PROPERTY_HINT_RANGE, "-99999,99999,or_less,or_greater,hide_slider");
    BIND_SET_GET(DiscordConnector, encryption_key, Variant::STRING, godot::PROPERTY_HINT_PASSWORD);
    BIND_SET_GET(DiscordConnector, token_auto_manage, Variant::BOOL);
    BIND_METHOD(DiscordConnector, connect_user);
    BIND_METHOD(DiscordConnector, update_user_token);
    BIND_METHOD(DiscordConnector, get_access_token);
    BIND_METHOD(DiscordConnector, get_refresh_token);
    BIND_METHOD(DiscordConnector, get_expires_in);
    BIND_SIGNAL(user_connected, PropertyInfo(Variant::STRING, "access_token"), PropertyInfo(Variant::STRING, "refresh_token"), PropertyInfo(Variant::INT, "expires_in"));
}
DiscordConnector::DiscordConnector()
{
    singleton = this;
}
DiscordConnector::~DiscordConnector()
{
    singleton = nullptr;
}
DiscordConnector *DiscordConnector::get_singleton()
{
    return singleton;
}

void DiscordConnector::_ready()
{
    client = std::make_shared<discordpp::Client>();
    if (encryption_key == "")
    {
        if (!Engine::get_singleton()->is_editor_hint() && !editor_process)
        {
            if (auto_connect)
                connect_user();
        }
    }
    else if (token_auto_manage)
    {
        ConfigFile config = DiscordUtil::get_singleton()->get_tokens(encryption_key);
        if (config.has_section_key("tokens", "access_token") && config.has_section_key("tokens", "refresh_token") && config.has_section_key("tokens", "expires_in"))
        {
            access_token = config.get_value("tokens", "access_token");
            refresh_token = config.get_value("tokens", "refresh_token");
            expires_in = config.get_value("tokens", "expires_in");
            update_user_token(access_token);
        }
        else
        {
            if (!Engine::get_singleton()->is_editor_hint() && !editor_process)
            {
                if (auto_connect)
                    connect_user();
            }
        }
    }
}

void DiscordConnector::_process(double delta)
{
    if (!Engine::get_singleton()->is_editor_hint() && !editor_process)
    {
        discordpp::RunCallbacks();
    }
    if (encryption_key == "")
    {
        DiscordUtil::get_singleton()->delete_tokens();
        encryption_key = DiscordUtil::get_singleton()->generate_encryption_key();
    }
}

void DiscordConnector::set_auto_connect(bool value)
{
    auto_connect = value;
}

bool DiscordConnector::get_auto_connect()
{
    return auto_connect;
}

void DiscordConnector::set_app_id(int64_t value)
{
    app_id = static_cast<int64_t>(value);
}

int64_t DiscordConnector::get_app_id()
{
    return static_cast<int64_t>(app_id);
}

void DiscordConnector::set_token_auto_manage(bool value)
{
    token_auto_manage = value;
}

bool DiscordConnector::get_token_auto_manage()
{
    return token_auto_manage;
}

void DiscordConnector::set_encryption_key(String value)
{
    encryption_key = value;
}

String DiscordConnector::get_encryption_key()
{
    return encryption_key;
}

void DiscordConnector::connect_user()
{
    auto codeVerifier = client->CreateAuthorizationCodeVerifier();

    discordpp::AuthorizationArgs args{};
    args.SetClientId(app_id);
    args.SetScopes(discordpp::Client::GetDefaultPresenceScopes());
    args.SetCodeChallenge(codeVerifier.Challenge());

    // Begin authentication process // TODO: option to open browser
    client->Authorize(args, [this, codeVerifier](auto result, auto code, auto redirectUri)
                      {
      if (!result.Successful()) {
        UtilityFunctions::push_error("Authentication Error: " + String(result.Error().c_str()));
        return;
      } else {
        client->GetToken(app_id, code, codeVerifier.Verifier(), redirectUri,
          [this](discordpp::ClientResult result,
          std::string accessToken,
          std::string refreshToken,
          discordpp::AuthorizationTokenType tokenType,
          int32_t expiresIn,
          std::string scope) {
            if (result.Successful()) {
            emit_signal("user_connected", accessToken.c_str(), refreshToken.c_str(), expiresIn);
            if (token_auto_manage)
            {
                DiscordUtil::get_singleton()->save_tokens(accessToken.c_str(), refreshToken.c_str(), expiresIn, encryption_key);
            }
            } else {
              UtilityFunctions::push_error("Access token error: " + String(result.Error().c_str()));
              return;
            }
            update_user_token(accessToken.c_str());
        });
      } });
}

void DiscordConnector::update_user_token(String access_token)
{
    client->UpdateToken(discordpp::AuthorizationTokenType::Bearer, access_token.utf8().get_data(), [this](discordpp::ClientResult result)
                        {
        if(result.Successful()) {
            client->Connect();
        } else {
          UtilityFunctions::push_error("Token update error: " + String(result.Error().c_str()));
        } });
}

String DiscordConnector::get_access_token()
{
    return access_token;
}

String DiscordConnector::get_refresh_token()
{
    return refresh_token;
}

int64_t DiscordConnector::get_expires_in()
{
    return expires_in;
}