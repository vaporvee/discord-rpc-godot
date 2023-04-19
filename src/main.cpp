#include "main.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "discord-game-sdk-cpp/discord.h"

using namespace godot;

discord::Core *core{};

void DiscordRPC::_bind_methods()
{
}

DiscordRPC::DiscordRPC()
{
    // initialize any variables here
}

DiscordRPC::~DiscordRPC()
{
    // add your cleanup here
}

void DiscordRPC::_ready()
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

void DiscordRPC::_process(float delta)
{
    ::core->RunCallbacks();
}