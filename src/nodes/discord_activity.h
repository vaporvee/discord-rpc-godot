#ifndef DISCORD_ACTIVITY_SDK_H
#define DISCORD_ACTIVITY_SDK_H

#include "discord_activity.h"
#include "discord_social_sdk.h"
#include "discord_connector.h"

using namespace godot;

class DiscordActivity : public DiscordSocialSDK
{
    GDCLASS(DiscordActivity, DiscordSocialSDK);

    static DiscordActivity *singleton;

protected:
    static void _bind_methods();

private:
NodePath root_connector; // Change to NodePath object

public:
    static DiscordActivity *
    get_singleton();
    
    DiscordConnector *connector;

    NodePath get_root_connector(); // Adjust return type
    void set_root_connector(NodePath value); // Adjust parameter type

    DiscordActivity();
    ~DiscordActivity();

    void _enter_tree() override;
};

#endif