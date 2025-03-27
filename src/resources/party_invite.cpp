#include "party_invite.h"

void PartyInvite::_bind_methods()
{
    BIND_SET_GET(PartyInvite, id, Variant::STRING);
    BIND_SET_GET(PartyInvite, current_size, Variant::INT);
    BIND_SET_GET(PartyInvite, max_size, Variant::INT);
    BIND_SET_GET(PartyInvite, join_secret, Variant::STRING);
    BIND_SET_GET(PartyInvite, instanced, Variant::BOOL);
    BIND_SET_GET(PartyInvite, is_public_party, Variant::BOOL);
}

PartyInvite::PartyInvite()
{
}

String PartyInvite::get_id()
{
    return id;
}

void PartyInvite::set_id(String value)
{
    id = value;
}

int64_t PartyInvite::get_current_size()
{
    return current_size;
}

void PartyInvite::set_current_size(int64_t value)
{
    current_size = value;
}

int64_t PartyInvite::get_max_size()
{
    return max_size;
}

void PartyInvite::set_max_size(int64_t value)
{
    max_size = value;
}

String PartyInvite::get_join_secret()
{
    return join_secret;
}

void PartyInvite::set_join_secret(String value)
{
    join_secret = value;
}

bool PartyInvite::get_instanced()
{
    return instanced;
}

void PartyInvite::set_instanced(bool value)
{
    instanced = value;
}

bool PartyInvite::get_is_public_party()
{
    return is_public_party;
}

void PartyInvite::set_is_public_party(bool value)
{
    is_public_party = value;
}

