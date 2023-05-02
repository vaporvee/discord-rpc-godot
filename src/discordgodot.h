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

    String state;
    String details;

    String large_image;
    String large_image_text;
    String small_image;
    String small_image_text;

    int64_t start_timestamp;
    int64_t end_timestamp;

public:
    static Discord_SDK *get_singleton();

    Discord_SDK();
    ~Discord_SDK();

    void debug();
    void coreupdate();
    void refresh();

    int64_t get_app_id() const;

    void set_app_id(const int64_t &value);
    String get_state() const;
    void set_state(const String &value);
    String get_details() const;
    void set_details(const String &value);

    String get_large_image() const;
    void set_large_image(const String &value);
    String get_large_image_text() const;
    void set_large_image_text(const String &value);
    String get_small_image() const;
    void set_small_image(const String &value);
    String get_small_image_text() const;
    void set_small_image_text(const String &value);

    int64_t get_start_timestamp() const;
    void set_start_timestamp(const int64_t &value);
    int64_t get_end_timestamp() const;
    void set_end_timestamp(const int64_t &value);

    bool get_is_discord_working() const;
    int get_result_int() const;
};

#endif