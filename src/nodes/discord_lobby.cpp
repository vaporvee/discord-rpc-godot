#include "discord_lobby.h"

void DiscordLobby ::_bind_methods()
{
    BIND_METHOD(DiscordLobby, create_or_join_lobby, "secret");
}

void DiscordLobby::create_or_join_lobby(String secret)
{
    DiscordLobby::connector->client->CreateOrJoinLobby(secret.utf8().get_data(), [this](discordpp::ClientResult result, uint64_t lobbyId)
                                                       {
            if(result.Successful()) {
            std::cout << "Lobby created or joined successfully! Lobby Id: " << lobbyId << std::endl;
            } else {
            UtilityFunctions::print("Failed to create or join lobby: " + String(result.Error().c_str()));
            } });
}

DiscordLobby::DiscordLobby()
{
}

DiscordLobby::~DiscordLobby()
{
}
