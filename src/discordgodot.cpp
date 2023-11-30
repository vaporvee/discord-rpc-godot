#include "discordgodot.h"
#include "lib/discord_game_sdk/cpp/discord.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/time.hpp>

#define BIND_METHOD(method, ...) godot::ClassDB::bind_method(D_METHOD(#method, __VA_ARGS__), &discord_sdk::method)
#define BIND_SET_GET(property_name, variant_type)                                                                   \
    godot::ClassDB::bind_method(D_METHOD("get_" #property_name), &discord_sdk::get_##property_name);                \
    godot::ClassDB::bind_method(D_METHOD("set_" #property_name, #variant_type), &discord_sdk::set_##property_name); \
    godot::ClassDB::add_property(get_class_static(), PropertyInfo(variant_type, #property_name), "set_" #property_name, "get_" #property_name)
#define BIND_SIGNAL(signal_name, ...) godot::ClassDB::add_signal(get_class_static(), MethodInfo(#signal_name, ##__VA_ARGS__))
#define SET_GET(variable, setter, ...) /*getter isn't mandatory for this project*/     \
    decltype(discord_sdk::variable) discord_sdk::get_##variable() { return variable; } \
    void discord_sdk::set_##variable(decltype(discord_sdk::variable) value)            \
    {                                                                                  \
        variable = value;                                                              \
        setter;                                                                        \
    }

discord_sdk *discord_sdk::singleton = nullptr;
discord::Core *core{};
discord::Result result;
discord::Activity activity{};
discord::User user{};

void discord_sdk::_bind_methods()
{
    BIND_SET_GET(app_id, Variant::INT);
    BIND_SET_GET(state, Variant::STRING);
    BIND_SET_GET(details, Variant::STRING);
    BIND_SET_GET(large_image, Variant::STRING);
    BIND_SET_GET(large_image_text, Variant::STRING);
    BIND_SET_GET(small_image, Variant::STRING);
    BIND_SET_GET(small_image_text, Variant::STRING);
    BIND_SET_GET(start_timestamp, Variant::INT);
    BIND_SET_GET(end_timestamp, Variant::INT);
    BIND_SET_GET(party_id, Variant::STRING);
    BIND_SET_GET(current_party_size, Variant::INT);
    BIND_SET_GET(max_party_size, Variant::INT);
    BIND_SET_GET(match_secret, Variant::STRING);
    BIND_SET_GET(join_secret, Variant::STRING);
    BIND_SET_GET(spectate_secret, Variant::STRING);
    BIND_SET_GET(instanced, Variant::BOOL);
    BIND_SET_GET(is_public_party, Variant::BOOL);
    BIND_SIGNAL(activity_join, PropertyInfo(Variant::STRING, "join_secret"));
    BIND_SIGNAL(activity_spectate, PropertyInfo(Variant::STRING, "spectate_secret"));
    BIND_SIGNAL(activity_join_request, PropertyInfo(Variant::DICTIONARY, "user_requesting"));
    BIND_SIGNAL(updated_relationship, PropertyInfo(Variant::DICTIONARY, "relationship"));
    BIND_SIGNAL(overlay_toggle, PropertyInfo(Variant::BOOL, "is_locked"));
    BIND_SIGNAL(relationships_init);
    BIND_METHOD(debug);
    BIND_METHOD(coreupdate);
    BIND_METHOD(refresh);
    ClassDB::bind_method(D_METHOD("clear", "reset_values"), &discord_sdk::clear, DEFVAL(false));
    BIND_METHOD(unclear);
    BIND_METHOD(register_command, "command");
    BIND_METHOD(register_steam, "steam_id");
    BIND_METHOD(accept_join_request, "user_id");
    BIND_METHOD(send_invite, "user_id", "is_spectate", "message_content");
    BIND_METHOD(accept_invite, "user_id");
    BIND_METHOD(get_current_user);
    BIND_METHOD(get_all_relationships);
    BIND_METHOD(get_is_overlay_enabled);
    BIND_METHOD(get_is_overlay_locked);
    BIND_METHOD(open_invite_overlay, "is_spectate");
    BIND_METHOD(open_server_invite_overlay, "invite_code");
    BIND_METHOD(open_voice_settings);
    BIND_METHOD(get_is_discord_working);
    BIND_METHOD(get_result_int);
}
SET_GET(state, activity.SetState(value.utf8().get_data()))
SET_GET(details, activity.SetDetails(value.utf8().get_data()))
SET_GET(large_image, activity.GetAssets().SetLargeImage(value.utf8().get_data()))
SET_GET(large_image_text, activity.GetAssets().SetLargeText(value.utf8().get_data()))
SET_GET(small_image, activity.GetAssets().SetSmallImage(value.utf8().get_data()))
SET_GET(small_image_text, activity.GetAssets().SetSmallText(value.utf8().get_data()))
SET_GET(start_timestamp, activity.GetTimestamps().SetStart(value))
SET_GET(end_timestamp, activity.GetTimestamps().SetEnd(value))
SET_GET(party_id, activity.GetParty().SetId(value.utf8().get_data()))
SET_GET(current_party_size, activity.GetParty().GetSize().SetCurrentSize(value))
SET_GET(max_party_size, activity.GetParty().GetSize().SetMaxSize(value))
SET_GET(match_secret, activity.GetSecrets().SetMatch(value.utf8().get_data()))
SET_GET(join_secret, activity.GetSecrets().SetJoin(value.utf8().get_data()))
SET_GET(spectate_secret, activity.GetSecrets().SetSpectate(value.utf8().get_data()))
SET_GET(instanced, activity.SetInstance(value))
SET_GET(is_public_party, activity.GetParty().SetPrivacy(static_cast<discord::ActivityPartyPrivacy>(value)))

discord_sdk::discord_sdk()
{
    singleton = this;
    app_id = 0;
}

discord_sdk::~discord_sdk()
{
    if (app_id != 0)
    {
        set_app_id(0);
        core->~Core();
    }
    singleton = nullptr;
}

discord_sdk *discord_sdk::get_singleton()
{
    return singleton;
}

void discord_sdk::coreupdate()
{
    if (result == discord::Result::Ok && app_id > 0)
        ::core->RunCallbacks();
}
void discord_sdk::debug()
{
    result = discord::Core::Create(1080224638845591692, DiscordCreateFlags_NoRequireDiscord, &core);
    activity.SetState("Test from Godot!");
    activity.SetDetails("I worked months on this");
    activity.GetAssets().SetLargeImage("test1");
    activity.GetAssets().SetLargeText("wow test text for large image");
    activity.GetAssets().SetSmallImage("godot");
    activity.GetAssets().SetSmallText("wow test text for small image");
    activity.GetTimestamps().SetStart(1682242800);
    if (result == discord::Result::Ok)
    {
        core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
    }
    else
        UtilityFunctions::push_warning("Discord Activity couldn't be updated. It could be that Discord isn't running!");
}

void discord_sdk::set_app_id(int64_t value)
{
    app_id = value;
    if (app_id > 0)
    {
        result = discord::Core::Create(value, DiscordCreateFlags_NoRequireDiscord, &core); // after setting app_ID it initializes everything

        if (result == discord::Result::Ok)
        {
            // initialize currentuser
            core->UserManager().OnCurrentUserUpdate.Connect([]()
                                                            {discord::User user{};
            core->UserManager().GetCurrentUser(&user); });
            // signals
            core->ActivityManager().OnActivityJoin.Connect([](const char *secret)
                                                           { discord_sdk::get_singleton()
                                                                 ->emit_signal("activity_join", secret); });
            core->ActivityManager().OnActivitySpectate.Connect([](const char *secret)
                                                               { discord_sdk::get_singleton()
                                                                     ->emit_signal("activity_spectate", secret); });
            core->ActivityManager().OnActivityJoinRequest.Connect([this](discord::User const &user)
                                                                  { discord_sdk::get_singleton()
                                                                        ->emit_signal("activity_join_request", user2dict(user)); });
            core->OverlayManager().OnToggle.Connect([](bool is_locked)
                                                    { discord_sdk::get_singleton()
                                                          ->emit_signal("overlay_toggle", is_locked); });
            core->RelationshipManager().OnRefresh.Connect([&]()
                                                          { discord_sdk::get_singleton()
                                                                ->emit_signal("relationships_init"); });
            core->RelationshipManager().OnRelationshipUpdate.Connect([&](discord::Relationship const &relationship)
                                                                     { discord_sdk::get_singleton()
                                                                           ->emit_signal("updated_relationship", relationship2dict(relationship)); });
        }
    }
}
int64_t discord_sdk::get_app_id()
{
    if (app_id != 0)
        return app_id;
    return old_app_id;
}

void discord_sdk::refresh()
{
    if (result == discord::Result::Ok && app_id > 0)
    {
        activity.GetParty().SetPrivacy(discord::ActivityPartyPrivacy::Public);
        activity.SetType(discord::ActivityType::Playing);
        core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
    }
    else
        UtilityFunctions::push_warning("Discord Activity couldn't be updated. It could be that Discord isn't running!");
}

void discord_sdk::clear(bool reset_values = false)
{
    if (result == discord::Result::Ok)
    {
        if (reset_values)
        {
            old_app_id = 0;
            set_state("");
            set_details("");
            set_large_image("");
            set_large_image_text("");
            set_small_image("");
            set_small_image_text("");
            set_start_timestamp(0);
            set_end_timestamp(0);
            set_party_id("");
            set_current_party_size(0);
            set_max_party_size(0);
            set_match_secret("");
            set_join_secret("");
            set_spectate_secret("");
            set_instanced(false);
            set_is_public_party(false);
            set_is_overlay_locked(false);
            core->ActivityManager().ClearActivity([](discord::Result result) {});
        }
        else
            old_app_id = app_id;
        set_app_id(0);
        delete core;
        core = nullptr;
    }
}

void discord_sdk::unclear()
{
    if (old_app_id > 0)
    {
        set_app_id(old_app_id);
        refresh();
        old_app_id = 0;
    }
    else
        UtilityFunctions::push_warning("Discord Activity couldn't be uncleared. Maybe it didn't get cleared before?");
}

bool discord_sdk::get_is_overlay_enabled()
{
    bool ie;
    if (result == discord::Result::Ok && app_id > 0)
        core->OverlayManager().IsEnabled(&ie);
    return ie;
}
bool discord_sdk::get_is_overlay_locked()
{
    bool il;
    if (result == discord::Result::Ok && app_id > 0)
        core->OverlayManager().IsLocked(&il);
    return il;
}
void discord_sdk::set_is_overlay_locked(bool value)
{
    is_overlay_locked = value;
    if (result == discord::Result::Ok && app_id > 0)
        core->OverlayManager().SetLocked(value, {});
}
void discord_sdk::open_invite_overlay(bool is_spectate)
{
    if (result == discord::Result::Ok && app_id > 0)
        core->OverlayManager().OpenActivityInvite(static_cast<discord::ActivityActionType>(is_spectate + 1), {});
}
void discord_sdk::open_server_invite_overlay(String invite_code)
{
    if (result == discord::Result::Ok && app_id > 0)
        core->OverlayManager().OpenGuildInvite(invite_code.utf8().get_data(), {});
}
void discord_sdk::open_voice_settings()
{
    if (result == discord::Result::Ok && app_id > 0)
        core->OverlayManager().OpenVoiceSettings({});
}

void discord_sdk::accept_join_request(int64_t user_id)
{
    if (result == discord::Result::Ok && app_id > 0)
        core->ActivityManager().SendRequestReply(user_id, static_cast<discord::ActivityJoinRequestReply>(1), {});
}
void discord_sdk::send_invite(int64_t user_id, bool is_spectate = false, String message_content = "")
{
    if (result == discord::Result::Ok && app_id > 0)
        core->ActivityManager().SendInvite(user_id, static_cast<discord::ActivityActionType>(is_spectate + 1), message_content.utf8().get_data(), {});
}
void discord_sdk::accept_invite(int64_t user_id)
{
    if (result == discord::Result::Ok && app_id > 0)
        core->ActivityManager().AcceptInvite(user_id, {});
}

void discord_sdk::register_command(String value)
{
    if (result == discord::Result::Ok && app_id > 0)
        core->ActivityManager().RegisterCommand(value.utf8().get_data());
}
void discord_sdk::register_steam(int32_t value)
{
    if (result == discord::Result::Ok && app_id > 0)
        core->ActivityManager().RegisterSteam(value);
}
Dictionary discord_sdk::get_current_user()
{
    Dictionary userdict;
    if (result == discord::Result::Ok && app_id > 0)
    {
        discord::User user{};
        core->UserManager().GetCurrentUser(&user);
        return user2dict(user);
    }
    return userdict;
}

Dictionary discord_sdk::get_relationship(int64_t user_id)
{
    if (result == discord::Result::Ok && app_id > 0)
    {
        discord::Relationship relationship{};
        core->RelationshipManager().Get(user_id, &relationship);
        return relationship2dict(relationship);
    }
    Dictionary dict;
    return dict;
}

Array discord_sdk::get_all_relationships()
{
    Array all_relationships;
    core->RelationshipManager().Filter(
        [](discord::Relationship const &relationship) -> bool
        { return true; });
    int32_t friendcount{0};
    core->RelationshipManager().Count(&friendcount);
    for (int i = 0; i < friendcount; i++)
    {
        discord::Relationship relationship{};
        core->RelationshipManager().GetAt(i, &relationship);
        all_relationships.append(relationship2dict(relationship));
    }
    return all_relationships;
}

int discord_sdk::get_result_int()
{
    return static_cast<int>(result);
}

Dictionary discord_sdk::user2dict(discord::User user)
{
    Dictionary userdict;
    userdict["avatar"] = user.GetAvatar(); // can be empty when user has no avatar
    userdict["is_bot"] = user.GetBot();
    userdict["discriminator"] = user.GetDiscriminator();
    userdict["id"] = user.GetId();
    userdict["username"] = user.GetUsername();
    if (String(userdict["avatar"]).is_empty())
        userdict["avatar_url"] = String(std::string("https://cdn.discordapp.com/embed/avatars/" + std::to_string((userdict["discriminator"].INT % 5) - 1) + ".png").c_str());
    else
        userdict["avatar_url"] = String(std::string("https://cdn.discordapp.com/avatars/" + std::to_string(user.GetId()) + "/" + user.GetAvatar() + ".png").c_str());
    userdict.make_read_only();
    return userdict;
}

Dictionary discord_sdk::relationship2dict(discord::Relationship relationship)
{
    Dictionary dict_relationship;
    Dictionary presence;
    Dictionary presence_activity;
    switch (static_cast<int>(relationship.GetPresence().GetStatus()))
    {
    case 0:
        presence["status"] = "Offline";
        break;
    case 1:
        presence["status"] = "Online";
        break;
    case 2:
        presence["status"] = "Idle";
        break;
    case 3:
        presence["status"] = "DoNotDisturb";
        break;
    default:
        presence["status"] = "NotAvailable";
        break;
    }
    presence_activity["application_id"] = relationship.GetPresence().GetActivity().GetApplicationId();
    presence_activity["name"] = relationship.GetPresence().GetActivity().GetName();
    presence_activity["state"] = relationship.GetPresence().GetActivity().GetState();
    presence_activity["details"] = relationship.GetPresence().GetActivity().GetDetails();
    presence_activity["large_image"] = relationship.GetPresence().GetActivity().GetAssets().GetLargeImage();
    presence_activity["large_text"] = relationship.GetPresence().GetActivity().GetAssets().GetLargeText();
    presence_activity["small_image"] = relationship.GetPresence().GetActivity().GetAssets().GetSmallImage();
    presence_activity["small_text"] = relationship.GetPresence().GetActivity().GetAssets().GetSmallText();
    presence_activity["timestamps_start"] = relationship.GetPresence().GetActivity().GetTimestamps().GetStart();
    presence_activity["timestamps_end"] = relationship.GetPresence().GetActivity().GetTimestamps().GetEnd();
    presence_activity["instance"] = relationship.GetPresence().GetActivity().GetInstance();
    presence_activity["party_id"] = relationship.GetPresence().GetActivity().GetParty().GetId();
    presence_activity["current_party_size"] = relationship.GetPresence().GetActivity().GetParty().GetSize().GetCurrentSize();
    presence_activity["max_party_size"] = relationship.GetPresence().GetActivity().GetParty().GetSize().GetMaxSize();
    presence_activity["join_secret"] = relationship.GetPresence().GetActivity().GetSecrets().GetJoin();
    presence_activity["spectate_secret"] = relationship.GetPresence().GetActivity().GetSecrets().GetSpectate();
    presence_activity["match_secret"] = relationship.GetPresence().GetActivity().GetSecrets().GetMatch();
    presence["activity"] = presence_activity;
    presence.make_read_only();
    switch (relationship.GetType())
    {
    case discord::RelationshipType::None:
        dict_relationship["type"] = "None";
        break;
    case discord::RelationshipType::Friend:
        dict_relationship["type"] = "Friend";
        break;
    case discord::RelationshipType::Blocked:
        dict_relationship["type"] = "Blocked";
        break;
    case discord::RelationshipType::PendingIncoming:
        dict_relationship["type"] = "PendingIncoming";
        break;
    case discord::RelationshipType::PendingOutgoing:
        dict_relationship["type"] = "PendingOutgoing";
        break;
    case discord::RelationshipType::Implicit:
        dict_relationship["type"] = "Implicit";
        break;
    default:
        dict_relationship["type"] = "NotAvailable";
        break;
    }
    dict_relationship["user"] = user2dict(relationship.GetUser());
    dict_relationship["presence"] = presence;
    dict_relationship.make_read_only();
    return dict_relationship;
}

bool discord_sdk::get_is_discord_working()
{
    return result == discord::Result::Ok && app_id > 0;
}