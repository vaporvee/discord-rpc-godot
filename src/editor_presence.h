#ifndef DISCORDGODOT_H
#define DISCORDGODOT_H

#include <stdio.h>
#include "lib/discord_game_sdk/cpp/discord.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>

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

    EditorPresence();
    ~EditorPresence();
    void _ready() override;
    void _process(double delta) override;
};

#endif