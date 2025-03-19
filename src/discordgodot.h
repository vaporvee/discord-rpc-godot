#ifndef DISCORDGODOT_H
#define DISCORDGODOT_H

#include <stdio.h>
#include "discordpp.h"
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

#define H_SET_GET(variable_type, property_name) \
    variable_type property_name;                \
    variable_type get_##property_name();        \
    void set_##property_name(variable_type value);

using namespace godot;

class DiscordRPC : public Object
{
    GDCLASS(DiscordRPC, Object);

    static DiscordRPC *singleton;

protected:
    static void _bind_methods();

public:
    static DiscordRPC *
    get_singleton();

    DiscordRPC();
    ~DiscordRPC();

    // INTERBNAL
    uint64_t old_app_id;
    Dictionary relationship2dict(discordpp::RelationshipHandle relationship);
    Dictionary user2dict(discordpp::UserHandle user);
    ///
    void set_app_id(uint64_t value);
    uint64_t get_app_id();
    uint64_t app_id = 0; // needs to be directly set to 0 or it will crash randomly
    H_SET_GET(String, state)
    H_SET_GET(String, details)
    H_SET_GET(bool, is_overlay_locked)

    void debug();
    void run_callbacks();
    void refresh();
    void clear(bool reset_values);
    void unclear();
    bool get_is_overlay_enabled();
    void open_invite_overlay(bool is_spectate);
    void open_server_invite_overlay(String invite_code);
    void open_voice_settings();
    void accept_join_request(uint64_t user_id);
    void send_invite(uint64_t user_id, bool is_spectate, String message_content);
    void accept_invite(uint64_t user_id);
    void register_command(String value);
    void register_steam(int32_t value);
    Dictionary get_current_user();
    Dictionary get_relationship(uint64_t user_id);
    Array get_all_relationships();
    bool get_is_discord_working();
    int get_result_int();
};

#endif