@tool
extends EditorPlugin

const ExportPlugin = preload("res://addons/discord-sdk-gd/export.gd")
var loaded_exportplugin = ExportPlugin.new()

func _enter_tree():
	add_autoload_singleton("discord_coreupdater", "res://addons/discord-sdk-gd/discord_coreupdater.gd")
	add_export_plugin(loaded_exportplugin)

func disable_plugin():
	remove_autoload_singleton("discord_coreupdater")
	remove_export_plugin(loaded_exportplugin)
