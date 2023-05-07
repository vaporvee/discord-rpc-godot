#include "discordgodot.h"
#include "lib/discord-rpc/include/discord_rpc.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/time.hpp>

using namespace godot;

Discord_SDK *Discord_SDK::singleton = nullptr;

DiscordRichPresence discordPresence;

void Discord_SDK::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("debug"), &Discord_SDK::debug);
    ClassDB::bind_method(D_METHOD("coreupdate"), &Discord_SDK::coreupdate);

    ClassDB::bind_method(D_METHOD("get_app_id"), &Discord_SDK::get_app_id);
    ClassDB::bind_method(D_METHOD("set_app_id", "app_id"), &Discord_SDK::set_app_id);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "app_id"), "set_app_id", "get_app_id");
    ClassDB::bind_method(D_METHOD("get_state"), &Discord_SDK::get_state);
    ClassDB::bind_method(D_METHOD("set_state", "state"), &Discord_SDK::set_state);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "state"), "set_state", "get_state");
    ClassDB::bind_method(D_METHOD("get_details"), &Discord_SDK::get_details);
    ClassDB::bind_method(D_METHOD("set_details", "details"), &Discord_SDK::set_details);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "details"), "set_details", "get_details");

    ClassDB::bind_method(D_METHOD("get_large_image"), &Discord_SDK::get_large_image);
    ClassDB::bind_method(D_METHOD("set_large_image", "large_image"), &Discord_SDK::set_large_image);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "large_image"), "set_large_image", "get_large_image");
    ClassDB::bind_method(D_METHOD("get_large_image_text"), &Discord_SDK::get_large_image_text);
    ClassDB::bind_method(D_METHOD("set_large_image_text", "large_image_text"), &Discord_SDK::set_large_image_text);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "large_image_text"), "set_large_image_text", "get_large_image_text");
    ClassDB::bind_method(D_METHOD("get_small_image"), &Discord_SDK::get_small_image);
    ClassDB::bind_method(D_METHOD("set_small_image", "small_image"), &Discord_SDK::set_small_image);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "small_image"), "set_small_image", "get_small_image");
    ClassDB::bind_method(D_METHOD("get_small_image_text"), &Discord_SDK::get_small_image_text);
    ClassDB::bind_method(D_METHOD("set_small_image_text", "large_small_text"), &Discord_SDK::set_small_image_text);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "small_image_text"), "set_small_image_text", "get_small_image_text");

    ClassDB::bind_method(D_METHOD("get_start_timestamp"), &Discord_SDK::get_start_timestamp);
    ClassDB::bind_method(D_METHOD("set_start_timestamp", "start_timestamp"), &Discord_SDK::set_start_timestamp);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "start_timestamp"), "set_start_timestamp", "get_start_timestamp");
    ClassDB::bind_method(D_METHOD("get_end_timestamp"), &Discord_SDK::get_end_timestamp);
    ClassDB::bind_method(D_METHOD("set_end_timestamp", "end_timestamp"), &Discord_SDK::set_end_timestamp);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "end_timestamp"), "set_end_timestamp", "get_end_timestamp");

    ClassDB::bind_method(D_METHOD("refresh"), &Discord_SDK::refresh);

    ClassDB::bind_method(D_METHOD("get_is_discord_working"), &Discord_SDK::get_is_discord_working);

    ClassDB::bind_method(D_METHOD("get_result_int"), &Discord_SDK::get_result_int);
}

Discord_SDK *Discord_SDK::get_singleton()
{
    return singleton;
}

Discord_SDK::Discord_SDK()
{
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
}

Discord_SDK::~Discord_SDK()
{
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

void Discord_SDK::coreupdate()
{
#ifdef DISCORD_DISABLE_IO_THREAD
    Discord_UpdateConnection();
#endif
    Discord_RunCallbacks();
}
void Discord_SDK::debug()
{
    DiscordEventHandlers handlers;
    Discord_Initialize("1099618430065324082", &handlers, 1, NULL);
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = "\"new\" discord rpc lib for godot";
    discordPresence.details = "Teeest";
    discordPresence.startTimestamp = 0;
    discordPresence.endTimestamp = time(0) + 5 * 60;
    discordPresence.largeImageKey = "example_game";
    discordPresence.smallImageKey = "fighting";
    discordPresence.partyId = "party1234";
    discordPresence.partySize = 1;
    discordPresence.partyMax = 6;
    discordPresence.partyPrivacy = DISCORD_PARTY_PUBLIC;
    discordPresence.matchSecret = "xyzzy";
    discordPresence.joinSecret = "join";
    discordPresence.spectateSecret = "look";
    discordPresence.instance = 0;
    Discord_UpdatePresence(&discordPresence);
}

void Discord_SDK::set_app_id(const int64_t &value)
{
    app_id = value;
}
int64_t Discord_SDK::get_app_id() const
{
    return app_id;
}

void Discord_SDK::set_state(const String &value)
{
    state = value;
}
String Discord_SDK::get_state() const
{
    return state;
}
void Discord_SDK::set_details(const String &value)
{
    details = value;
}
String Discord_SDK::get_details() const
{
    return details;
}

void Discord_SDK::refresh()
{
}

void Discord_SDK::set_large_image(const String &value)
{
    large_image = value;
}
String Discord_SDK::get_large_image() const
{
    return large_image;
}
void Discord_SDK::set_large_image_text(const String &value)
{
    large_image_text = value;
}
String Discord_SDK::get_large_image_text() const
{
    return large_image_text;
}
void Discord_SDK::set_small_image(const String &value)
{
    small_image = value;
}
String Discord_SDK::get_small_image() const
{
    return small_image;
}
void Discord_SDK::set_small_image_text(const String &value)
{
    small_image_text = value;
}
String Discord_SDK::get_small_image_text() const
{
    return small_image_text;
}

void Discord_SDK::set_start_timestamp(const int64_t &value)
{
    start_timestamp = value;
}
int64_t Discord_SDK::get_start_timestamp() const
{
    return 0;
}
void Discord_SDK::set_end_timestamp(const int64_t &value)
{
    end_timestamp = value;
}
int64_t Discord_SDK::get_end_timestamp() const
{
    return 0;
}

bool Discord_SDK::get_is_discord_working() const
{
    return 0;
}

int Discord_SDK::get_result_int() const
{
    return 0;
}
