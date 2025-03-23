#ifndef REGISTER_TYPES_H
#define REGISTER_TYPES_H

#define DISCORDPP_IMPLEMENTATION // this is way too important to forget

void initialize_DiscordUtil_module();
void uninitialize_DiscordUtil_module();

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/godot.hpp>

#include "util.h"
#include "nodes/discord_social_sdk.h"
#include "nodes/editor_presence.h"
#include "nodes/discord_connector.h"

#endif // REGISTER_TYPES_H