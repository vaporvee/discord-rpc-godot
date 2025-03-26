#include "activity.h"

void ActivityResource::_bind_methods()
{
    BIND_SET_GET(ActivityResource, type, Variant::INT, PROPERTY_HINT_ENUM, "Playing,Streaming,Listening,Watching,Custom Status,Competing,Hang Status");
    BIND_SET_GET(ActivityResource, state, Variant::STRING);
    BIND_SET_GET(ActivityResource, details, Variant::STRING);
    BIND_SET_GET(ActivityResource, large_image, Variant::STRING);
    BIND_SET_GET(ActivityResource, large_text, Variant::STRING);
    BIND_SET_GET(ActivityResource, small_image, Variant::STRING);
    BIND_SET_GET(ActivityResource, small_text, Variant::STRING);
    BIND_SET_GET(ActivityResource, timestamps_start, Variant::INT);
    BIND_SET_GET(ActivityResource, timestamps_end, Variant::INT);

    BIND_ENUM_CONSTANT(TYPE_PLAYING);
    BIND_ENUM_CONSTANT(TYPE_STREAMING);
    BIND_ENUM_CONSTANT(TYPE_LISTENING);
    BIND_ENUM_CONSTANT(TYPE_WATCHING);
    BIND_ENUM_CONSTANT(TYPE_CUSTOM_STATUS);
    BIND_ENUM_CONSTANT(TYPE_COMPETING);
    BIND_ENUM_CONSTANT(TYPE_HANG_STATUS);
}

ActivityResource::ActivityResource()
{
}

void ActivityResource::set_type(ActivityType p_type)
{
    type = p_type;
}

ActivityResource::ActivityType ActivityResource::get_type()
{
    return type;
}

void ActivityResource::set_state(String p_state)
{
    state = p_state;
}

String ActivityResource::get_state()
{
    return state;
}

void ActivityResource::set_details(String value)
{
    details = value;
}

String ActivityResource::get_details()
{
    return details;
}

void ActivityResource::set_large_image(String value)
{
    large_image = value;
}

String ActivityResource::get_large_image()
{
    return large_image;
}

void ActivityResource::set_large_text(String value)
{
    large_text = value;
}

String ActivityResource::get_large_text()
{
    return large_text;
}

void ActivityResource::set_small_image(String value)
{
    small_image = value;
}

String ActivityResource::get_small_image()
{
    return small_image;
}

void ActivityResource::set_small_text(String value)
{
    small_text = value;
}

String ActivityResource::get_small_text()
{
    return small_text;
}

void ActivityResource::set_timestamps_start(int64_t value)
{
    timestamps_start = value;
}

int64_t ActivityResource::get_timestamps_start()
{
    return timestamps_start;
}

void ActivityResource::set_timestamps_end(int64_t value)
{
    timestamps_end = value;
}

int64_t ActivityResource::get_timestamps_end()
{
    return timestamps_end;
}