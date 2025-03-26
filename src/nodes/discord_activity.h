#ifndef DISCORD_ACTIVITY_H
#define DISCORD_ACTIVITY_H

#include "discord_connected.h"
#include "../resources/activity.h"

using namespace godot;

class DiscordActivity : public DiscordConnected
{
    GDCLASS(DiscordActivity, DiscordConnected);

protected:
    static void _bind_methods();

public:
    Ref<ActivityResource> activity;
    Ref<ActivityResource> get_activity();
    void set_activity(Ref<ActivityResource> value);

    DiscordActivity();
    ~DiscordActivity();
};

#endif