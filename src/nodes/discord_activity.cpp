#include "discord_activity.h"

void DiscordActivity::_bind_methods()
{
    
    ClassDB::bind_method(D_METHOD("get_activities"), &DiscordActivity::get_activities);
    ClassDB::bind_method(D_METHOD("set_activities", "value"), &DiscordActivity::set_activities);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "activities", PROPERTY_HINT_ARRAY_TYPE, MAKE_RESOURCE_TYPE_HINT("ActivityResource")), "set_activities", "get_activities");
}
DiscordActivity::DiscordActivity()
{
}
DiscordActivity::~DiscordActivity()
{
}

TypedArray<ActivityResource> DiscordActivity::get_activities()
{
    return activities;
}

void DiscordActivity::set_activities(TypedArray<ActivityResource> value)
{
    activities = value;
}
