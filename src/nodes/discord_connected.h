#ifndef DISCORD_CONNECTED_H
#define DISCORD_CONNECTED_H

#include "discord_social_sdk.h"
#include "discord_connector.h"

using namespace godot;

class DiscordConnected : public DiscordSocialSDK
{
    GDCLASS(DiscordConnected, DiscordSocialSDK);

protected:
    static void _bind_methods();

private:
    NodePath root_connector; // Change to NodePath object

public:
    DiscordConnector *connector;

    NodePath get_root_connector(); // Adjust return type
    void set_root_connector(NodePath value); // Adjust parameter type

    DiscordConnected();
    ~DiscordConnected();

    void _enter_tree() override;
};

#endif