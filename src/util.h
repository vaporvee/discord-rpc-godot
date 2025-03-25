#ifndef DISCORDGODOT_H
#define DISCORDGODOT_H

#include "definitions.h"
#include "discordpp.h"
#include <stdio.h>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/config_file.hpp>
#include <godot_cpp/classes/file_access.hpp>

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

    void save_tokens(String access_token, String refresh_token, int64_t expires_in, String auto_encryption_key);
    String generate_auto_encryption_key();
    void delete_tokens();
    ConfigFile get_tokens(String auto_encryption_key);

    void debug();
    void run_callbacks();
};

#endif