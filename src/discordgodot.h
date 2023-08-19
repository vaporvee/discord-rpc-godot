#ifndef DISCORDGODOT_H
#define DISCORDGODOT_H

#include <stdio.h>
#include "lib/discord_game_sdk/cpp/discord.h"
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class discord_sdk : public RefCounted
{
    GDCLASS(discord_sdk, Object);

    static discord_sdk *singleton;

protected:
    static void _bind_methods();

public:
    static discord_sdk *
    get_singleton();

    discord_sdk();
    ~discord_sdk();

    // INTERBNAL
    int64_t old_app_id;
    Dictionary relationship2dict(discord::Relationship relationship);
    Dictionary user2dict(discord::User user);
    ///

    int64_t app_id = 0;

    String state;
    String details;

    String large_image;
    String large_image_text;
    String small_image;
    String small_image_text;

    int64_t start_timestamp;
    int64_t end_timestamp;

    String party_id;
    int32_t current_party_size;
    int32_t max_party_size;
    String match_secret;
    String join_secret;
    String spectate_secret;

    bool is_public_party;

    bool instanced;

    bool is_overlay_locked;

    void debug();
    void coreupdate();
    void refresh();
    void clear(bool reset_values);

    void unclear();
    int64_t get_app_id();
    void set_app_id(int64_t value);
    String get_state();
    void set_state(String value);
    String get_details();
    void set_details(String value);

    String get_large_image();
    void set_large_image(String value);
    String get_large_image_text();
    void set_large_image_text(String value);
    String get_small_image();
    void set_small_image(String value);
    String get_small_image_text();
    void set_small_image_text(String value);

    int64_t get_start_timestamp();
    void set_start_timestamp(int64_t value);
    int64_t get_end_timestamp();
    void set_end_timestamp(int64_t value);

    String get_party_id();
    void set_party_id(String value);

    int32_t get_current_party_size();
    void set_current_party_size(int32_t value);
    int32_t get_max_party_size();
    void set_max_party_size(int32_t value);
    String get_match_secret();
    void set_match_secret(String value);
    String get_join_secret();
    void set_join_secret(String value);
    String get_spectate_secret();
    void set_spectate_secret(String value);

    bool get_is_public_party();
    void set_is_public_party(bool value);

    bool get_instanced();
    void set_instanced(bool value);

    bool get_is_overlay_enabled();
    bool get_is_overlay_locked();
    void set_is_overlay_locked(bool value);
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