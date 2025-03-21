#ifndef EDITOR_PRESENCE_H
#define EDITOR_PRESENCE_H

#include <stdio.h>
#include "discordpp.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/classes/tree.hpp>

using namespace godot;

class EditorPresence : public Node
{
    GDCLASS(EditorPresence, Node);

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