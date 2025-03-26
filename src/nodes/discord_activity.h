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
    TypedArray<ActivityResource> activities;
    TypedArray<ActivityResource> get_activities();
    void set_activities(TypedArray<ActivityResource> value);

    DiscordActivity();
    ~DiscordActivity();
};

#endif