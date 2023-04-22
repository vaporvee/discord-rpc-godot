#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class DiscordSDK : public Object
{
    GDCLASS(DiscordSDK, Object);

    static DiscordSDK *singleton;

protected:
    static void _bind_methods();

private:
    int64_t app_id;
    String state;
    String details;

public:
    static DiscordSDK *get_singleton();

    DiscordSDK();
    ~DiscordSDK();

    void debug();
    void coreupdate();
    void refresh();

    int64_t get_app_id() const;
    void set_app_id(const int64_t &p_app_id);
    String get_state() const;
    void set_state(const String &p_state);
    String get_details() const;
    void set_details(const String &p_details);
};

#endif