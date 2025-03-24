#ifndef DISCORDGODOT_H
#define DISCORDGODOT_H

#include "definitions.h"
#include "discordpp.h"
#include <stdio.h>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class DiscordUtil : public Object
{
    GDCLASS(DiscordUtil, Object);

    static DiscordUtil *singleton;

protected:
    static void _bind_methods();

public:
    static DiscordUtil *
    get_singleton();

    DiscordUtil();
    ~DiscordUtil();

    Dictionary relationship2dict(discordpp::RelationshipHandle relationship);
    Dictionary user2dict(discordpp::UserHandle user);

    void debug();
    void run_callbacks();
};

#endif