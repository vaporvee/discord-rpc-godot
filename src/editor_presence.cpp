#include "editor_presence.h"
#include "lib/discord_game_sdk/cpp/discord.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/time.hpp>

#define BIND_METHOD(method, ...) godot::ClassDB::bind_method(D_METHOD(#method, ##__VA_ARGS__), &EditorPresence::method)

EditorPresence *EditorPresence::singleton = nullptr;
discord::Core *ep_core{};
discord::Result ep_result;
discord::Activity ep_activity{};

void EditorPresence::_bind_methods()
{
    BIND_METHOD(start);
    BIND_METHOD(stop);
    BIND_METHOD(tick, "edited_scene_path");
}
EditorPresence::EditorPresence()
{
    singleton = this;
}
EditorPresence::~EditorPresence()
{
    stop();
    singleton = nullptr;
}
EditorPresence *EditorPresence::get_singleton()
{
    return singleton;
}

void EditorPresence::start()
{
    Engine *engine = Engine::get_singleton();
    ProjectSettings *project_settings = ProjectSettings::get_singleton();
    Time *time = Time::get_singleton();

    ep_result = discord::Core::Create(1108142249990176808, DiscordCreateFlags_NoRequireDiscord, &ep_core);
    ep_activity.SetState("Editing a project...");
    ep_activity.SetDetails(String(project_settings->get_setting("application/config/name")).utf8());
    if (project_settings->has_setting("application/config/name"))
    {
        ep_activity.GetAssets().SetLargeImage("godot");
    }
    ep_activity.GetAssets().SetLargeText(String(engine->get_version_info()["string"]).utf8());
    ep_activity.GetTimestamps().SetStart(time->get_unix_time_from_system());
    if (ep_result == discord::Result::Ok)
        ep_core->ActivityManager().UpdateActivity(ep_activity, [](discord::Result result) {});
    else
        UtilityFunctions::push_warning("EditorPresence couldn't be loaded! Maybe your Discord isn't running?");
}

void EditorPresence::stop()
{
    delete ep_core; // couldn't use destructor because it would not compile on linux
    ep_core = nullptr;
    ep_result = discord::Result::InternalError;
}

void EditorPresence::tick(String edited_scene_path)
{
    if (!ep_core)
        return;

    String new_state;
    if (!edited_scene_path.is_empty())
    {
        new_state = "Editing: \"" + edited_scene_path.replace("res://", "") + "\"";
    }
    else
    {
        new_state = "No Scene Loaded";
    }

    if (new_state.utf8() != ep_activity.GetState())
    {
        ep_activity.SetState(new_state.utf8());
        if (ep_result == discord::Result::Ok)
            ep_core->ActivityManager().UpdateActivity(ep_activity, [](discord::Result result) {});
    }

    if (ep_result == discord::Result::Ok)
        ep_core->RunCallbacks();
}
