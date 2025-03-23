#ifndef DISCORD_SOCIAL_SDK_H
#define DISCORD_SOCIAL_SDK_H

#include "discordpp.h"
#include "../definitions.h"

#include <stdio.h>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/classes/tree.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

using namespace godot;

class DiscordSocialSDK : public Node
{
    GDCLASS(DiscordSocialSDK, Node);

    static DiscordSocialSDK *singleton;

protected:
    static void _bind_methods();

public:
    static DiscordSocialSDK *
    get_singleton();

    DiscordSocialSDK();
    ~DiscordSocialSDK();
};

#endif