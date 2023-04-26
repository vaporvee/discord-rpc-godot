#include "discordgodot.h"
#include "./discord-game-sdk-cpp/discord.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/time.hpp>

using namespace godot;

Discord_SDK *Discord_SDK::singleton = nullptr;

discord::Core *core{};
discord::Result result;
discord::Activity activity{};
discord::User user{};

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
    if (result == discord::Result::Ok)
    {
        ::core->RunCallbacks();
        core->UserManager().OnCurrentUserUpdate.Connect([]()
                                                        { core->UserManager().GetCurrentUser(&user); });
    }
}

void Discord_SDK::debug()
{
    result = discord::Core::Create(1080224638845591692, DiscordCreateFlags_NoRequireDiscord, &core);
    activity.SetState("Test from Godot!");
    activity.SetDetails("I worked months on this");
    activity.GetAssets().SetLargeImage("test1");
    activity.GetAssets().SetLargeText("wow test text for large image");
    activity.GetAssets().SetSmallImage("godot");
    activity.GetAssets().SetSmallText("wow test text for small image");
    activity.GetTimestamps().SetStart(1682242800);
    if (result == discord::Result::Ok)
    {
        core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
    }
    else
        UtilityFunctions::push_warning("Discord Activity couldn't be updated. It could be that Discord isn't running!");
}

void Discord_SDK::set_app_id(const int64_t &value)
{
    app_id = value;
    result = discord::Core::Create(value, DiscordCreateFlags_NoRequireDiscord, &core);
}
int64_t Discord_SDK::get_app_id() const
{
    return app_id;
}

void Discord_SDK::set_state(const String &value)
{
    state = value;
    activity.SetState(value.utf8().get_data());
}
String Discord_SDK::get_state() const
{
    return state;
}
void Discord_SDK::set_details(const String &value)
{
    details = value;
    activity.SetDetails(value.utf8().get_data());
}
String Discord_SDK::get_details() const
{
    return details;
}

void Discord_SDK::refresh()
{
    if (result == discord::Result::Ok)
        core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
    else
        UtilityFunctions::push_warning("Discord Activity couldn't be updated. It could be that Discord isn't running!");
}

void Discord_SDK::set_large_image(const String &value)
{
    large_image = value;
    activity.GetAssets().SetLargeImage(value.utf8().get_data());
}
String Discord_SDK::get_large_image() const
{
    return large_image;
}
void Discord_SDK::set_large_image_text(const String &value)
{
    large_image_text = value;
    activity.GetAssets().SetLargeText(value.utf8().get_data());
}
String Discord_SDK::get_large_image_text() const
{
    return large_image_text;
}
void Discord_SDK::set_small_image(const String &value)
{
    small_image = value;
    activity.GetAssets().SetSmallImage(value.utf8().get_data());
}
String Discord_SDK::get_small_image() const
{
    return small_image;
}
void Discord_SDK::set_small_image_text(const String &value)
{
    small_image_text = value;
    activity.GetAssets().SetSmallText(value.utf8().get_data());
}
String Discord_SDK::get_small_image_text() const
{
    return small_image_text;
}

void Discord_SDK::set_start_timestamp(const int64_t &value)
{
    start_timestamp = value;
    activity.GetTimestamps().SetStart(value);
}
int64_t Discord_SDK::get_start_timestamp() const
{
    return activity.GetTimestamps().GetStart();
}
void Discord_SDK::set_end_timestamp(const int64_t &value)
{
    end_timestamp = value;
    activity.GetTimestamps().SetEnd(value);
}
int64_t Discord_SDK::get_end_timestamp() const
{
    return activity.GetTimestamps().GetEnd();
}

bool Discord_SDK::get_is_discord_working() const
{
    return result == discord::Result::Ok;
}