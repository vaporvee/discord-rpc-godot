#ifndef DISCORDGODOT_H
#define DISCORDGODOT_H

#include <stdio.h>
#include "lib/discord_game_sdk/cpp/discord.h"
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class Discord_Activity : public Object
{
    GDCLASS(Discord_Activity, Object);

    static Discord_Activity *singleton;

protected:
    static void _bind_methods();

private:
    int64_t app_id;

    String state;
    String details;

    String large_image;
    String large_image_text;
    String small_image;
    String small_image_text;

    int64_t start_timestamp;
    int64_t end_timestamp;

public:
    static Discord_Activity *get_singleton();

    Discord_Activity();
    ~Discord_Activity();

    void debug();
    void coreupdate();
    void refresh();

    int64_t get_app_id();

    void set_app_id(int64_t value);
    String get_state();
    void set_state(String value);
    String get_details();
    void set_details(String value);

    String get_large_image();
    void set_large_image(String value);
    String get_large_image_text();
    void set_large_image_text(String value);
    String get_small_image();
    void set_small_image(String value);
    String get_small_image_text();
    void set_small_image_text(String value);

    int64_t get_start_timestamp();
    void set_start_timestamp(int64_t value);
    int64_t get_end_timestamp();
    void set_end_timestamp(int64_t value);

    bool get_is_discord_working();
    int get_result_int();
};

#endif