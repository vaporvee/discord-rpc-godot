@tool
extends EditorPlugin

const DiscordSDKLoader = preload("res://addons/discord-sdk-gd/nodes/core_updater.gd")
const DiscordSDKLoader_icon = preload("res://addons/discord-sdk-gd/nodes/assets/Group_1.svg")
var loaded_DiscordSDKLoader = DiscordSDKLoader.new()

const DiscordSDKDebug = preload("res://addons/discord-sdk-gd/nodes/debug.gd")
const DiscordSDKDebug_icon = preload("res://addons/discord-sdk-gd/nodes/assets/Debug.svg")
var loaded_DiscordSDKDebug = DiscordSDKDebug.new()


const ExportPlugin = preload("res://addons/discord-sdk-gd/export.gd")
var loaded_exportplugin = ExportPlugin.new()


func _enter_tree():
	add_custom_type("DiscordSDKLoader","Node",DiscordSDKLoader,DiscordSDKLoader_icon)
	add_custom_type("DiscordSDKDebug","Node",DiscordSDKDebug,DiscordSDKDebug_icon)
	add_autoload_singleton("DiscordSDKLoader", "res://addons/discord-sdk-gd/nodes/DiscordSDKLoader.tscn")
	add_export_plugin(loaded_exportplugin)
	
func disable_plugin():
	remove_custom_type("DiscordSDKLoader")
	remove_custom_type("DiscordSDKDebug")
	remove_autoload_singleton("DiscordSDKLoader")
	remove_export_plugin(loaded_exportplugin)
