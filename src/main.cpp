#include "main.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "./discord-game-sdk-cpp/discord.h"

using namespace godot;
using namespace discord;

Core* core{};

void DiscordRPC::_bind_methods() {
}

DiscordRPC::DiscordRPC() {
    // initialize any variables here
    time_passed = 0.0;
}

DiscordRPC::~DiscordRPC() {
    // add your cleanup here
}

void DiscordRPC::_ready() {
    discord::Result res /*= Core::Create(53908232506183680, DiscordCreateFlags_NoRequireDiscord, &core)*/;
	Activity activity{};
    UtilityFunctions::print(core);
	/*activity.SetState("Testing");
	activity.SetDetails("Fruit Loops");
	core->ActivityManager().UpdateActivity(activity, [](Result res) {
    });*/
}

void DiscordRPC::_process(float delta) {
    //::core->RunCallbacks();
}