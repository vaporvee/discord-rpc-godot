@tool
extends EditorPlugin

const DiscordSDKDebug = preload("res://addons/discord-sdk-gd/nodes/debug.gd")
const DiscordSDKDebug_icon = preload("res://addons/discord-sdk-gd/Debug.svg")
var loaded_DiscordSDKDebug = DiscordSDKDebug.new()
var restart_window: Control = preload("res://addons/discord-sdk-gd/restart_window.tscn").instantiate()



func _enter_tree() -> void:
	add_custom_type("DiscordSDKDebug","Node",DiscordSDKDebug,DiscordSDKDebug_icon)
	ProjectSettings.set_setting("DiscordSDK/EditorPresence/enabled",false)
	ProjectSettings.set_as_basic("DiscordSDK/EditorPresence/enabled",true)
	ProjectSettings.set_initial_value("DiscordSDK/EditorPresence/enabled",false)

func _enable_plugin() -> void:
	add_autoload_singleton("DiscordSDKAutoload","res://addons/discord-sdk-gd/nodes/discord_autoload.gd")
	if FileAccess.file_exists(ProjectSettings.globalize_path("res://") + "addons/discord-sdk-gd/bin/.gdignore"):
		DirAccess.remove_absolute(ProjectSettings.globalize_path("res://") + "addons/discord-sdk-gd/bin/.gdignore")
	if FileAccess.file_exists(ProjectSettings.globalize_path("res://") + "addons/discord-sdk-gd/nodes/.gdignore"):
		DirAccess.remove_absolute(ProjectSettings.globalize_path("res://") + "addons/discord-sdk-gd/nodes/.gdignore")

func _disable_plugin() -> void:
	remove_autoload_singleton("DiscordSDKAutoload")
	FileAccess.open("res://addons/discord-sdk-gd/bin/.gdignore",FileAccess.WRITE)
	FileAccess.open("res://addons/discord-sdk-gd/nodes/.gdignore",FileAccess.WRITE)
	remove_custom_type("DiscordSDKDebug")
	ProjectSettings.clear("DiscordSDK/EditorPresence/enabled")
