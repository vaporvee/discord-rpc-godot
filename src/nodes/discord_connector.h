#ifndef DISCORD_CONNECTOR_H
#define DISCORD_CONNECTOR_H

#include "discord_social_sdk.h"
#include "../util.h"

using namespace godot;

class DiscordConnector : public DiscordSocialSDK
{
    GDCLASS(DiscordConnector, DiscordSocialSDK);

protected:
    static void _bind_methods();

public:
    bool editor_process = false;

    std::shared_ptr<discordpp::Client> client;

    H_SET_GET(app_id, 0)
    H_SET_GET(auto_encryption_key, "")
    H_SET_GET(auto_token_manage, true)
    H_SET_GET(auto_connect, false)

    String access_token;
    String refresh_token;
    int64_t expires_in;

    void auth();
    void token_connect(String access_token);
    void token_refresh(String refresh_token);

    void refresh_auto_encryption_key();

    DiscordConnector();
    ~DiscordConnector();
    void _ready() override;
    void _process(double delta) override;
};

#endif