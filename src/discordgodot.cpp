#include "discordgodot.h"
#include "lib/discord_game_sdk/cpp/discord.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/time.hpp>

using namespace godot;

discord_sdk *discord_sdk::singleton = nullptr;

discord::Core *core{};
discord::Result result;
discord::Activity activity{};
discord::User user{};

void discord_sdk::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("debug"), &discord_sdk::debug);
    ClassDB::bind_method(D_METHOD("coreupdate"), &discord_sdk::coreupdate);

    ClassDB::bind_method(D_METHOD("get_app_id"), &discord_sdk::get_app_id);
    ClassDB::bind_method(D_METHOD("set_app_id", "app_id"), &discord_sdk::set_app_id);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "app_id"), "set_app_id", "get_app_id");
    ClassDB::bind_method(D_METHOD("get_state"), &discord_sdk::get_state);
    ClassDB::bind_method(D_METHOD("set_state", "state"), &discord_sdk::set_state);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "state"), "set_state", "get_state");
    ClassDB::bind_method(D_METHOD("get_details"), &discord_sdk::get_details);
    ClassDB::bind_method(D_METHOD("set_details", "details"), &discord_sdk::set_details);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "details"), "set_details", "get_details");

    ClassDB::bind_method(D_METHOD("get_large_image"), &discord_sdk::get_large_image);
    ClassDB::bind_method(D_METHOD("set_large_image", "large_image"), &discord_sdk::set_large_image);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "large_image"), "set_large_image", "get_large_image");
    ClassDB::bind_method(D_METHOD("get_large_image_text"), &discord_sdk::get_large_image_text);
    ClassDB::bind_method(D_METHOD("set_large_image_text", "large_image_text"), &discord_sdk::set_large_image_text);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "large_image_text"), "set_large_image_text", "get_large_image_text");
    ClassDB::bind_method(D_METHOD("get_small_image"), &discord_sdk::get_small_image);
    ClassDB::bind_method(D_METHOD("set_small_image", "small_image"), &discord_sdk::set_small_image);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "small_image"), "set_small_image", "get_small_image");
    ClassDB::bind_method(D_METHOD("get_small_image_text"), &discord_sdk::get_small_image_text);
    ClassDB::bind_method(D_METHOD("set_small_image_text", "large_small_text"), &discord_sdk::set_small_image_text);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "small_image_text"), "set_small_image_text", "get_small_image_text");

    ClassDB::bind_method(D_METHOD("get_start_timestamp"), &discord_sdk::get_start_timestamp);
    ClassDB::bind_method(D_METHOD("set_start_timestamp", "start_timestamp"), &discord_sdk::set_start_timestamp);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "start_timestamp"), "set_start_timestamp", "get_start_timestamp");
    ClassDB::bind_method(D_METHOD("get_end_timestamp"), &discord_sdk::get_end_timestamp);
    ClassDB::bind_method(D_METHOD("set_end_timestamp", "end_timestamp"), &discord_sdk::set_end_timestamp);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "end_timestamp"), "set_end_timestamp", "get_end_timestamp");

    ClassDB::bind_method(D_METHOD("get_party_id"), &discord_sdk::get_party_id);

    ClassDB::bind_method(D_METHOD("set_party_id", "party_id"), &discord_sdk::set_party_id);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "party_id"), "set_party_id", "get_party_id");

    ClassDB::bind_method(D_METHOD("get_current_party_size"), &discord_sdk::get_current_party_size);
    ClassDB::bind_method(D_METHOD("set_current_party_size", "current_party_size"), &discord_sdk::set_current_party_size);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "current_party_size"), "set_current_party_size", "get_current_party_size");
    ClassDB::bind_method(D_METHOD("get_max_party_size"), &discord_sdk::get_max_party_size);
    ClassDB::bind_method(D_METHOD("set_max_party_size", "max_party_size"), &discord_sdk::set_max_party_size);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "max_party_size"), "set_max_party_size", "get_max_party_size");

    ClassDB::bind_method(D_METHOD("get_match_secret"), &discord_sdk::get_match_secret);
    ClassDB::bind_method(D_METHOD("set_match_secret", "match_secret"), &discord_sdk::set_match_secret);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "match_secret"), "set_match_secret", "get_match_secret");
    ClassDB::bind_method(D_METHOD("get_join_secret"), &discord_sdk::get_join_secret);
    ClassDB::bind_method(D_METHOD("set_join_secret", "join_secret"), &discord_sdk::set_join_secret);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "join_secret"), "set_join_secret", "get_join_secret");
    ClassDB::bind_method(D_METHOD("get_spectate_secret"), &discord_sdk::get_spectate_secret);
    ClassDB::bind_method(D_METHOD("set_spectate_secret", "spectate_secret"), &discord_sdk::set_spectate_secret);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "spectate_secret"), "set_spectate_secret", "get_spectate_secret");

    ClassDB::bind_method(D_METHOD("get_instanced"), &discord_sdk::get_instanced);
    ClassDB::bind_method(D_METHOD("set_instanced", "instanced"), &discord_sdk::set_instanced);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "instanced"), "set_instanced", "get_instanced");

    ClassDB::bind_method(D_METHOD("get_is_public_party"), &discord_sdk::get_is_public_party);
    ClassDB::bind_method(D_METHOD("set_is_public_party", "is_public_party"), &discord_sdk::set_is_public_party);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_public_party"), "set_is_public_party", "get_is_public_party");

    ADD_SIGNAL(MethodInfo("activity_join", PropertyInfo(Variant::STRING, "join_secret")));
    ADD_SIGNAL(MethodInfo("activity_spectate", PropertyInfo(Variant::STRING, "spectate_secret")));
    ADD_SIGNAL(MethodInfo("activity_join_request", PropertyInfo(Variant::DICTIONARY, "user_requesting")));

    ADD_SIGNAL(MethodInfo("relationships_init"));
    ADD_SIGNAL(MethodInfo("updated_relationship", PropertyInfo(Variant::DICTIONARY, "relationship")));

    ClassDB::bind_method(D_METHOD("refresh"), &discord_sdk::refresh);
    ClassDB::bind_method(D_METHOD("clear", "reset_values"), &discord_sdk::clear, DEFVAL(false));
    ClassDB::bind_method(D_METHOD("unclear"), &discord_sdk::unclear);

    ClassDB::bind_method(D_METHOD("register_command", "command"), &discord_sdk::register_command);
    ClassDB::bind_method(D_METHOD("register_steam", "steam_id"), &discord_sdk::register_steam);

    ClassDB::bind_method(D_METHOD("accept_join_request", "user_id"), &discord_sdk::accept_join_request);
    ClassDB::bind_method(D_METHOD("send_invite", "user_id", "is_spectate", "message_content"), &discord_sdk::send_invite);
    ClassDB::bind_method(D_METHOD("accept_invite", "user_id"), &discord_sdk::accept_invite);

    ClassDB::bind_method(D_METHOD("get_current_user"), &discord_sdk::get_current_user);
    ClassDB::bind_method(D_METHOD("get_all_relationships"), &discord_sdk::get_all_relationships);

    ClassDB::bind_method(D_METHOD("get_is_overlay_enabled"), &discord_sdk::get_is_overlay_enabled);
    ClassDB::bind_method(D_METHOD("get_is_overlay_locked"), &discord_sdk::get_is_overlay_locked);
    ClassDB::bind_method(D_METHOD("set_is_overlay_locked", "is_overlay_locked"), &discord_sdk::set_is_overlay_locked);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_overlay_locked"), "set_is_overlay_locked", "get_is_overlay_locked");
    ClassDB::bind_method(D_METHOD("open_invite_overlay", "is_spectate"), &discord_sdk::open_invite_overlay);
    ClassDB::bind_method(D_METHOD("open_server_invite_overlay", "invite_code"), &discord_sdk::open_server_invite_overlay);
    ClassDB::bind_method(D_METHOD("open_voice_settings"), &discord_sdk::open_voice_settings);
    ADD_SIGNAL(MethodInfo("overlay_toggle", PropertyInfo(Variant::BOOL, "is_locked")));

    ClassDB::bind_method(D_METHOD("get_is_discord_working"), &discord_sdk::get_is_discord_working);

    ClassDB::bind_method(D_METHOD("get_result_int"), &discord_sdk::get_result_int);
}

