#ifndef DISCORDGODOT_H
#define DISCORDGODOT_H

#include <stdio.h>
#include "lib/discord_game_sdk/cpp/discord.h"
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

#define H_SET_GET(variable_type, property_name) \
    variable_type property_name;                \
    variable_type get_##property_name();        \
    void set_##property_name(variable_type value);

using namespace godot;

class DiscordSDK : public Object
{
    GDCLASS(DiscordSDK, Object);

    static DiscordSDK *singleton;

protected:
    static void _bind_methods();

public:
    static DiscordSDK *
    get_singleton();

    DiscordSDK();
    ~DiscordSDK();

    // INTERBNAL
    int64_t old_app_id;
    Dictionary relationship2dict(discord::Relationship relationship);
    Dictionary user2dict(discord::User user);
    ///
    H_SET_GET(int64_t, app_id)
    H_SET_GET(String, state)
    H_SET_GET(String, details)
    H_SET_GET(String, large_image)
    H_SET_GET(String, large_image_text)
    H_SET_GET(String, small_image)
    H_SET_GET(String, small_image_text)
    H_SET_GET(int64_t, start_timestamp)
    H_SET_GET(int64_t, end_timestamp)
    H_SET_GET(String, party_id)
    H_SET_GET(int32_t, current_party_size)
    H_SET_GET(int32_t, max_party_size)
    H_SET_GET(String, match_secret)
    H_SET_GET(String, join_secret)
    H_SET_GET(String, spectate_secret)
    H_SET_GET(bool, is_public_party)
    H_SET_GET(bool, instanced)
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
    void accept_join_request(int64_t user_id);
    void send_invite(int64_t user_id, bool is_spectate, String message_content);
    void accept_invite(int64_t user_id);
    void register_command(String value);
    void register_steam(int32_t value);
    Dictionary get_current_user();
    Dictionary get_relationship(int64_t user_id);
    Array get_all_relationships();
    bool get_is_discord_working();
    int get_result_int();
};

#endif