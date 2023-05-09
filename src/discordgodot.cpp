#include <string>
#include "discordgodot.h"
#include "lib/discord-rpc/include/discord_rpc.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/time.hpp>

using namespace godot;

discord_rpc *discord_rpc::singleton = nullptr;

DiscordEventHandlers handlers;
DiscordRichPresence discordPresence;

void discord_rpc::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("debug"), &discord_rpc::debug);

    ClassDB::bind_method(D_METHOD("get_app_id"), &discord_rpc::get_app_id);
    ClassDB::bind_method(D_METHOD("set_app_id", "app_id"), &discord_rpc::set_app_id);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "app_id"), "set_app_id", "get_app_id");
    ClassDB::bind_method(D_METHOD("get_state"), &discord_rpc::get_state);
    ClassDB::bind_method(D_METHOD("set_state", "state"), &discord_rpc::set_state);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "state"), "set_state", "get_state");
    ClassDB::bind_method(D_METHOD("get_details"), &discord_rpc::get_details);
    ClassDB::bind_method(D_METHOD("set_details", "details"), &discord_rpc::set_details);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "details"), "set_details", "get_details");

    ClassDB::bind_method(D_METHOD("get_large_image"), &discord_rpc::get_large_image);
    ClassDB::bind_method(D_METHOD("set_large_image", "large_image"), &discord_rpc::set_large_image);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "large_image"), "set_large_image", "get_large_image");
    ClassDB::bind_method(D_METHOD("get_large_image_text"), &discord_rpc::get_large_image_text);
    ClassDB::bind_method(D_METHOD("set_large_image_text", "large_image_text"), &discord_rpc::set_large_image_text);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "large_image_text"), "set_large_image_text", "get_large_image_text");
    ClassDB::bind_method(D_METHOD("get_small_image"), &discord_rpc::get_small_image);
    ClassDB::bind_method(D_METHOD("set_small_image", "small_image"), &discord_rpc::set_small_image);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "small_image"), "set_small_image", "get_small_image");
    ClassDB::bind_method(D_METHOD("get_small_image_text"), &discord_rpc::get_small_image_text);
    ClassDB::bind_method(D_METHOD("set_small_image_text", "large_small_text"), &discord_rpc::set_small_image_text);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "small_image_text"), "set_small_image_text", "get_small_image_text");

    ClassDB::bind_method(D_METHOD("get_start_timestamp"), &discord_rpc::get_start_timestamp);
    ClassDB::bind_method(D_METHOD("set_start_timestamp", "start_timestamp"), &discord_rpc::set_start_timestamp);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "start_timestamp"), "set_start_timestamp", "get_start_timestamp");
    ClassDB::bind_method(D_METHOD("get_end_timestamp"), &discord_rpc::get_end_timestamp);
    ClassDB::bind_method(D_METHOD("set_end_timestamp", "end_timestamp"), &discord_rpc::set_end_timestamp);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "end_timestamp"), "set_end_timestamp", "get_end_timestamp");

    ClassDB::bind_method(D_METHOD("get_first_button_text"), &discord_rpc::get_first_button_text);
    ClassDB::bind_method(D_METHOD("set_first_button_text", "first_button_text"), &discord_rpc::set_first_button_text);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "first_button_text"), "set_first_button_text", "get_first_button_text");
    ClassDB::bind_method(D_METHOD("get_first_button_url"), &discord_rpc::get_first_button_url);
    ClassDB::bind_method(D_METHOD("set_first_button_url", "first_button_url"), &discord_rpc::set_first_button_url);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "first_button_url"), "set_first_button_url", "get_first_button_url");
    ClassDB::bind_method(D_METHOD("get_second_button_text"), &discord_rpc::get_second_button_text);
    ClassDB::bind_method(D_METHOD("set_second_button_text", "second_button_text"), &discord_rpc::set_second_button_text);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "second_button_text"), "set_second_button_text", "get_second_button_text");
    ClassDB::bind_method(D_METHOD("get_second_button_url"), &discord_rpc::get_first_button_url);
    ClassDB::bind_method(D_METHOD("set_second_button_url", "second_button_url"), &discord_rpc::set_second_button_url);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "second_button_url"), "set_second_button_url", "get_second_button_url");

    ClassDB::bind_method(D_METHOD("refresh"), &discord_rpc::refresh);
}

discord_rpc *discord_rpc::get_singleton()
{
    return singleton;
}

discord_rpc::discord_rpc()
{
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
}

