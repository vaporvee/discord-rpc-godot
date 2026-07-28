#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/editor_interface.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/godot.hpp>

#include "discordgodot.h"
#include "editor_presence.h"
using namespace godot;

static DiscordRPC *discordrpc;
static EditorPresence *editorpresence;

void initialize_discordrpc_module(ModuleInitializationLevel p_level)
{
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        ClassDB::register_class<DiscordRPC>();
        discordrpc = memnew(DiscordRPC);
        Engine::get_singleton()->register_singleton("DiscordRPC", DiscordRPC::get_singleton());

        ClassDB::register_class<EditorPresence>();
        editorpresence = memnew(EditorPresence);
        Engine::get_singleton()->register_singleton("EditorPresence", EditorPresence::get_singleton());
    }
    else if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR)
    {
        // Only the plugin's own EditorPlugin script requires the user to enable
        // it manually; the GDExtension itself loads regardless. Auto-enable it
        // once so users don't have to find it in Project Settings themselves,
        // but never force it back on if they later disable it.
        ProjectSettings *project_settings = ProjectSettings::get_singleton();
        const String auto_enable_marker = "discord_rpc_gd/auto_enabled_plugin";
        if (!project_settings->has_setting(auto_enable_marker))
        {
            EditorInterface *editor_interface = EditorInterface::get_singleton();
            if (editor_interface != nullptr)
            {
                editor_interface->call_deferred("set_plugin_enabled", "discord-rpc-gd", true);
            }
            project_settings->set_setting(auto_enable_marker, true);
            project_settings->save();
        }
    }
}

void uninitialize_discordrpc_module(ModuleInitializationLevel p_level)
{
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        Engine::get_singleton()->unregister_singleton("DiscordRPC");
        memdelete(discordrpc);
        discordrpc = nullptr;

        Engine::get_singleton()->unregister_singleton("EditorPresence");
        memdelete(editorpresence);
        editorpresence = nullptr;
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
