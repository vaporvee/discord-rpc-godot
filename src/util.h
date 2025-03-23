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

    // INTERBNAL
    int64_t old_app_id;
    Dictionary relationship2dict(discordpp::RelationshipHandle relationship);
    Dictionary user2dict(discordpp::UserHandle user);
    ///
    void set_app_id(int64_t value);
    int64_t get_app_id();
    int64_t app_id = 0; // needs to be directly set to 0 or it will crash randomly
    H_SET_GET(is_overlay_locked, false)

    void debug();
    void run_callbacks();
    void refresh();
    void clear(bool reset_values);
    void unclear();
    bool get_is_overlay_enabled();
    void open_invite_overlay(bool is_spectate);
    void open_server_invite_overlay(String invite_code);
    void open_voice_settings();
    void accept_join_request(int64_t user_id);
    void send_invite(int64_t user_id, bool is_spectate, String message_content);
    void accept_invite(int64_t user_id);
    void register_command(String value);
    void register_steam(int32_t value);
    Dictionary get_current_user();
    Dictionary get_relationship(int64_t user_id);
    Array get_all_relationships();
    bool get_is_discord_working();
};

#endif