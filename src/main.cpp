#include "main.h"
#include "./discord-game-sdk-cpp/discord.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

DiscordSDK *DiscordSDK::singleton = nullptr;

discord::Core *core{};
discord::Result result;
discord::Activity activity{};

void DiscordSDK::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("debug"), &DiscordSDK::debug);
    ClassDB::bind_method(D_METHOD("coreupdate"), &DiscordSDK::coreupdate);

    ClassDB::bind_method(D_METHOD("get_app_id"), &DiscordSDK::get_app_id);
    ClassDB::bind_method(D_METHOD("set_app_id", "app_id"), &DiscordSDK::set_app_id);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "app_id"), "set_app_id", "get_app_id");
    ClassDB::bind_method(D_METHOD("get_state"), &DiscordSDK::get_state);
    ClassDB::bind_method(D_METHOD("set_state", "state"), &DiscordSDK::set_state);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "state"), "set_state", "get_state");
    ClassDB::bind_method(D_METHOD("get_details"), &DiscordSDK::get_details);
    ClassDB::bind_method(D_METHOD("set_details", "details"), &DiscordSDK::set_details);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "details"), "set_details", "get_details");

    ClassDB::bind_method(D_METHOD("refresh"), &DiscordSDK::refresh);
}

DiscordSDK *DiscordSDK::get_singleton()
{
    return singleton;
}

DiscordSDK::DiscordSDK()
{
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
}

DiscordSDK::~DiscordSDK()
{
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

void DiscordSDK::debug()
{
    auto debugresult = discord::Core::Create(1080224638845591692, DiscordCreateFlags_NoRequireDiscord, &core);
    discord::Activity debugactivity{};
    debugactivity.SetState("Test from Godot!");
    debugactivity.SetDetails("I worked months on this");
    discord::ActivityAssets debugassets = debugactivity.GetAssets();
    debugassets.SetLargeImage("test1");
    debugassets.SetSmallImage("godot");
    core->ActivityManager().UpdateActivity(debugactivity, [](discord::Result debugresult) {});
}

void DiscordSDK::coreupdate()
{
    ::core->RunCallbacks();
}

void DiscordSDK::set_app_id(const int64_t &appid)
{
    app_id = appid;
    result = discord::Core::Create(app_id, DiscordCreateFlags_NoRequireDiscord, &core);
}
int64_t DiscordSDK::get_app_id() const
{
    return app_id;
}

void DiscordSDK::set_state(const String &pstate)
{
    state = pstate;
    activity.SetState(state.utf8().get_data());
}
String DiscordSDK::get_state() const
{
    return state;
}
void DiscordSDK::set_details(const String &detail)
{
    details = detail;
    activity.SetDetails(details.utf8().get_data());
}
String DiscordSDK::get_details() const
{
    return details;
}

void DiscordSDK::refresh()
{
    core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
}