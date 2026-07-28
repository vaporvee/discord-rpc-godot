@tool
extends EditorPlugin

const DiscordRPCDebug: GDScript = preload("res://addons/discord-rpc-gd/nodes/debug.gd")
const DiscordRPCDebug_icon: Texture2D = preload("res://addons/discord-rpc-gd/Debug.svg")
var loaded_DiscordRPCDebug: DiscordRPCDebug = DiscordRPCDebug.new()
var plugin_cfg: ConfigFile = ConfigFile.new()
const plugin_data_filename: String = "/plugin_data.cfg"

func _enter_tree() -> void:
	add_custom_type("DiscordRPCDebug","Node",DiscordRPCDebug,DiscordRPCDebug_icon)
	get_editor_interface().get_editor_settings().settings_changed.connect(_on_editor_settings_changed)

func _ready() -> void:
	await get_tree().create_timer(0.5).timeout
	plugin_cfg.load(get_editor_interface().get_editor_paths().get_data_dir() + plugin_data_filename)
	if !get_editor_interface().get_editor_settings().has_setting("DiscordRPC/EditorPresence/enabled"):
		get_editor_interface().get_editor_settings().set_setting("DiscordRPC/EditorPresence/enabled",plugin_cfg.get_value("Discord","editor_presence",false))

func _exit_tree() -> void:
	if get_editor_interface().get_editor_settings().has_setting("DiscordRPC/EditorPresence/enabled"):
		get_editor_interface().get_editor_settings().erase("DiscordRPC/EditorPresence/enabled")

func _enable_plugin() -> void:
	add_autoload_singleton("DiscordRPCLoader","res://addons/discord-rpc-gd/nodes/discord_autoload.gd")
	get_editor_interface().get_resource_filesystem().scan()

func _disable_plugin() -> void:
	remove_autoload_singleton("DiscordRPCLoader")
	remove_custom_type("DiscordRPCDebug")
	get_editor_interface().get_editor_settings().erase("DiscordRPC/EditorPresence/enabled")
	editor_presence_active = false
	get_editor_interface().get_resource_filesystem().scan()

var editor_presence_active: bool = false

func _process(_delta: float) -> void:
	if not editor_presence_active:
		return
	var edited_scene_path: String = ""
	var edited_scene_root: Node = get_editor_interface().get_edited_scene_root()
	if edited_scene_root != null:
		edited_scene_path = edited_scene_root.scene_file_path
	Engine.get_singleton("EditorPresence").tick(edited_scene_path)

func _on_editor_settings_changed() -> void:
	plugin_cfg.set_value("Discord","editor_presence",get_editor_interface().get_editor_settings().get_setting("DiscordRPC/EditorPresence/enabled"))
	plugin_cfg.save(get_editor_interface().get_editor_paths().get_data_dir() + plugin_data_filename)
	var should_be_active: bool = get_editor_interface().get_editor_settings().has_setting("DiscordRPC/EditorPresence/enabled") && get_editor_interface().get_editor_settings().get_setting("DiscordRPC/EditorPresence/enabled")
	if should_be_active and not editor_presence_active:
		Engine.get_singleton("EditorPresence").start()
	elif not should_be_active and editor_presence_active:
		Engine.get_singleton("EditorPresence").stop()
	editor_presence_active = should_be_active
