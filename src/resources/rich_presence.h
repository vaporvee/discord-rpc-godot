#ifndef RICH_PRESENCE_H
#define RICH_PRESENCE_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/resource.hpp>
#include "../util.h"

using namespace godot;

class RichPresence : public Resource {
	GDCLASS(RichPresence, Resource);

protected:
	static void _bind_methods();

public:

	H_SET_GET(state, "")
	H_SET_GET(details, "")
	StringName large_image;
	StringName get_large_image();
	void set_large_image(StringName value);
	H_SET_GET(large_text, "")
	StringName small_image;
	StringName get_small_image();
	void set_small_image(StringName value);
	H_SET_GET(small_text, "")
	H_SET_GET(timestamps_start, 0)
	H_SET_GET(timestamps_end, 0)

    RichPresence();
};

#endif