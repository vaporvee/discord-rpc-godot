@tool
extends EditorPlugin

const DiscordSDKDebug = preload("res://addons/discord-sdk-gd/nodes/debug.gd")
const DiscordSDKDebug_icon = preload("res://addons/discord-sdk-gd/nodes/assets/Debug.svg")
var loaded_DiscordSDKDebug = DiscordSDKDebug.new()


const ExportPlugin = preload("res://addons/discord-sdk-gd/export.gd")
var loaded_exportplugin = ExportPlugin.new()


func _enter_tree() -> void:
	add_custom_type("DiscordSDKDebug","Node",DiscordSDKDebug,DiscordSDKDebug_icon)
	add_autoload_singleton("DiscordSDKLoader", "res://addons/discord-sdk-gd/nodes/core_updater.gd")
	add_export_plugin(loaded_exportplugin)

func _enable_plugin() -> void:
	print("DiscordSDK Addon got enabled (PLEASE  RESTART THE EDITOR)")
	ProjectSettings.set_setting("DiscordSDK/EditorPresence/enabled",false)
	ProjectSettings.set_initial_value("DiscordSDK/EditorPresence/enabled",false)
	ProjectSettings.set_restart_if_changed("DiscordSDK/EditorPresence/enabled",true)

func _disable_plugin() -> void:
	print("DiscordSDK Addon got disabled")
	remove_autoload_singleton("DiscordSDKLoader")
	remove_custom_type("DiscordSDKDebug")
	ProjectSettings.clear("DiscordSDK/EditorPresence/enabled")

func  _process(_delta):
	if(ProjectSettings.get_setting("DiscordSDK/EditorPresence/enabled")&&!get_editor_interface().is_playing_scene()):
		if(discord_sdk.app_id != 1108142249990176808):
			discord_sdk.app_id = 1108142249990176808
			discord_sdk.details = ProjectSettings.get_setting("application/config/name")
			discord_sdk.state = "Editing: \""+ str(get_tree().edited_scene_root.scene_file_path).replace("res://","") +"\""
			discord_sdk.large_image = "godot"
			discord_sdk.large_image_text = str(Engine.get_version_info().string)
			discord_sdk.start_timestamp = int(Time.get_unix_time_from_system())
			discord_sdk.refresh()
		if(discord_sdk.app_id == 1108142249990176808):
			discord_sdk.coreupdate()
