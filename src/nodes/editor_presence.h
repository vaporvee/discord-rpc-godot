#ifndef EDITOR_PRESENCE_H
#define EDITOR_PRESENCE_H

#include "discord_social_sdk.h"

using namespace godot;

class EditorPresence : public DiscordSocialSDK
{
    GDCLASS(EditorPresence, DiscordSocialSDK);

    static EditorPresence *singleton;

protected:
    static void _bind_methods();

public:
    static EditorPresence *
    get_singleton();

    godot::Engine *engine = godot::Engine::get_singleton();
    godot::ProjectSettings *project_settings = godot::ProjectSettings::get_singleton();
    godot::Time *time = godot::Time::get_singleton();

    String state_string;

    EditorPresence();
    ~EditorPresence();
    void _ready() override;
    void _process(double delta) override;
};

#endif