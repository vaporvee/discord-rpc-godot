#ifndef DISCORD_LOBBY_H
#define DISCORD_LOBBY_H

#include "discord_connected.h"

using namespace godot;

class DiscordLobby : public DiscordConnected
{
    GDCLASS(DiscordLobby, DiscordConnected);

protected:
    static void _bind_methods();

public:
    void create_or_join_lobby(String secret);
    DiscordLobby();
    ~DiscordLobby();
};

#endif