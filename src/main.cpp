#include "main.h"
#include <godot_cpp/core/class_db.hpp>

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

void DiscordRPC::_process(float delta) {
    time_passed += delta;

    Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));

    set_position(new_position);
}