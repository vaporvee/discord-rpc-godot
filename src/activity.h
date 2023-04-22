#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <stdio.h>
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

public:
    static Discord_Activity *get_singleton();

    Discord_Activity();
    ~Discord_Activity();

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