discord_sdk *discord_sdk::get_singleton()
{
    return singleton;
}

discord_sdk::discord_sdk()
{
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
}

discord_sdk::~discord_sdk()
{
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
    delete core;
    core = nullptr;
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
            // initialize currentuser stuff
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

void discord_sdk::set_state(String value)
{
    state = value;
    activity.SetState(value.utf8().get_data());
}
String discord_sdk::get_state()
{
    return state;
}
void discord_sdk::set_details(String value)
{
    details = value;
    activity.SetDetails(value.utf8().get_data());
}
String discord_sdk::get_details()
{
    return details;
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

void discord_sdk::set_large_image(String value)
{
    large_image = value;
    activity.GetAssets().SetLargeImage(value.utf8().get_data());
}
String discord_sdk::get_large_image()
{
    return large_image;
}
void discord_sdk::set_large_image_text(String value)
{
    large_image_text = value;
    activity.GetAssets().SetLargeText(value.utf8().get_data());
}
String discord_sdk::get_large_image_text()
{
    return large_image_text;
}
void discord_sdk::set_small_image(String value)
{
    small_image = value;
    activity.GetAssets().SetSmallImage(value.utf8().get_data());
}
String discord_sdk::get_small_image()
{
    return small_image;
}
void discord_sdk::set_small_image_text(String value)
{
    small_image_text = value;
    activity.GetAssets().SetSmallText(value.utf8().get_data());
}
String discord_sdk::get_small_image_text()
{
    return small_image_text;
}

void discord_sdk::set_start_timestamp(int64_t value)
{
    start_timestamp = value;
    activity.GetTimestamps().SetStart(value);
}
int64_t discord_sdk::get_start_timestamp()
{
    return activity.GetTimestamps().GetStart();
}
void discord_sdk::set_end_timestamp(int64_t value)
{
    end_timestamp = value;
    activity.GetTimestamps().SetEnd(value);
}
int64_t discord_sdk::get_end_timestamp()
{
    return activity.GetTimestamps().GetEnd();
}

void discord_sdk::set_party_id(String value)
{
    party_id = value;
    activity.GetParty().SetId(value.utf8().get_data());
}
String discord_sdk::get_party_id()
{
    return party_id;
}

void discord_sdk::set_current_party_size(int32_t value)
{
    current_party_size = value;
    activity.GetParty().GetSize().SetCurrentSize(value);
}
int32_t discord_sdk::get_current_party_size()
{
    return current_party_size;
}
void discord_sdk::set_max_party_size(int32_t value)
{
    max_party_size = value;
    activity.GetParty().GetSize().SetMaxSize(value);
}
int32_t discord_sdk::get_max_party_size()
{
    return max_party_size;
}

void discord_sdk::set_match_secret(String value)
{
    match_secret = value;
    activity.GetSecrets().SetMatch(value.utf8().get_data());
}
String discord_sdk::get_match_secret()
{
    return match_secret;
}
void discord_sdk::set_join_secret(String value)
{
    join_secret = value;
    activity.GetSecrets().SetJoin(value.utf8().get_data());
}
String discord_sdk::get_join_secret()
{
    return join_secret;
}
void discord_sdk::set_spectate_secret(String value)
{
    spectate_secret = value;
    activity.GetSecrets().SetSpectate(value.utf8().get_data());
}
String discord_sdk::get_spectate_secret()
{
    return spectate_secret;
}

void discord_sdk::set_instanced(bool value)
{
    instanced = value;
    activity.SetInstance(value);
}
bool discord_sdk::get_instanced()
{
    return instanced;
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

void discord_sdk::set_is_public_party(bool value)
{
    is_public_party = value;
    activity.GetParty().SetPrivacy(static_cast<discord::ActivityPartyPrivacy>(value)); // normaly true
}
bool discord_sdk::get_is_public_party()
{
    return is_public_party;
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

bool discord_sdk::get_is_discord_working()
{
    return result == discord::Result::Ok && app_id > 0;
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