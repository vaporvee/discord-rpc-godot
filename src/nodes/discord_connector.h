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
    H_SET_GET(auto_encryption_key, "")
    H_SET_GET(auto_token_manage, false)
    H_SET_GET(auto_connect, false)

    String access_token;
    String refresh_token;
    int64_t expires_in;

    void connect_user();
    void update_user_token(String access_token);
    void refresh_user_token(String refresh_token);

    void refresh_auto_encryption_key();

    DiscordConnector();
    ~DiscordConnector();
    void _ready() override;
    void _process(double delta) override;
};

#endif