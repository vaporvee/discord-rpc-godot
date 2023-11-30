#include "loader_node.h"
#include "discordgodot.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

#define EDITOR_PRESENCE_ID 1108142249990176808

void DiscordLoader::_bind_methods()
{
}

DiscordLoader::DiscordLoader()
{
}

DiscordLoader::~DiscordLoader()
{
}

void DiscordLoader::_process(double delta)
{
    discord_sdk *singleton = discord_sdk::get_singleton();
    singleton->coreupdate();
}