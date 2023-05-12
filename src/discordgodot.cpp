#include "discordgodot.h"
#include "lib/discord_game_sdk/cpp/discord.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/time.hpp>

using namespace godot;

discord_sdk *discord_sdk::singleton = nullptr;

discord::Core *core{};
discord::Result result;
discord::Activity sdkactivity{};
discord::User user{};

void discord_sdk::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("debug"), &discord_sdk::debug);
    ClassDB::bind_method(D_METHOD("coreupdate"), &discord_sdk::coreupdate);

    ClassDB::bind_method(D_METHOD("get_activity"), &discord_sdk::get_activity);
    ClassDB::bind_method(D_METHOD("set_activity", "activity"), &discord_sdk::set_activity);
    ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "activity"), "set_activity", "get_activity");

    ClassDB::bind_method(D_METHOD("refresh"), &discord_sdk::refresh);

    ClassDB::bind_method(D_METHOD("get_is_discord_working"), &discord_sdk::get_is_discord_working);

    ClassDB::bind_method(D_METHOD("get_result_int"), &discord_sdk::get_result_int);
}

discord_sdk *discord_sdk::get_singleton()
{
    return singleton;
}

discord_sdk::discord_sdk()
{
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
    // add Dictionary values:
    activity["app_id"] = 461618159171141643;
    activity["state"] = "";
    activity["details"] = "";
    activity["large_image"] = "";
    activity["large_image_text"] = "";
    activity["small_image"] = "";
    activity["small_image_text"] = "";
    activity["start_timestamp"] = 0;
    activity["end_timestamp"] = 0;
    // intitalize core with discord's dummy application ID to make "is_discord_working" work anytime
    result = discord::Core::Create(activity["app_id"].INT, DiscordCreateFlags_NoRequireDiscord, &core);
}

discord_sdk::~discord_sdk()
{
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

void discord_sdk::coreupdate()
{
    if (result == discord::Result::Ok && activity["app_id"].INT > 0 && activity["app_id"].INT != 461618159171141643)
    {
        ::core->RunCallbacks();
    }
}
void discord_sdk::debug()
{
    result = discord::Core::Create(1080224638845591692, DiscordCreateFlags_NoRequireDiscord, &core);
    sdkactivity.SetState("Test from Godot!");
    sdkactivity.SetDetails("I worked months on this");
    sdkactivity.GetAssets().SetLargeImage("test1");
    sdkactivity.GetAssets().SetLargeText("wow test text for large image");
    sdkactivity.GetAssets().SetSmallImage("godot");
    sdkactivity.GetAssets().SetSmallText("wow test text for small image");
    sdkactivity.GetTimestamps().SetStart(1682242800);
    if (result == discord::Result::Ok)
    {
        core->ActivityManager().UpdateActivity(sdkactivity, [](discord::Result result) {});
        core->UserManager().OnCurrentUserUpdate.Connect([]()
                                                        { core->UserManager().GetCurrentUser(&user); });
    }
    else
        UtilityFunctions::push_warning("Discord Activity couldn't be updated. It could be that Discord isn't running!");
}

void discord_sdk::set_activity(Dictionary value)
{
    activity = value;
    // sdkactivity.SetState(value["app_id"].stringify().utf8().get_data());
    result = discord::Core::Create(value["app_id"].INT, DiscordCreateFlags_NoRequireDiscord, &core);
}
Dictionary discord_sdk::get_activity()
{
    return activity;
}

void discord_sdk::refresh()
{
    if (result == discord::Result::Ok && activity["app_id"].INT > 0 && activity["app_id"].INT != 461618159171141643)
    {
        core->ActivityManager().UpdateActivity(sdkactivity, [](discord::Result result) {});
        core->UserManager().OnCurrentUserUpdate.Connect([]()
                                                        { core->UserManager().GetCurrentUser(&user); });
    }
    else
        UtilityFunctions::push_warning("Discord Activity couldn't be updated. It could be that Discord isn't running!");
}
/*
void discord_sdk::set_state(String value)
{
    state = value;
    sdkactivity.SetState(value.utf8().get_data());
}
String discord_sdk::get_state()
{
    return state;
}
void discord_sdk::set_details(String value)
{
    details = value;
    sdkactivity.SetDetails(value.utf8().get_data());
}
String discord_sdk::get_details()
{
    return details;
}


void discord_sdk::set_large_image(String value)
{
    large_image = value;
    sdkactivity.GetAssets().SetLargeImage(value.utf8().get_data());
}
String discord_sdk::get_large_image()
{
    return large_image;
}
void discord_sdk::set_large_image_text(String value)
{
    large_image_text = value;
    sdkactivity.GetAssets().SetLargeText(value.utf8().get_data());
}
String discord_sdk::get_large_image_text()
{
    return large_image_text;
}
void discord_sdk::set_small_image(String value)
{
    small_image = value;
    sdkactivity.GetAssets().SetSmallImage(value.utf8().get_data());
}
String discord_sdk::get_small_image()
{
    return small_image;
}
void discord_sdk::set_small_image_text(String value)
{
    small_image_text = value;
    sdkactivity.GetAssets().SetSmallText(value.utf8().get_data());
}
String discord_sdk::get_small_image_text()
{
    return small_image_text;
}

void discord_sdk::set_start_timestamp(int64_t value)
{
    start_timestamp = value;
    sdkactivity.GetTimestamps().SetStart(value);
}
int64_t discord_sdk::get_start_timestamp()
{
    return sdkactivity.GetTimestamps().GetStart();
}
void discord_sdk::set_end_timestamp(int64_t value)
{
    end_timestamp = value;
    sdkactivity.GetTimestamps().SetEnd(value);
}
int64_t discord_sdk::get_end_timestamp()
{
    return sdkactivity.GetTimestamps().GetEnd();
} */

bool discord_sdk::get_is_discord_working()
{
    return result == discord::Result::Ok && activity["app_id"].INT > 0;
}

int discord_sdk::get_result_int()
{
    return static_cast<int>(result);
}
