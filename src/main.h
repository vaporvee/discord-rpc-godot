#ifndef DISCORDRPC_H
#define DISCORDRPC_H

#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

class DiscordRPC : public Sprite2D {
    GDCLASS(DiscordRPC, Sprite2D)

private:
    float time_passed;

protected:
    static void _bind_methods();

public:
    DiscordRPC();
    ~DiscordRPC();

    void _process(float delta);
};

}

#endif