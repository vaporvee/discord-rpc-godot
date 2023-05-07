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
    if (value == 0)
        app_id = NULL;
    else
        app_id = value;
    std::string s = std::to_string(app_id);
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
    if (value == "")
        app_id = NULL;
    else
        state = value;
    discordPresence.state = state.utf8().get_data();
}
String discord_rpc::get_state() const
{
    return state;
}
void discord_rpc::set_details(const String &value)
{
    if (value == "")
        app_id = NULL;
    else
        details = value;
    discordPresence.details = details.utf8().get_data();
}
String discord_rpc::get_details() const
{
    return details;
}

void discord_rpc::set_large_image(const String &value)
{
    if (value == "")
        app_id = NULL;
    else
        large_image = value;
    discordPresence.largeImageKey = large_image.utf8().get_data();
}
String discord_rpc::get_large_image() const
{
    return large_image;
}
void discord_rpc::set_large_image_text(const String &value)
{
    if (value == "")
        app_id = NULL;
    else
        large_image_text = value;
    discordPresence.largeImageText = large_image_text.utf8().get_data();
}
String discord_rpc::get_large_image_text() const
{
    return large_image_text;
}
void discord_rpc::set_small_image(const String &value)
{
    if (value == "")
        app_id = NULL;
    else
        small_image = value;
    discordPresence.smallImageKey = small_image.utf8().get_data();
}
String discord_rpc::get_small_image() const
{
    return small_image;
}
void discord_rpc::set_small_image_text(const String &value)
{
    if (value == "")
        app_id = NULL;
    else
        small_image_text = value;
    discordPresence.smallImageText = small_image_text.utf8().get_data();
}
String discord_rpc::get_small_image_text() const
{
    return small_image_text;
}

void discord_rpc::set_start_timestamp(const int64_t &value)
{
    if (value == 0)
        app_id = NULL;
    else
        start_timestamp = value;
    discordPresence.startTimestamp = start_timestamp;
}
int64_t discord_rpc::get_start_timestamp() const
{
    return start_timestamp;
}
void discord_rpc::set_end_timestamp(const int64_t &value)
{
    if (value == 0)
        app_id = NULL;
    else
        end_timestamp = value;
    discordPresence.endTimestamp = end_timestamp;
}
int64_t discord_rpc::get_end_timestamp() const
{
    return end_timestamp;
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
    set_app_id(NULL);
    set_state("");
    set_details("");
    set_large_image("");
    set_large_image_text("");
    set_small_image("");
    set_small_image_text("");
    set_start_timestamp(NULL);
    set_end_timestamp(NULL);
    Discord_ClearPresence();
}

void discord_rpc::clear_invite_system()
{
}

void discord_rpc::clear_buttons()
{
}