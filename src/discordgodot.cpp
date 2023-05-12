#include "discordgodot.h"
#include "lib/discord_game_sdk/cpp/discord.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/time.hpp>

using namespace godot;

Discord_Activity *Discord_Activity::singleton = nullptr;

discord::Core *core{};
discord::Result result;
discord::Activity activity{};
discord::User user{};

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

    ClassDB::bind_method(D_METHOD("get_start_timestamp"), &Discord_Activity::get_start_timestamp);
    ClassDB::bind_method(D_METHOD("set_start_timestamp", "start_timestamp"), &Discord_Activity::set_start_timestamp);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "start_timestamp"), "set_start_timestamp", "get_start_timestamp");
    ClassDB::bind_method(D_METHOD("get_end_timestamp"), &Discord_Activity::get_end_timestamp);
    ClassDB::bind_method(D_METHOD("set_end_timestamp", "end_timestamp"), &Discord_Activity::set_end_timestamp);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "end_timestamp"), "set_end_timestamp", "get_end_timestamp");

    ClassDB::bind_method(D_METHOD("refresh"), &Discord_Activity::refresh);

    ClassDB::bind_method(D_METHOD("get_is_discord_working"), &Discord_Activity::get_is_discord_working);

    ClassDB::bind_method(D_METHOD("get_result_int"), &Discord_Activity::get_result_int);
}

Discord_Activity *Discord_Activity::get_singleton()
{
    return singleton;
}

Discord_Activity::Discord_Activity()
{
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;

    // intitalize core with discord's dummy application ID to make "is_discord_working" work anytime
    app_id = 461618159171141643;
    result = discord::Core::Create(app_id, DiscordCreateFlags_NoRequireDiscord, &core);
}

Discord_Activity::~Discord_Activity()
{
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

void Discord_Activity::coreupdate()
{
    if (result == discord::Result::Ok && app_id > 0 && app_id != 461618159171141643)
    {
        ::core->RunCallbacks();
    }
}
void Discord_Activity::debug()
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
        core->UserManager().OnCurrentUserUpdate.Connect([]()
                                                        { core->UserManager().GetCurrentUser(&user); });
    }
    else
        UtilityFunctions::push_warning("Discord Activity couldn't be updated. It could be that Discord isn't running!");
}

void Discord_Activity::set_app_id(int64_t value)
{
    app_id = value;
    result = discord::Core::Create(value, DiscordCreateFlags_NoRequireDiscord, &core);
}
int64_t Discord_Activity::get_app_id()
{
    if (app_id = 461618159171141643)
        return 0;
    else
        return app_id;
}

void Discord_Activity::set_state(String value)
{
    state = value;
    activity.SetState(value.utf8().get_data());
}
String Discord_Activity::get_state()
{
    return state;
}
void Discord_Activity::set_details(String value)
{
    details = value;
    activity.SetDetails(value.utf8().get_data());
}
String Discord_Activity::get_details()
{
    return details;
}

void Discord_Activity::refresh()
{
    if (result == discord::Result::Ok && app_id > 0 && app_id != 461618159171141643)
    {
        core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
        core->UserManager().OnCurrentUserUpdate.Connect([]()
                                                        { core->UserManager().GetCurrentUser(&user); });
    }
    else
        UtilityFunctions::push_warning("Discord Activity couldn't be updated. It could be that Discord isn't running!");
}

void Discord_Activity::set_large_image(String value)
{
    large_image = value;
    activity.GetAssets().SetLargeImage(value.utf8().get_data());
}
String Discord_Activity::get_large_image()
{
    return large_image;
}
void Discord_Activity::set_large_image_text(String value)
{
    large_image_text = value;
    activity.GetAssets().SetLargeText(value.utf8().get_data());
}
String Discord_Activity::get_large_image_text()
{
    return large_image_text;
}
void Discord_Activity::set_small_image(String value)
{
    small_image = value;
    activity.GetAssets().SetSmallImage(value.utf8().get_data());
}
String Discord_Activity::get_small_image()
{
    return small_image;
}
void Discord_Activity::set_small_image_text(String value)
{
    small_image_text = value;
    activity.GetAssets().SetSmallText(value.utf8().get_data());
}
String Discord_Activity::get_small_image_text()
{
    return small_image_text;
}

void Discord_Activity::set_start_timestamp(int64_t value)
{
    start_timestamp = value;
    activity.GetTimestamps().SetStart(value);
}
int64_t Discord_Activity::get_start_timestamp()
{
    return activity.GetTimestamps().GetStart();
}
void Discord_Activity::set_end_timestamp(int64_t value)
{
    end_timestamp = value;
    activity.GetTimestamps().SetEnd(value);
}
int64_t Discord_Activity::get_end_timestamp()
{
    return activity.GetTimestamps().GetEnd();
}

bool Discord_Activity::get_is_discord_working()
{
    return result == discord::Result::Ok && app_id > 0;
}

int Discord_Activity::get_result_int()
{
    return static_cast<int>(result);
}
