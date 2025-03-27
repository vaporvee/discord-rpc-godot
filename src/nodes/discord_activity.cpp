#include "discord_activity.h"

void DiscordActivity::_bind_methods()
{
    BIND_SET_GET(DiscordActivity, rich_presence, Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "RichPresence");
    BIND_SET_GET(DiscordActivity, party_invite, Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "PartyInvite");
    BIND_METHOD(DiscordActivity, update);
}
DiscordActivity::DiscordActivity()
{
}
DiscordActivity::~DiscordActivity()
{
}

Ref<RichPresence> DiscordActivity::get_rich_presence()
{
    return rich_presence;
}

void DiscordActivity::set_rich_presence(Ref<RichPresence> value)
{
    rich_presence = value;
}

Ref<PartyInvite> DiscordActivity::get_party_invite()
{
    return party_invite;
}

void DiscordActivity::set_party_invite(Ref<PartyInvite> value)
{
    party_invite = value;
}

void DiscordActivity::update()
{
    discordpp::Activity activity;
    if (rich_presence.is_valid())
    {
        activity.SetState(rich_presence->get_state().utf8().get_data());
        activity.SetDetails(rich_presence->get_details().utf8().get_data());
        discordpp::ActivityAssets assets;
        assets.SetSmallImage(String(rich_presence->get_small_image()).utf8().get_data());
        assets.SetSmallText(rich_presence->get_small_text().utf8().get_data());
        assets.SetLargeImage(String(rich_presence->get_large_image()).utf8().get_data());
        assets.SetLargeText(rich_presence->get_large_text().utf8().get_data());
        activity.SetAssets(assets);
        discordpp::ActivityTimestamps timestamps;
        timestamps.SetStart(rich_presence->get_timestamps_start());
        timestamps.SetEnd(rich_presence->get_timestamps_end());
        activity.SetTimestamps(timestamps);
    }
    if (party_invite.is_valid())
    {
        discordpp::ActivityParty party;
        party.SetCurrentSize(party_invite->get_current_size());
        party.SetMaxSize(party_invite->get_max_size());
        party.SetId(party_invite->get_id().utf8().get_data());
        party.SetPrivacy(party_invite->get_is_public_party() ? discordpp::ActivityPartyPrivacy::Public : discordpp::ActivityPartyPrivacy::Private);
        discordpp::ActivitySecrets secrets;
        secrets.SetJoin(party_invite->get_join_secret().utf8().get_data());
        activity.SetSecrets(secrets);
        activity.SetParty(party);
        // TODO: Supported platforms
        // activity.SetSupportedPlatforms();
        // TODO: Error on invalid values inside getters
    }
    connector->client->UpdateRichPresence(activity, [](discordpp::ClientResult result) {});
}