#include "main.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "./discord-game-sdk-cpp/discord.h"

using namespace godot;

discord::Core* core{};

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
    UtilityFunctions::print("HELLO MOM");
    discord::Result res /*= discord::Core::Create(53908232506183680, DiscordCreateFlags_NoRequireDiscord, &core)*/;
	//discord::Activity activity{};
	//activity.SetState("Testing");
	//activity.SetDetails("Fruit Loops");
	//core->ActivityManager().UpdateActivity(activity, [](discord::Result res) {

    //});
}

void DiscordRPC::_process(float delta) {
    //::core->RunCallbacks();
}