#include "discord_activity.h"

DiscordActivity *DiscordActivity::singleton = nullptr;

void DiscordActivity::_bind_methods()
{
    BIND_SET_GET(DiscordActivity, root_connector, Variant::NODE_PATH, godot::PROPERTY_HINT_NODE_PATH_VALID_TYPES, "DiscordConnector");
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

NodePath DiscordActivity::get_root_connector()
{
    return root_connector;
}

void DiscordActivity::set_root_connector(NodePath value)
{
    root_connector = value;
}

void DiscordActivity::_enter_tree()
{
    if (Object::cast_to<DiscordConnector>(get_parent()))
    {
        if (root_connector.is_empty())
        {
            root_connector = Object::cast_to<DiscordConnector>(get_parent())->get_path();
            if (!root_connector.is_empty())
            {
                connector = get_node<DiscordConnector>(root_connector);
            }
        }
        else
        {
            connector = get_node<DiscordConnector>(root_connector);
        }
    }
}
