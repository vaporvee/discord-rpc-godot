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
    int app_id;
    String state;
    String details;

public:
    static DiscordSDK *get_singleton();

    DiscordSDK();
    ~DiscordSDK();

    int p_appid;
    String p_state;
    String p_details;

    void debug();
    void coreupdate();
    void refresh();
    int get_app_id();
    void set_app_id(int appid);
    String get_state();
    void set_state(String state);
    String get_details();
    void set_details(String details);
};

#endif