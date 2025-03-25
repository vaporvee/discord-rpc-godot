#ifndef DISCORD_ACTIVITY_H
#define DISCORD_ACTIVITY_H

#include "discord_connected.h"

using namespace godot;

class DiscordActivity : public DiscordConnected
{
    GDCLASS(DiscordActivity, DiscordConnected);

    static DiscordActivity *singleton;

protected:
    static void _bind_methods();

public:
    static DiscordActivity *
    get_singleton();

    DiscordActivity();
    ~DiscordActivity();
};

#endif