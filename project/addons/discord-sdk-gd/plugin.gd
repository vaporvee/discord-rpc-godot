@tool
extends EditorPlugin

const ExportPlugin = preload("export.gd")
var loaded_exportplugin = ExportPlugin.new()

func _enter_tree():
	add_autoload_singleton("updater_discordsdk", "res://addons/discord-sdk-gd/sdk_utility.gd")
	add_export_plugin(loaded_exportplugin)

func disable_plugin():
	remove_autoload_singleton("updater_discordsdk")
	remove_export_plugin(loaded_exportplugin)
