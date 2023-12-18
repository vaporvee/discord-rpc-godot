#include "editor_presence.h"
#include "lib/discord_game_sdk/cpp/discord.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/time.hpp>

Ref<ProjectSettings> project_settings = ProjectSettings::get_singleton();
Ref<Engine> engine = Engine::get_singleton();
Ref<Time> time = Time::get_singleton();

EditorPresence *EditorPresence::singleton = nullptr;

discord::Core *core{};
discord::Result result;
discord::Activity activity{};

void EditorPresence::_bind_methods()
{
}
EditorPresence::EditorPresence()
{
    singleton = this;
}
EditorPresence::~EditorPresence()
{
    singleton = nullptr;
}
EditorPresence *EditorPresence::get_singleton()
{
    return singleton;
}

void EditorPresence::_ready()
{
    result = discord::Core::Create(1108142249990176808, DiscordCreateFlags_NoRequireDiscord, &core);
    activity.SetState("Test from Godot!");
    activity.SetDetails("I worked months on this");
    if (project_settings->has_setting("application/config/name"))
    {
        activity.GetAssets().SetLargeImage(String(project_settings->get_setting("application/config/name")).utf8());
    }
    activity.GetAssets().SetLargeText(String(engine->get_version_info()["string"]).utf8());
    activity.GetTimestamps().SetStart(time->get_unix_time_from_system());
    if (result == discord::Result::Ok)
    {
        core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
    }
    else
    {
        UtilityFunctions::push_warning("EditorPresence couldn't be loaded! Maybe your Discord isn't running?");
    }
}

void EditorPresence::_process(double delta)
{
    if (result == discord::Result::Ok)
        ::core->RunCallbacks();
}