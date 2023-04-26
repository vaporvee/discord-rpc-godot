#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/godot.hpp>

#include "activity.h"
#include "user.h"
using namespace godot;

static Discord_Activity *discordactivity;
static Discord_User *discorduser;

void gdextension_initialize(ModuleInitializationLevel p_level)
{
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        ClassDB::register_class<Discord_Activity>();
        ClassDB::register_class<Discord_User>();
        discordactivity = memnew(Discord_Activity);
        discorduser = memnew(Discord_User);
        Engine::get_singleton()->register_singleton("Discord_Activity", Discord_Activity::get_singleton());
        Engine::get_singleton()->register_singleton("Discord_User", Discord_User::get_singleton());
    }
}

void gdextension_terminate(ModuleInitializationLevel p_level)
{
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        Engine::get_singleton()->unregister_singleton("Discord_Activity");
        Engine::get_singleton()->unregister_singleton("Discord_User");
        memdelete(discordactivity);
        memdelete(discorduser);
    }
}

extern "C"
{
    GDExtensionBool GDE_EXPORT discordsdkgd_library_init(const GDExtensionInterface *p_interface, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
    {
        godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

        init_obj.register_initializer(gdextension_initialize);
        init_obj.register_terminator(gdextension_terminate);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}
