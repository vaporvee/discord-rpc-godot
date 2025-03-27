#include "rich_presence.h"

void RichPresence::_bind_methods()
{
    BIND_SET_GET(RichPresence, state, Variant::STRING);
    BIND_SET_GET(RichPresence, details, Variant::STRING);
    ADD_GROUP("Large Image", "large_");
    BIND_SET_GET(RichPresence, large_image, Variant::STRING_NAME);
    BIND_SET_GET(RichPresence, large_text, Variant::STRING);
    ADD_GROUP("Small Image", "small_");
    BIND_SET_GET(RichPresence, small_image, Variant::STRING_NAME);
    BIND_SET_GET(RichPresence, small_text, Variant::STRING);
}

RichPresence::RichPresence()
{
}

void RichPresence::set_state(String p_state)
{
    state = p_state;
}

String RichPresence::get_state()
{
    return state;
}

void RichPresence::set_details(String value)
{
    details = value;
}

String RichPresence::get_details()
{
    return details;
}

void RichPresence::set_large_image(StringName value)
{
    large_image = value;
}

StringName RichPresence::get_large_image()
{
    return large_image;
}

void RichPresence::set_large_text(String value)
{
    large_text = value;
}

String RichPresence::get_large_text()
{
    return large_text;
}

void RichPresence::set_small_image(StringName value)
{
    small_image = value;
}

StringName RichPresence::get_small_image()
{
    return small_image;
}

void RichPresence::set_small_text(String value)
{
    small_text = value;
}

String RichPresence::get_small_text()
{
    return small_text;
}

void RichPresence::set_timestamps_start(int64_t value)
{
    timestamps_start = value;
}

int64_t RichPresence::get_timestamps_start()
{
    return timestamps_start;
}

void RichPresence::set_timestamps_end(int64_t value)
{
    timestamps_end = value;
}

int64_t RichPresence::get_timestamps_end()
{
    return timestamps_end;
}