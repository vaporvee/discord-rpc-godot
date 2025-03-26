#ifndef DISCORD_LINKED_CHANNEL_H
#define DISCORD_LINKED_CHANNEL_H

#include "discord_connected.h"

using namespace godot;

class DiscordLinkedChannel : public DiscordConnected
{
    GDCLASS(DiscordLinkedChannel, DiscordConnected);

protected:
    static void _bind_methods();

public:
    DiscordLinkedChannel();
    ~DiscordLinkedChannel();
};

#endif