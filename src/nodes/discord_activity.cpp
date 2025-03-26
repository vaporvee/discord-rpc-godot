#include "discord_activity.h"

void DiscordActivity::_bind_methods()
{
    BIND_SET_GET(DiscordActivity, activity, Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "ActivityResource");
}
DiscordActivity::DiscordActivity()
{
}
DiscordActivity::~DiscordActivity()
{
}

Ref<ActivityResource> DiscordActivity::get_activity()
{
    return activity;
}

void DiscordActivity::set_activity(Ref<ActivityResource> value)
{
    activity = value;
}
