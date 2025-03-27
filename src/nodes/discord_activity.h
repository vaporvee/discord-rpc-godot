#ifndef DISCORD_ACTIVITY_H
#define DISCORD_ACTIVITY_H

#include "discord_connected.h"
#include "../resources/rich_presence.h"

using namespace godot;

class DiscordActivity : public DiscordConnected
{
    GDCLASS(DiscordActivity, DiscordConnected);

protected:
    static void _bind_methods();

public:
    Ref<RichPresence> rich_presence;
    Ref<RichPresence> get_rich_presence();
    void set_rich_presence(Ref<RichPresence> value);

    void update_rich_presence();

    DiscordActivity();
    ~DiscordActivity();
};

#endif