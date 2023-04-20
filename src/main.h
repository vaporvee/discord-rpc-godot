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

public:
    static DiscordSDK *get_singleton();

    DiscordSDK();
    ~DiscordSDK();

    void debug();
    void coreupdate();
    void refresh_activity();
    void set_app_id(int64_t appid);
    void set_state(String state);
    void set_details(String details);
};

#endif