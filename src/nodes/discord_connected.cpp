#include "discord_connected.h"

DiscordConnected *DiscordConnected::singleton = nullptr;

void DiscordConnected::_bind_methods()
{
    BIND_SET_GET(DiscordConnected, root_connector, Variant::NODE_PATH, godot::PROPERTY_HINT_NODE_PATH_VALID_TYPES, "DiscordConnector");
}
DiscordConnected::DiscordConnected()
{
    singleton = this;
}
DiscordConnected::~DiscordConnected()
{
    singleton = nullptr;
}
DiscordConnected *DiscordConnected::get_singleton()
{
    return singleton;
}

NodePath DiscordConnected::get_root_connector()
{
    return root_connector;
}

void DiscordConnected::set_root_connector(NodePath value)
{
    root_connector = value;
}

void DiscordConnected::_enter_tree()
{
    if (cast_to<DiscordConnector>(get_parent()))
    {
        if (root_connector.is_empty())
        {
            root_connector = cast_to<DiscordConnector>(get_parent())->get_path();
            if (!root_connector.is_empty())
            {
                connector = get_node<DiscordConnector>(root_connector);
            }
        }
        else
        {
            if (get_node_or_null(root_connector)){
                connector = get_node<DiscordConnector>(root_connector);
            }
        }
    }
}