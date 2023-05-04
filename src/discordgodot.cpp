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
discord::Activity sdkactivity{};
discord::User user{};

void Discord_SDK::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("debug"), &Discord_SDK::debug);
    ClassDB::bind_method(D_METHOD("coreupdate"), &Discord_SDK::coreupdate);

    ClassDB::bind_method(D_METHOD("get_app_id"), &Discord_SDK::get_app_id);
    ClassDB::bind_method(D_METHOD("set_app_id", "app_id"), &Discord_SDK::set_app_id);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "app_id"), "set_app_id", "get_app_id");
<<<<<<< HEAD

    ClassDB::bind_method(D_METHOD("get_activity"), &Discord_SDK::get_activity);
    ClassDB::bind_method(D_METHOD("set_activity", "activity"), &Discord_SDK::set_activity);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "activity"), "set_activity", "get_activity")
    == == == =
>>>>>>> 3047e47 (constructed custom activity struct)

                 ClassDB::bind_method(D_METHOD("get_is_discord_working"), &Discord_SDK::get_is_discord_working);

    ClassDB::bind_method(D_METHOD("get_result_int"), &Discord_SDK::get_result_int);

    ClassDB::bind_method(D_METHOD("refresh"), &Discord_SDK::refresh);
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
    if (result == discord::Result::Ok && app_id > 0)
    {
        ::core->RunCallbacks();
    }
}
void Discord_SDK::debug()
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

void Discord_SDK::set_app_id(const int64_t &value)
{
    app_id = value;
    result = discord::Core::Create(value, DiscordCreateFlags_NoRequireDiscord, &core);
}
int64_t Discord_SDK::get_app_id() const
{
    return app_id;
}

void Discord_SDK::set_activity(const activitystruct &value)
{
    activity = value;
    sdkactivity.SetState(activity.state.utf8().get_data());
    sdkactivity.SetDetails(activity.details.utf8().get_data());
    sdkactivity.GetAssets().SetLargeImage(activity.large_image.utf8().get_data());
    sdkactivity.GetAssets().SetLargeText(activity.large_image_text.utf8().get_data());
    sdkactivity.GetAssets().SetSmallImage(activity.small_image.utf8().get_data());
    sdkactivity.GetAssets().SetSmallText(activity.small_image_text.utf8().get_data());
    sdkactivity.GetTimestamps().SetStart(activity.start_timestamp);
    sdkactivity.GetTimestamps().SetEnd(activity.end_timestamp);
}
Discord_SDK::activitystruct Discord_SDK::get_activity() const
{
    return activity;
}

bool Discord_SDK::get_is_discord_working() const
{
    return result == discord::Result::Ok && app_id > 0;
}

int Discord_SDK::get_result_int() const
{
    return static_cast<int>(result);
}

void Discord_SDK::refresh()
{
    if (result == discord::Result::Ok && app_id > 0)
    {
        core->ActivityManager().UpdateActivity(sdkactivity, [](discord::Result result) {});
        core->UserManager().OnCurrentUserUpdate.Connect([]()
                                                        { core->UserManager().GetCurrentUser(&user); });
    }
    else
        UtilityFunctions::push_warning("Discord Activity couldn't be updated. It could be that Discord isn't running!");
}