discord_rpc::~discord_rpc()
{
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

void discord_rpc::debug()
{
    Discord_Initialize("1099618430065324082", &handlers, 1, NULL);
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = "\"new\" discord rpc lib for godot";
    discordPresence.details = "Teeest";
    discordPresence.startTimestamp = 0;
    discordPresence.endTimestamp = time(0) + 5 * 60;
    discordPresence.largeImageKey = "example_game";
    discordPresence.smallImageKey = "fighting";
    discordPresence.smallImageText = "Fighting";
    discordPresence.largeImageText = "Try it now!";
    discordPresence.button1Label = NULL;
    discordPresence.button1Url = NULL;
    discordPresence.button2Label = NULL;
    discordPresence.button2Url = NULL;
    discordPresence.partyId = "party1234";
    discordPresence.partySize = 1;
    discordPresence.partyMax = 6;
    discordPresence.partyPrivacy = DISCORD_PARTY_PUBLIC;
    discordPresence.matchSecret = "xyzzy";
    discordPresence.joinSecret = "join";
    discordPresence.spectateSecret = "look";

    // WARNING: if button variables are filled clear invite variables and if invite variables are filled clear button variables or the rpc will not launch
    discordPresence.instance = 0;
    Discord_UpdatePresence(&discordPresence);
#ifdef DISCORD_DISABLE_IO_THREAD
    Discord_UpdateConnection();
#endif
    Discord_RunCallbacks();
}

void discord_rpc::set_app_id(const int64_t &value)
{
    app_id = value;
    if (value == 0)
        app_id = NULL;
    std::string s = std::to_string(value);
    char const *pchar = s.c_str();
    Discord_Initialize(pchar, &handlers, 1, NULL);
    memset(&discordPresence, 0, sizeof(discordPresence));
}
int64_t discord_rpc::get_app_id() const
{
    return app_id;
}

void discord_rpc::set_state(const String &value)
{
    state = value;
    if (value == "")
        discordPresence.state = NULL;
    else
        discordPresence.state = value.utf8().get_data();
}
String discord_rpc::get_state() const
{
    return state;
}
void discord_rpc::set_details(const String &value)
{
    details = value;
    if (value == "")
        discordPresence.details = NULL;
    else
        discordPresence.details = value.utf8().get_data();
}
String discord_rpc::get_details() const
{
    return details;
}

void discord_rpc::set_large_image(const String &value)
{
    large_image = value;
    if (value == "")
        discordPresence.largeImageKey = NULL;
    else
        discordPresence.largeImageKey = value.utf8().get_data();
}
String discord_rpc::get_large_image() const
{
    return large_image;
}
void discord_rpc::set_large_image_text(const String &value)
{
    large_image_text = value;
    if (value == "")
        discordPresence.largeImageText = NULL;
    else
        discordPresence.largeImageText = value.utf8().get_data();
}
String discord_rpc::get_large_image_text() const
{
    return large_image_text;
}
void discord_rpc::set_small_image(const String &value)
{
    small_image = value;
    if (value == "")
        discordPresence.smallImageKey = NULL;
    else
        discordPresence.smallImageKey = value.utf8().get_data();
}
String discord_rpc::get_small_image() const
{
    return small_image;
}
void discord_rpc::set_small_image_text(const String &value)
{
    small_image_text = value;
    if (value == "")
        discordPresence.smallImageText = NULL;
    else
        discordPresence.smallImageText = value.utf8().get_data();
}
String discord_rpc::get_small_image_text() const
{
    return small_image_text;
}

void discord_rpc::set_start_timestamp(const int64_t &value)
{
    start_timestamp = value;
    if (value == 0)
        discordPresence.startTimestamp = NULL;
    else
        discordPresence.startTimestamp = value;
}
int64_t discord_rpc::get_start_timestamp() const
{
    return start_timestamp;
}
void discord_rpc::set_end_timestamp(const int64_t &value)
{
    if (value == 0)
        discordPresence.endTimestamp = NULL;
    else
    {
        end_timestamp = value;
        discordPresence.endTimestamp = value;
    }
}
int64_t discord_rpc::get_end_timestamp() const
{
    return end_timestamp;
}

void discord_rpc::set_first_button_url(const String &value)
{
    first_button_url = value;
    clear_invite_system();
    if (value == "")
        discordPresence.button1Url = NULL;
    else
        discordPresence.button1Url = value.utf8().get_data();
}
String discord_rpc::get_first_button_url() const
{
    return first_button_url;
}
void discord_rpc::set_first_button_text(const String &value)
{
    first_button_text = value;
    clear_invite_system();
    if (value == "")
        discordPresence.button1Label = NULL;
    else
        discordPresence.button1Label = value.utf8().get_data();
}
String discord_rpc::get_first_button_text() const
{
    return first_button_text;
}
void discord_rpc::set_second_button_url(const String &value)
{
    second_button_url = value;
    clear_invite_system();
    if (value == "")
        discordPresence.button2Url = NULL;
    else
        discordPresence.button2Url = value.utf8().get_data();
}
String discord_rpc::get_second_button_url() const
{
    return second_button_url;
}
void discord_rpc::set_second_button_text(const String &value)
{
    second_button_text = value;
    clear_invite_system();
    if (value == "")
        discordPresence.button2Label = NULL;
    else
        discordPresence.button2Label = value.utf8().get_data();
}
String discord_rpc::get_second_button_text() const
{
    return second_button_text;
}

void discord_rpc::refresh()
{
    Discord_UpdatePresence(&discordPresence);
#ifdef DISCORD_DISABLE_IO_THREAD
    Discord_UpdateConnection();
#endif
    Discord_RunCallbacks();
}

void discord_rpc::clear()
{
    app_id = NULL;
    state = "";
    details = "";
    large_image = "";
    large_image_text = "";
    small_image = "";
    small_image_text = "";
    start_timestamp = NULL;
    end_timestamp = NULL;
    clear_buttons();
    clear_invite_system();
    Discord_ClearPresence();
}

void discord_rpc::clear_invite_system()
{
}

void discord_rpc::clear_buttons()
{
}