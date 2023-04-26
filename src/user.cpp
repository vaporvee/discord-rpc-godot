#include "user.h"
#include <string>
#include "./discord-game-sdk-cpp/discord.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/time.hpp>

using namespace godot;

Discord_User *Discord_User::singleton = nullptr;

void Discord_User::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_name"), &Discord_User::get_name);
}

Discord_User *Discord_User::get_singleton()
{
    return singleton;
}

Discord_User::Discord_User()
{
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
}

Discord_User::~Discord_User()
{
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

String Discord_User::get_name() const
{
    discord::User user;
    return user.GetUsername();
}