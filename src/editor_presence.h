#ifndef EDITOR_PRESENCE_H
#define EDITOR_PRESENCE_H

#include <stdio.h>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/string.hpp>

using namespace godot;

class EditorPresence : public Object
{
    GDCLASS(EditorPresence, Object);

    static EditorPresence *singleton;

protected:
    static void _bind_methods();

public:
    static EditorPresence *
    get_singleton();

    EditorPresence();
    ~EditorPresence();
    void start();
    void stop();
    void tick(String edited_scene_path);
};

#endif
