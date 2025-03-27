#include "discord_activity.h"

void DiscordActivity::_bind_methods()
{
    BIND_SET_GET(DiscordActivity, rich_presence, Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "RichPresence");
    BIND_METHOD(DiscordActivity, update_rich_presence);
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

void DiscordActivity::update_rich_presence()
{
    if(rich_presence.is_valid()){
        discordpp::Activity activity;
        activity.SetState(rich_presence->get_state().utf8().get_data());
        activity.SetDetails(rich_presence->get_details().utf8().get_data());
        discordpp::ActivityAssets assets;
        assets.SetSmallImage(String(rich_presence->get_small_image()).utf8().get_data());
        assets.SetSmallText(rich_presence->get_small_text().utf8().get_data());
        assets.SetLargeImage(String(rich_presence->get_large_image()).utf8().get_data());
        assets.SetLargeText(rich_presence->get_large_text().utf8().get_data());
        activity.SetAssets(assets);
        
        connector->client->UpdateRichPresence(activity, [](discordpp::ClientResult result){});
    }
}