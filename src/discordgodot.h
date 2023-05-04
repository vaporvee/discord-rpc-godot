#ifndef DISCORDGODOT_H
#define DISCORDGODOT_H

#include <stdio.h>
#include "discord-game-sdk-cpp/discord.h"
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class Discord_SDK : public Object
{
    GDCLASS(Discord_SDK, Object);

    static Discord_SDK *singleton;

protected:
    static void _bind_methods();

private:
    int64_t app_id;

    struct activitystruct
    {
        String state;
        String details;

        String large_image;
        String large_image_text;
        String small_image;
        String small_image_text;

        int64_t start_timestamp;
        int64_t end_timestamp;
    };
    activitystruct activity;

public:
    static Discord_SDK *
    get_singleton();

    Discord_SDK();
    ~Discord_SDK();

    void debug();
    void coreupdate();
    void refresh();

    int64_t get_app_id() const;
    void set_app_id(const int64_t &value);

    void set_activity(const activitystruct &value);
    activitystruct get_activity() const;

    bool get_is_discord_working() const;
    int get_result_int() const;
};

#endif