#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/godot.hpp>

#include "main.h"
using namespace godot;

static DiscordSDK *discordsdk;

void gdextension_initialize(ModuleInitializationLevel p_level)
{
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        ClassDB::register_class<DiscordSDK>();

        discordsdk = memnew(DiscordSDK);
        Engine::get_singleton()->register_singleton("DiscordSDK", DiscordSDK::get_singleton()); // Cant change the class name in the cpp files for some reason
    }
}

void gdextension_terminate(ModuleInitializationLevel p_level)
{
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        Engine::get_singleton()->unregister_singleton("DiscordActivity");
        memdelete(discordsdk);
    }
}

extern "C"
{
    GDExtensionBool GDE_EXPORT discordrpcgd_library_init(const GDExtensionInterface *p_interface, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
    {
        godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

        init_obj.register_initializer(gdextension_initialize);
        init_obj.register_terminator(gdextension_terminate);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}
