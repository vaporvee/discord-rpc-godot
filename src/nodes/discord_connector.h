#ifndef DISCORD_CONNECTOR_H
#define DISCORD_CONNECTOR_H

#include "discord_social_sdk.h"

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
    H_SET_GET(token_auto_manage, true)
    H_SET_GET(auto_connect, false)

    DiscordConnector();
    ~DiscordConnector();
    void _ready() override;
    void _process(double delta) override;
};

#endif