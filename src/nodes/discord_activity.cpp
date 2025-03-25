#include "discord_activity.h"

DiscordActivity *DiscordActivity::singleton = nullptr;

void DiscordActivity::_bind_methods()
{
}
DiscordActivity::DiscordActivity()
{
    singleton = this;
}
DiscordActivity::~DiscordActivity()
{
    singleton = nullptr;
}
DiscordActivity *DiscordActivity::get_singleton()
{
    return singleton;
}