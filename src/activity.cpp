#include "activity.h"
#include "./discord-game-sdk-cpp/discord.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

Discord_Activity *Discord_Activity::singleton = nullptr;

discord::Core *core{};
discord::Result result;
discord::Activity activity{};

void Discord_Activity::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("debug"), &Discord_Activity::debug);
    ClassDB::bind_method(D_METHOD("coreupdate"), &Discord_Activity::coreupdate);

    ClassDB::bind_method(D_METHOD("get_app_id"), &Discord_Activity::get_app_id);
    ClassDB::bind_method(D_METHOD("set_app_id", "app_id"), &Discord_Activity::set_app_id);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "app_id"), "set_app_id", "get_app_id");
    ClassDB::bind_method(D_METHOD("get_state"), &Discord_Activity::get_state);
    ClassDB::bind_method(D_METHOD("set_state", "state"), &Discord_Activity::set_state);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "state"), "set_state", "get_state");
    ClassDB::bind_method(D_METHOD("get_details"), &Discord_Activity::get_details);
    ClassDB::bind_method(D_METHOD("set_details", "details"), &Discord_Activity::set_details);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "details"), "set_details", "get_details");

    ClassDB::bind_method(D_METHOD("get_large_image"), &Discord_Activity::get_large_image);
    ClassDB::bind_method(D_METHOD("set_large_image", "large_image"), &Discord_Activity::set_large_image);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "large_image"), "set_large_image", "get_large_image");
    ClassDB::bind_method(D_METHOD("get_large_image_text"), &Discord_Activity::get_large_image_text);
    ClassDB::bind_method(D_METHOD("set_large_image_text", "large_image_text"), &Discord_Activity::set_large_image_text);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "large_image_text"), "set_large_image_text", "get_large_image_text");
    ClassDB::bind_method(D_METHOD("get_small_image"), &Discord_Activity::get_small_image);
    ClassDB::bind_method(D_METHOD("set_small_image", "small_image"), &Discord_Activity::set_small_image);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "small_image"), "set_small_image", "get_small_image");
    ClassDB::bind_method(D_METHOD("get_small_image_text"), &Discord_Activity::get_small_image_text);
    ClassDB::bind_method(D_METHOD("set_small_image_text", "large_small_text"), &Discord_Activity::set_small_image_text);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "small_image_text"), "set_small_image_text", "get_small_image_text");

    ClassDB::bind_method(D_METHOD("refresh"), &Discord_Activity::refresh);
}

Discord_Activity *Discord_Activity::get_singleton()
{
    return singleton;
}

Discord_Activity::Discord_Activity()
{
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
}

Discord_Activity::~Discord_Activity()
{
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

void Discord_Activity::debug()
{
    auto debugresult = discord::Core::Create(1080224638845591692, DiscordCreateFlags_NoRequireDiscord, &core);
    discord::Activity debugactivity{};
    debugactivity.SetState("Test from Godot!");
    debugactivity.SetDetails("I worked months on this");
    debugactivity.GetAssets().SetLargeImage("test1");
    debugactivity.GetAssets().SetLargeText("wow test text for large image");
    debugactivity.GetAssets().SetSmallImage("godot");
    debugactivity.GetAssets().SetSmallText("wow test text for small image");
    core->ActivityManager().UpdateActivity(debugactivity, [](discord::Result debugresult) {});
}

void Discord_Activity::coreupdate()
{
    ::core->RunCallbacks();
}

void Discord_Activity::set_app_id(const int64_t &value)
{
    app_id = value;
    result = discord::Core::Create(value, DiscordCreateFlags_NoRequireDiscord, &core);
}
int64_t Discord_Activity::get_app_id() const
{
    return app_id;
}

void Discord_Activity::set_state(const String &value)
{
    state = value;
    activity.SetState(value.utf8().get_data());
}
String Discord_Activity::get_state() const
{
    return state;
}
void Discord_Activity::set_details(const String &value)
{
    details = value;
    activity.SetDetails(value.utf8().get_data());
}
String Discord_Activity::get_details() const
{
    return details;
}

void Discord_Activity::refresh()
{
    core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
}

void Discord_Activity::set_large_image(const String &value)
{
    large_image = value;
    activity.GetAssets().SetLargeImage(value.utf8().get_data());
}
String Discord_Activity::get_large_image() const
{
    return large_image;
}
void Discord_Activity::set_large_image_text(const String &value)
{
    large_image_text = value;
    activity.GetAssets().SetLargeText(value.utf8().get_data());
}
String Discord_Activity::get_large_image_text() const
{
    return large_image_text;
}
void Discord_Activity::set_small_image(const String &value)
{
    small_image = value;
    activity.GetAssets().SetSmallImage(value.utf8().get_data());
}
String Discord_Activity::get_small_image() const
{
    return small_image;
}
void Discord_Activity::set_small_image_text(const String &value)
{
    small_image_text = value;
    activity.GetAssets().SetSmallText(value.utf8().get_data());
}
String Discord_Activity::get_small_image_text() const
{
    return small_image_text;
}