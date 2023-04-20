#include "main.h"
#include "./discord-game-sdk-cpp/discord.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

DiscordSDK *DiscordSDK::singleton = nullptr;
discord::Core *core{};

void DiscordSDK::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("debug"), &DiscordSDK::debug);
    ClassDB::bind_method(D_METHOD("update"), &DiscordSDK::update);
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
    auto result = discord::Core::Create(1080224638845591692, DiscordCreateFlags_Default, &core);
    discord::Activity activity{};
    activity.SetState("Test from Godot!");
    activity.SetDetails("I worked months on this");
    discord::ActivityAssets assets = activity.GetAssets();
    assets.SetLargeImage("test1");
    assets.SetSmallImage("godot");
    core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
}
void DiscordSDK::update()
{
    ::core->RunCallbacks();
}