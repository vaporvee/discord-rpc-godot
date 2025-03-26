#include "discord_lobby.h"

void DiscordLobby ::_bind_methods()
{
    BIND_METHOD(DiscordLobby, create_or_join_lobby, "secret");
}

void DiscordLobby::create_or_join_lobby(String secret) {
    if (connector) {
        auto current_client = connector->client;

        current_client->CreateOrJoinLobby(secret.utf8().get_data(),[current_client](discordpp::ClientResult result, uint64_t lobbyId) {
            if(result.Successful()) {
            std::cout << "Lobby created or joined successfully! Lobby Id: " << lobbyId << std::endl;
            } else {
            std::cout << "Lobby creation/join failed\n" << result.Error().c_str();
            }
        });
    }
}

DiscordLobby::DiscordLobby()
{

}

DiscordLobby::~DiscordLobby()
{

}

