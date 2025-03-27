#ifndef DISCORD_ACTIVITY_H
#define DISCORD_ACTIVITY_H

#include "discord_connected.h"
#include "../resources/rich_presence.h"
#include "../resources/party_invite.h"

using namespace godot;

class DiscordActivity : public DiscordConnected
{
    GDCLASS(DiscordActivity, DiscordConnected);

protected:
    static void _bind_methods();

public:
    Ref<RichPresence> rich_presence;
    Ref<RichPresence> get_rich_presence();
    void set_rich_presence(Ref<RichPresence> value);

    Ref<PartyInvite> party_invite;
    Ref<PartyInvite> get_party_invite();
    void set_party_invite(Ref<PartyInvite> value);

	void register_launch_command(String command);
	void register_steam(int32_t steam_id);

	void accept_join_request(int64_t user_id);
	void send_invite(int64_t friend_user_id, bool is_spectate, String message_content);
	void accept_invite(int64_t user_id);

    void update();

    DiscordActivity();
    ~DiscordActivity();
};

#endif