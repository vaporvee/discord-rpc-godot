#include "discordpp.h"
#include "discordgodot.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#define BIND_METHOD(method, ...) godot::ClassDB::bind_method(D_METHOD(#method, ##__VA_ARGS__), &DiscordRPC::method)
#define BIND_SET_GET(property_name, variant_type)                                                                  \
    godot::ClassDB::bind_method(D_METHOD("get_" #property_name), &DiscordRPC::get_##property_name);                \
    godot::ClassDB::bind_method(D_METHOD("set_" #property_name, #variant_type), &DiscordRPC::set_##property_name); \
    godot::ClassDB::add_property(get_class_static(), PropertyInfo(variant_type, #property_name), "set_" #property_name, "get_" #property_name)
#define BIND_SIGNAL(signal_name, ...) godot::ClassDB::add_signal(get_class_static(), MethodInfo(#signal_name, ##__VA_ARGS__))
#define SET_GET(variable, setter, ...) /*getter isn't mandatory for this project*/   \
    decltype(DiscordRPC::variable) DiscordRPC::get_##variable() { return variable; } \
    void DiscordRPC::set_##variable(decltype(DiscordRPC::variable) value)            \
    {                                                                                \
        variable = value;                                                            \
        setter;                                                                      \
    }

DiscordRPC *DiscordRPC::singleton = nullptr;

void DiscordRPC::_bind_methods()
{
    BIND_SET_GET(app_id, Variant::INT);
    BIND_SIGNAL(activity_join, PropertyInfo(Variant::STRING, "join_secret"));
    BIND_SIGNAL(activity_spectate, PropertyInfo(Variant::STRING, "spectate_secret"));
    BIND_SIGNAL(activity_join_request, PropertyInfo(Variant::DICTIONARY, "user_requesting"));
    BIND_SIGNAL(updated_relationship, PropertyInfo(Variant::DICTIONARY, "relationship"));
    BIND_SIGNAL(overlay_toggle, PropertyInfo(Variant::BOOL, "is_locked"));
    BIND_SIGNAL(relationships_init);
    BIND_METHOD(debug);
    BIND_METHOD(run_callbacks);
    BIND_METHOD(refresh);
    ClassDB::bind_method(D_METHOD("clear", "reset_values"), &DiscordRPC::clear, DEFVAL(false));
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
}

DiscordRPC::DiscordRPC()
{
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
}

DiscordRPC::~DiscordRPC()
{
    app_id = 0;
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

DiscordRPC *DiscordRPC::get_singleton()
{
    return singleton;
}

void DiscordRPC::run_callbacks()
{
    if (app_id > 0) //result.Successful() &&
        discordpp::RunCallbacks();
}
void DiscordRPC::debug()
{
    auto client = std::make_shared<discordpp::Client>();
}

void DiscordRPC::set_app_id(uint64_t value)
{
    app_id = value;
    if (app_id > 0)
    {
        /*
         result = discordpp::Core::Create(value, DiscordCreateFlags_NoRequireDiscord, &core); // after setting app_ID it initializes everything
         if (result == discordpp::Result::Ok)
         {
             // initialize currentuser
             core->UserManager().OnCurrentUserUpdate.Connect([]()
             {discordpp::User user{};
             core->UserManager().GetCurrentUser(&user); });
             // signals
             core->ActivityManager().OnActivityJoin.Connect([](const char *secret)
             { DiscordRPC::get_singleton()
             ->emit_signal("activity_join", secret); });
             core->ActivityManager().OnActivitySpectate.Connect([](const char *secret)
             { DiscordRPC::get_singleton()
             ->emit_signal("activity_spectate", secret); });
             core->ActivityManager().OnActivityJoinRequest.Connect([this](discordpp::User const &user)
                                                                   { DiscordRPC::get_singleton()
                                                                         ->emit_signal("activity_join_request", user2dict(user)); });
             core->OverlayManager().OnToggle.Connect([](bool is_locked)
             { DiscordRPC::get_singleton()
             ->emit_signal("overlay_toggle", is_locked); });
             core->RelationshipManager().OnRefresh.Connect([&]()
             { DiscordRPC::get_singleton()
             ->emit_signal("relationships_init"); });
             core->RelationshipManager().OnRelationshipUpdate.Connect([&](discordpp::Relationship const &relationship)
             { DiscordRPC::get_singleton()
             ->emit_signal("updated_relationship", relationship2dict(relationship)); });
         }
         */
    }
}
uint64_t DiscordRPC::get_app_id()
{
    if (app_id != 0)
        return app_id;
    return old_app_id;
}

void DiscordRPC::refresh()
{
    if (get_is_discord_working())
    {
        /*activity.GetParty().SetPrivacy(discordpp::ActivityPartyPrivacy::Public);
        activity.SetType(discordpp::ActivityType::Playing);
        core->ActivityManager().UpdateActivity(activity, [](discordpp::Result result) {});*/
        return;
    }
    else
        UtilityFunctions::push_warning("Discord Activity couldn't be updated. It could be that Discord isn't running!");
}

void DiscordRPC::clear(bool reset_values = false)
{
    if (get_is_discord_working())
    {
        if (reset_values)
        {
            old_app_id = 0;
            set_is_overlay_locked(false);
            // core->ActivityManager().ClearActivity([](discordpp::Result result) {});
        }
        else
            old_app_id = app_id;
        app_id = 0;
    }
}

void DiscordRPC::unclear()
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

bool DiscordRPC::get_is_overlay_enabled()
{
    bool ie;
    if (get_is_discord_working()){
        // core->OverlayManager().IsEnabled(&ie);
        return ie;
    }
    return ie;
}
bool DiscordRPC::get_is_overlay_locked()
{
    bool il;
    if (get_is_discord_working())
    {
        // core->OverlayManager().IsLocked(&il);
        return il;
    }
    return il;
}
void DiscordRPC::set_is_overlay_locked(bool value)
{
    is_overlay_locked = value;
    if (get_is_discord_working())
        // core->OverlayManager().SetLocked(value, {});
        return;
}
void DiscordRPC::open_invite_overlay(bool is_spectate)
{
    if (get_is_discord_working())
        // core->OverlayManager().OpenActivityInvite(static_cast<discordpp::ActivityActionType>(is_spectate + 1), {});
        return;
}
void DiscordRPC::open_server_invite_overlay(String invite_code)
{
    if (get_is_discord_working())
        // core->OverlayManager().OpenGuildInvite(invite_code.utf8().get_data(), {});
        return;
}
void DiscordRPC::open_voice_settings()
{
    if (get_is_discord_working())
        // core->OverlayManager().OpenVoiceSettings({});
        return;
}

void DiscordRPC::accept_join_request(uint64_t user_id)
{
    if (get_is_discord_working())
        // core->ActivityManager().SendRequestReply(user_id, static_cast<discordpp::ActivityJoinRequestReply>(1), {});
        return;
}
void DiscordRPC::send_invite(uint64_t user_id, bool is_spectate = false, String message_content = "")
{
    if (get_is_discord_working())
        // core->ActivityManager().SendInvite(user_id, static_cast<discordpp::ActivityActionType>(is_spectate + 1), message_content.utf8().get_data(), {});
        return;
}
void DiscordRPC::accept_invite(uint64_t user_id)
{
    if (get_is_discord_working())
        // core->ActivityManager().AcceptInvite(user_id, {});
        return;
}

void DiscordRPC::register_command(String value)
{
    if (get_is_discord_working())
        // core->ActivityManager().RegisterCommand(value.utf8().get_data());
        return;
}
void DiscordRPC::register_steam(int32_t value)
{
    if (get_is_discord_working())
        // core->ActivityManager().RegisterSteam(value);
        return;
}
Dictionary DiscordRPC::get_current_user()
{
    Dictionary userdict;
    if (get_is_discord_working())
    {
        // discordpp::User user{};
        // core->UserManager().GetCurrentUser(&user);
        return userdict; //user2dict(user)
    }
    return userdict;
}

Dictionary DiscordRPC::get_relationship(uint64_t user_id)
{
    Dictionary dict;
    if (get_is_discord_working())
    {
        // discordpp::Relationship relationship{};
        // core->RelationshipManager().Get(user_id, &relationship);
        return dict /*relationship2dict(relationship)*/;
    }
    return dict;
}

Array DiscordRPC::get_all_relationships()
{
    Array all_relationships;
    /*core->RelationshipManager().Filter(
        [](discordpp::Relationship const &relationship) -> bool
        { return true; });*/
    uint32_t friendcount{0};
    //core->RelationshipManager().Count(&friendcount);
    /*for (int i = 0; i < friendcount; i++)
    {
        discordpp::Relationship relationship{};
        core->RelationshipManager().GetAt(i, &relationship);
        all_relationships.append(relationship2dict(relationship));
    }*/
    return all_relationships;
}

Dictionary DiscordRPC::user2dict(discordpp::UserHandle user)
{
    Dictionary userdict;
    /*userdict["avatar"] = user.GetAvatar(); // can be empty when user has no avatar
    userdict["is_bot"] = user.GetBot();
    userdict["discriminator"] = user.GetDiscriminator();
    userdict["id"] = user.GetId();
    userdict["username"] = user.GetUsername();
    if (String(userdict["avatar"]).is_empty())
        userdict["avatar_url"] = String(std::string("https://cdn.discordapp.com/embed/avatars/" + std::to_string((userdict["discriminator"].INT % 5) - 1) + ".png").c_str());
    else
        userdict["avatar_url"] = String(std::string("https://cdn.discordapp.com/avatars/" + std::to_string(user.GetId()) + "/" + user.GetAvatar() + ".png").c_str());
    userdict.make_read_only();*/
    return userdict;
}

Dictionary DiscordRPC::relationship2dict(discordpp::RelationshipHandle relationship)
{
    Dictionary dict_relationship;
    Dictionary presence;
    Dictionary presence_activity;
    /*switch (static_cast<int>(relationship.GetPresence().GetStatus()))
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
    case discordpp::RelationshipType::None:
        dict_relationship["type"] = "None";
        break;
    case discordpp::RelationshipType::Friend:
        dict_relationship["type"] = "Friend";
        break;
    case discordpp::RelationshipType::Blocked:
        dict_relationship["type"] = "Blocked";
        break;
    case discordpp::RelationshipType::PendingIncoming:
        dict_relationship["type"] = "PendingIncoming";
        break;
    case discordpp::RelationshipType::PendingOutgoing:
        dict_relationship["type"] = "PendingOutgoing";
        break;
    case discordpp::RelationshipType::Implicit:
        dict_relationship["type"] = "Implicit";
        break;
    default:
        dict_relationship["type"] = "NotAvailable";
        break;
    }
    dict_relationship["user"] = user2dict(relationship.GetUser());
    dict_relationship["presence"] = presence;
    dict_relationship.make_read_only();*/
    return dict_relationship;
}

bool DiscordRPC::get_is_discord_working()
{
    return app_id > 0; /*result.Successful() &&*/ 
}