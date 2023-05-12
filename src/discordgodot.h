#ifndef DISCORDGODOT_H
#define DISCORDGODOT_H

#include <stdio.h>
#include "lib/discord_game_sdk/cpp/discord.h"
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class discord_sdk : public Object
{
    GDCLASS(discord_sdk, Object);

    static discord_sdk *singleton;

protected:
    static void _bind_methods();

private:
    Dictionary activity;

public:
    static discord_sdk *get_singleton();

    discord_sdk();
    ~discord_sdk();

    void debug();
    void coreupdate();
    void refresh();

    Dictionary get_activity();
    void set_activity(Dictionary value);

    bool get_is_discord_working();
    int get_result_int();
};

#endif