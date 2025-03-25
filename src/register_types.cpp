#include "register_types.h"

using namespace godot;

static DiscordUtil *discordutil;

void initialize_DiscordUtil_module(ModuleInitializationLevel p_level)
{
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        ClassDB::register_abstract_class<DiscordSocialSDK>();
        ClassDB::register_class<DiscordUtil>();
        discordutil = memnew(DiscordUtil);
        Engine::get_singleton()->register_singleton("DiscordUtil", DiscordUtil::get_singleton());
        ClassDB::register_class<EditorPresence>();
        ClassDB::register_class<DiscordConnector>();
        ClassDB::register_abstract_class<DiscordConnected>();
        ClassDB::register_class<DiscordActivity>();
    }
}

void uninitialize_DiscordUtil_module(ModuleInitializationLevel p_level)
{
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        Engine::get_singleton()->unregister_singleton("DiscordUtil");
        memdelete(discordutil);
    }
}

extern "C"
{
    GDExtensionBool GDE_EXPORT DiscordUtilgd_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
    {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        init_obj.register_initializer(initialize_DiscordUtil_module);
        init_obj.register_terminator(uninitialize_DiscordUtil_module);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}
