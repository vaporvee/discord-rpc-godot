#include "discord_social_sdk.h"

DiscordSocialSDK *DiscordSocialSDK::singleton = nullptr;

void DiscordSocialSDK::_bind_methods()
{
}
DiscordSocialSDK::DiscordSocialSDK()
{
    singleton = this;
}
DiscordSocialSDK::~DiscordSocialSDK()
{
    singleton = nullptr;
}
DiscordSocialSDK *DiscordSocialSDK::get_singleton()
{
    return singleton;
}