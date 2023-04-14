#ifndef DISCORDRPC_H
#define DISCORDRPC_H

#include <godot_cpp/classes/node.hpp>
#include "discord.h"

namespace godot
{
    class DiscordRPC : public Node
    {
        GDCLASS(DiscordRPC, Node)

    private:
        float time_passed;

    protected:
        static void _bind_methods();

    public:
        DiscordRPC();
        ~DiscordRPC();

        void _ready();
        void _process(float delta);
    };
}

#endif