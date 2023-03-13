#include "main.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

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
   UtilityFunctions::print("Hello mom");
}

void DiscordRPC::_process(float delta) {
    
}