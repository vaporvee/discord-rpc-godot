@tool
extends EditorPlugin

const DiscordSocialSDKDebug: GDScript = preload("res://addons/discord-rpc-gd/nodes/debug.gd")
const DiscordSocialSDKDebug_icon: Texture2D = preload("res://addons/discord-rpc-gd/Debug.svg")
var loaded_DiscordSocialSDKDebug: DiscordSocialSDKDebug = DiscordSocialSDKDebug.new()
var restart_window: ConfirmationDialog = preload("res://addons/discord-rpc-gd/restart_window.tscn").instantiate()
var plugin_cfg: ConfigFile = ConfigFile.new()
const plugin_data_filename: String = "/plugin_data.cfg"

func _ready() -> void:
	await get_tree().create_timer(0.5).timeout
	plugin_cfg.load(get_editor_interface().get_editor_paths().get_data_dir() + plugin_data_filename)
	if !get_editor_interface().get_editor_settings().has_setting("DiscordSocialSDK/EditorPresence/enabled"):
		get_editor_interface().get_editor_settings().set_setting("DiscordSocialSDK/EditorPresence/enabled",plugin_cfg.get_value("Discord","editor_presence",false))

func _enter_tree() -> void:
	add_custom_type("DiscordSocialSDKDebug","Node",DiscordSocialSDKDebug,DiscordSocialSDKDebug_icon)
	get_editor_interface().get_editor_settings().settings_changed.connect(_on_editor_settings_changed)

func _exit_tree() -> void:
	if get_editor_interface().get_editor_settings().has_setting("DiscordSocialSDK/EditorPresence/enabled"):
		get_editor_interface().get_editor_settings().erase("DiscordSocialSDK/EditorPresence/enabled")

func _enable_plugin() -> void:
	add_custom_type("DiscordSocialSDKDebug","Node",DiscordSocialSDKDebug,DiscordSocialSDKDebug_icon)
	get_editor_interface().get_editor_settings().settings_changed.connect(_on_editor_settings_changed)
	if FileAccess.file_exists(ProjectSettings.globalize_path("res://") + "addons/discord-rpc-gd/bin/.gdignore"):
		DirAccess.remove_absolute(ProjectSettings.globalize_path("res://") + "addons/discord-rpc-gd/bin/.gdignore")
	restart_window.connect("confirmed", save_no_restart)
	restart_window.connect("canceled", save_and_restart)
	get_editor_interface().popup_dialog_centered(restart_window)
	print("IGNORE RED ERROR MESSAGES BEFORE THE SECOND RESTART!")

func _disable_plugin() -> void:
	remove_autoload_singleton("DiscordUtilLoader")
	FileAccess.open("res://addons/discord-rpc-gd/bin/.gdignore",FileAccess.WRITE)
	remove_custom_type("DiscordSocialSDKDebug")
	get_editor_interface().get_editor_settings().erase("DiscordSocialSDK/EditorPresence/enabled")
	push_warning("Please restart the editor to fully disable the DiscordUtil plugin")

func save_and_restart() -> void:
	get_editor_interface().restart_editor(true)

func save_no_restart() -> void:
	get_editor_interface().restart_editor(false)
	
var editor_presence: Node
func _on_editor_settings_changed() -> void:
	plugin_cfg.set_value("Discord","editor_presence",get_editor_interface().get_editor_settings().get_setting("DiscordSocialSDK/EditorPresence/enabled"))
	plugin_cfg.save(get_editor_interface().get_editor_paths().get_data_dir() + plugin_data_filename)
	if ClassDB.class_exists("EditorPresence") && editor_presence == null:
		editor_presence = ClassDB.instantiate("EditorPresence")
	if get_editor_interface().get_editor_settings().has_setting("DiscordSocialSDK/EditorPresence/enabled") && get_editor_interface().get_editor_settings().get_setting("DiscordSocialSDK/EditorPresence/enabled"):
		add_child(editor_presence)
	else:
		editor_presence.queue_free()
