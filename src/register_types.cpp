#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/godot.hpp>

#include "discordgodot.h"
#include "editor_presence.h"
using namespace godot;

static DiscordRPC *discordrpc;

void initialize_discordrpc_module(ModuleInitializationLevel p_level)
{
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        ClassDB::register_class<DiscordRPC>();
        discordrpc = memnew(DiscordRPC);
        Engine::get_singleton()->register_singleton("DiscordRPC", DiscordRPC::get_singleton());
        ClassDB::register_class<EditorPresence>();
    }
}

void uninitialize_discordrpc_module(ModuleInitializationLevel p_level)
{
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        Engine::get_singleton()->unregister_singleton("DiscordRPC");
        memdelete(discordrpc);
    }
}

extern "C"
{
    GDExtensionBool GDE_EXPORT discordrpcgd_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
    {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        init_obj.register_initializer(initialize_discordrpc_module);
        init_obj.register_terminator(uninitialize_discordrpc_module);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}
