@tool
extends EditorPlugin

const DiscordSDKDebug = preload("res://addons/discord-sdk-gd/nodes/debug.gd")
const DiscordSDKDebug_icon = preload("res://addons/discord-sdk-gd/Debug.svg")
var loaded_DiscordSDKDebug = DiscordSDKDebug.new()
var restart_window: ConfirmationDialog = preload("res://addons/discord-sdk-gd/restart_window.tscn").instantiate()

func _enter_tree() -> void:
	add_custom_type("DiscordSDKDebug","Node",DiscordSDKDebug,DiscordSDKDebug_icon)
	ProjectSettings.set_setting("DiscordSDK/EditorPresence/enabled",false)
	ProjectSettings.set_as_basic("DiscordSDK/EditorPresence/enabled",true)
	ProjectSettings.set_initial_value("DiscordSDK/EditorPresence/enabled",false)

func _enable_plugin() -> void:
	if FileAccess.file_exists(ProjectSettings.globalize_path("res://") + "addons/discord-sdk-gd/bin/.gdignore"):
		DirAccess.remove_absolute(ProjectSettings.globalize_path("res://") + "addons/discord-sdk-gd/bin/.gdignore")
	if FileAccess.file_exists(ProjectSettings.globalize_path("res://") + "addons/discord-sdk-gd/nodes/.gdignore"):
		DirAccess.remove_absolute(ProjectSettings.globalize_path("res://") + "addons/discord-sdk-gd/nodes/.gdignore")
	add_autoload_singleton("DiscordSDKAutoload","res://addons/discord-sdk-gd/nodes/discord_autoload.gd")
	restart_window.connect("confirmed", save_no_restart)
	restart_window.connect("canceled", save_and_restart)
	EditorInterface.popup_dialog_centered(restart_window)

func _disable_plugin() -> void:
	GDExtensionManager.unload_extension("res://addons/discord-sdk-gd/bin/discord-rpc-gd.gdextension")
	remove_autoload_singleton("DiscordSDKAutoload")
	FileAccess.open("res://addons/discord-sdk-gd/bin/.gdignore",FileAccess.WRITE)
	FileAccess.open("res://addons/discord-sdk-gd/nodes/.gdignore",FileAccess.WRITE)
	remove_custom_type("DiscordSDKDebug")
	ProjectSettings.clear("DiscordSDK/EditorPresence/enabled")

func save_and_restart() -> void:
	EditorInterface.save_all_scenes()
	EditorInterface.restart_editor(true)

func save_no_restart() -> void:
	EditorInterface.restart_editor(false)
