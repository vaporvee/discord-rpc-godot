#ifndef DISCORD_CONNECTOR_H
#define DISCORD_CONNECTOR_H

#include "discord_social_sdk.h"
#include "../util.h"

using namespace godot;

class DiscordConnector : public DiscordSocialSDK
{
    GDCLASS(DiscordConnector, DiscordSocialSDK);

    static DiscordConnector *singleton;

protected:
    static void _bind_methods();

public:
    static DiscordConnector *
    get_singleton();

    bool editor_process = false;

    std::shared_ptr<discordpp::Client> client;

    H_SET_GET(app_id, 0)
    H_SET_GET(encryption_key, "")
    H_SET_GET(token_auto_manage, true)
    H_SET_GET(auto_connect, false)

    String access_token;
    String refresh_token;
    int64_t expires_in;
    String get_access_token();
    String get_refresh_token();
    int64_t get_expires_in();

    void connect_user();
    void update_user_token(String access_token);
    String refresh_user_token(String refresh_token);

    DiscordConnector();
    ~DiscordConnector();
    void _ready() override;
    void _process(double delta) override;
};

#endif