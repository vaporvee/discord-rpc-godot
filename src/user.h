#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class Discord_User : public Object
{
    GDCLASS(Discord_User, Object);

    static Discord_User *singleton;

protected:
    static void _bind_methods();

public:
    static Discord_User *get_singleton();

    Discord_User();
    ~Discord_User();

    String get_name() const;
};

#endif