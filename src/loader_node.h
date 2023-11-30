#ifndef LOADER_NODE_H
#define LOADER_NODE_H

#include <godot_cpp/classes/node.hpp>

namespace godot
{

    class DiscordLoader : public Node
    {
        GDCLASS(DiscordLoader, Node)

    protected:
        static void _bind_methods();

    public:
        DiscordLoader();
        ~DiscordLoader();

        void _process(double delta) override;
    };

}

#endif