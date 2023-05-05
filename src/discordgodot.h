#ifndef DISCORDGODOT_H
#define DISCORDGODOT_H

#include <stdio.h>
#include "lib/discord_game_sdk/cpp/discord.h"
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

discord::Core *core{};
discord::Result result;
discord::Activity sdkactivity{};
discord::User user{};

class Discord_SDK : public RefCounted
{
    GDCLASS(Discord_SDK, RefCounted);
    static Discord_SDK *singleton;

protected:
    static void _bind_methods();

private:
    int64_t app_id;

public:
    static Discord_SDK *
    get_singleton();

    Discord_SDK();
    ~Discord_SDK();

    class activitystruct : public Object
    {
        GDCLASS(activitystruct, Object);

    protected:
        static void _bind_methods();

    public:
        static activitystruct *
        get_singleton();

        activitystruct();
        ~activitystruct();

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

    void debug();
    void coreupdate();
    void refresh();

    int64_t get_app_id() const;
    void set_app_id(const int64_t &value);

    void set_activity(const Object &value);
    Object get_activity() const;

    bool get_is_discord_working() const;
    int get_result_int() const;
};

#endif