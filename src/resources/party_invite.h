#ifndef PARTY_INVITE_H
#define PARTY_INVITE_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/resource.hpp>
#include "../util.h"

using namespace godot;

class PartyInvite : public Resource {
	GDCLASS(PartyInvite, Resource);

protected:
	static void _bind_methods();

public:
	H_SET_GET(id, "")
	H_SET_GET(current_size, 1)
	H_SET_GET(max_size, 4)
	H_SET_GET(join_secret, "")
	H_SET_GET(instanced, false)
	H_SET_GET(is_public_party, false)

	PartyInvite();
};

#endif