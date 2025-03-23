#include "discord_connector.h"

DiscordConnector *DiscordConnector::singleton = nullptr;

void DiscordConnector::_bind_methods()
{
    BIND_SET_GET(DiscordConnector, app_id, Variant::INT, godot::PROPERTY_HINT_RANGE, "-99999,99999,or_less,or_greater,hide_slider");
    BIND_SET_GET(DiscordConnector, auto_connect, Variant::BOOL);
    BIND_SET_GET(DiscordConnector, token_auto_manage, Variant::BOOL);
}
DiscordConnector::DiscordConnector()
{
    singleton = this;
}
DiscordConnector::~DiscordConnector()
{
    singleton = nullptr;
}
DiscordConnector *DiscordConnector::get_singleton()
{
    return singleton;
}

void DiscordConnector::_ready()
{
    client = std::make_shared<discordpp::Client>();
}

void DiscordConnector::_process(double delta)
{
    if (Engine::get_singleton()->is_editor_hint() && !editor_process)
    {
        discordpp::RunCallbacks();
    }
}

void DiscordConnector::set_app_id(uint64_t value)
{
    app_id = value;
}

uint64_t DiscordConnector::get_app_id()
{
    return app_id;
}

void DiscordConnector::set_token_auto_manage(bool value)
{
    token_auto_manage = value;
}

bool DiscordConnector::get_token_auto_manage()
{
    return token_auto_manage;
}

void DiscordConnector::set_auto_connect(bool value)
{
    auto_connect = value;
}

bool DiscordConnector::get_auto_connect()
{
    return auto_connect;
}