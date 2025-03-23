#include "discord_connector.h"

DiscordConnector *DiscordConnector::singleton = nullptr;

void DiscordConnector::_bind_methods()
{
    BIND_SET_GET(DiscordConnector, app_id, Variant::STRING, godot::PROPERTY_HINT_RANGE, "-99999,99999,or_less,or_greater,hide_slider");
    BIND_SET_GET(DiscordConnector, auto_connect, Variant::BOOL);
    BIND_SET_GET(DiscordConnector, token_auto_manage, Variant::BOOL);
    BIND_METHOD(DiscordConnector, connect);
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
    if (!Engine::get_singleton()->is_editor_hint() && !editor_process)
    {
        if (auto_connect)
            connect();
    }
}

void DiscordConnector::_process(double delta)
{
    if (!Engine::get_singleton()->is_editor_hint() && !editor_process)
    {
        discordpp::RunCallbacks();
    }
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

void DiscordConnector::set_auto_connect(bool value)
{
    auto_connect = value;
}

bool DiscordConnector::get_auto_connect()
{
    return auto_connect;
}

void DiscordConnector::connect()
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
          std::string accessToken, // needs to be stored securely
          std::string refreshToken, // needs to be stored securely
          discordpp::AuthorizationTokenType tokenType,
          int32_t expiresIn,
          std::string scope) {
            client->UpdateToken(discordpp::AuthorizationTokenType::Bearer, accessToken, [this](discordpp::ClientResult result) {
                if(result.Successful()) {
                    client->Connect();
                    UtilityFunctions::print("TODO: connection success signal");
                } else {
                  UtilityFunctions::push_error("Token update error: " + String(result.Error().c_str()));
                }
              });
        });
      } });
}