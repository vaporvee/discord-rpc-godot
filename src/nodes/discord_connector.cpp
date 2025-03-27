#include "discord_connector.h"

void DiscordConnector::_bind_methods()
{
    BIND_SET_GET(DiscordConnector, app_id, Variant::STRING, godot::PROPERTY_HINT_RANGE, "-99999,99999,or_less,or_greater,hide_slider");
    ADD_GROUP("Automatic", "auto_");
    BIND_SET_GET(DiscordConnector, auto_connect, Variant::BOOL);
    BIND_SET_GET(DiscordConnector, auto_token_manage, Variant::BOOL);
    BIND_SET_GET(DiscordConnector, auto_encryption_key, Variant::STRING, godot::PROPERTY_HINT_NONE, "", godot::PROPERTY_USAGE_NO_EDITOR);
    BIND_METHOD(DiscordConnector, auth);
    BIND_METHOD(DiscordConnector, token_connect, "access_token");
    BIND_METHOD(DiscordConnector, token_refresh, "current_refresh_token");
    BIND_SIGNAL(authenticated, PropertyInfo(Variant::STRING, "access_token"), PropertyInfo(Variant::STRING, "refresh_token"), PropertyInfo(Variant::INT, "expires_in"));
    BIND_SIGNAL(authentication_failed, PropertyInfo(Variant::STRING, "error"));
    BIND_SIGNAL(connection_ready);
    BIND_SIGNAL(connection_error, PropertyInfo(Variant::STRING, "error"));
    BIND_SIGNAL(token_refreshed, PropertyInfo(Variant::STRING, "access_token"), PropertyInfo(Variant::STRING, "refresh_token"), PropertyInfo(Variant::INT, "expires_in"));
    BIND_SIGNAL(token_refresh_failed, PropertyInfo(Variant::STRING, "error"));
}

DiscordConnector::DiscordConnector()
{
}
DiscordConnector::~DiscordConnector()
{
}

void DiscordConnector::_ready()
{

    if (Engine::get_singleton()->is_editor_hint() || editor_process)
        return;

    client = std::make_shared<discordpp::Client>();

    client->SetStatusChangedCallback([this](discordpp::Client::Status status, discordpp::Client::Error error, int32_t errorDetail)
                                     {
        if (status == discordpp::Client::Status::Ready)
        {
            emit_signal("connection_ready");
        }
        if (error != discordpp::Client::Error::None)
        {
            emit_signal("connection_error", String(discordpp::Client::ErrorToString(error).c_str()));
        } });

    if (auto_connect)
    {
        auth();
    }
}

void DiscordConnector::_process(double delta)
{
    if (!Engine::get_singleton()->is_editor_hint() && !editor_process && client)
    {
        discordpp::RunCallbacks();
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

void DiscordConnector::set_auto_token_manage(bool value)
{
    auto_token_manage = value;
}

bool DiscordConnector::get_auto_token_manage()
{
    return auto_token_manage;
}

void DiscordConnector::set_auto_encryption_key(String value)
{
    auto_encryption_key = value;
}

String DiscordConnector::get_auto_encryption_key()
{
    return auto_encryption_key;
}

void DiscordConnector::auth()
{
    if (auto_token_manage)
    {
        if (auto_encryption_key.is_empty())
        {
            auto_encryption_key = DiscordUtil::get_singleton()->generate_auto_encryption_key();
        }
        Ref<godot::ConfigFile> config = DiscordUtil::get_singleton()->get_tokens(auto_encryption_key);
        if (config->has_section_key("tokens", "access_token") &&
            config->has_section_key("tokens", "refresh_token") &&
            config->has_section_key("tokens", "expires_in"))
        {
            access_token = config->get_value("tokens", "access_token");
            refresh_token = config->get_value("tokens", "refresh_token");
            expires_in = config->get_value("tokens", "expires_in");
            token_connect(access_token);
            return;
        }
        else
        {
            DiscordUtil::get_singleton()->delete_tokens();
        }
    }

    auto codeVerifier = client->CreateAuthorizationCodeVerifier();

    discordpp::AuthorizationArgs args{};
    args.SetClientId(app_id);
    args.SetScopes(discordpp::Client::GetDefaultPresenceScopes());
    
    args.SetCodeChallenge(codeVerifier.Challenge());

    // Begin authentication process // TODO: option to open browser
    client->Authorize(args, [this, codeVerifier](auto result, auto code, auto redirectUri)
                      {
      if (!result.Successful()) {
        emit_signal("authentication_failed", result.Error().c_str());
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
            if (auto_token_manage)
            {
                DiscordUtil::get_singleton()->save_tokens(accessToken.c_str(), refreshToken.c_str(), expiresIn, auto_encryption_key);
            }
        } else {
            emit_signal("authenticated", result.Error().c_str());
            return;
          }
            token_connect(accessToken.c_str());
        });
      } });
}

void DiscordConnector::token_connect(String access_token)
{
    client->UpdateToken(discordpp::AuthorizationTokenType::Bearer, access_token.utf8().get_data(), [this](discordpp::ClientResult result)
                        {
        if(result.Successful()) {
            client->Connect();
        } else {
          emit_signal("connection_error", result.Error().c_str());
        } });
}

void DiscordConnector::token_refresh(String current_refresh_token)
{
    client->RefreshToken(std::stoull(refresh_token.utf8().get_data()), refresh_token.utf8().get_data(), [this, current_refresh_token](discordpp::ClientResult result, std::string accessToken, std::string refreshToken, discordpp::AuthorizationTokenType tokenType, int32_t expiresIn, std::string scopes)
                         {
        if (result.Successful())
        {
            emit_signal("token_refreshed", accessToken.c_str(), refreshToken.c_str(), expiresIn);
            if (auto_token_manage)
            {
                DiscordUtil::get_singleton()->save_tokens(accessToken.c_str(), refreshToken.c_str(), expiresIn, auto_encryption_key);
                token_connect(accessToken.c_str());
            }
        }
        else
        {
            emit_signal("token_refresh_failed", result.Error().c_str());
        } });
}