#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/resource.hpp>
#include "../util.h"

using namespace godot;

class ActivityResource : public Resource {
	GDCLASS(ActivityResource, Resource);

protected:
	static void _bind_methods();

public:
	enum ActivityType {
		TYPE_PLAYING = 0,
		TYPE_STREAMING = 1,
		TYPE_LISTENING = 2,
		TYPE_WATCHING = 3,
		TYPE_CUSTOM_STATUS = 4,
		TYPE_COMPETING = 5,
		TYPE_HANG_STATUS = 6,
	};

	ActivityType type = TYPE_PLAYING;
	ActivityType get_type();
	void set_type(ActivityType p_type);

	H_SET_GET(state, "")
	H_SET_GET(details, "")
	H_SET_GET(large_image, "")
	H_SET_GET(large_text, "")
	H_SET_GET(small_image, "")
	H_SET_GET(small_text, "")
	H_SET_GET(timestamps_start, 0)
	H_SET_GET(timestamps_end, 0)

    ActivityResource();
};

VARIANT_ENUM_CAST(ActivityResource::ActivityType);

#endif