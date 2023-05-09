@tool
extends EditorPlugin

const ExportPlugin = preload("res://addons/discord-rpc-gd/export.gd")
var loaded_exportplugin = ExportPlugin.new()

func _enter_tree():
	add_export_plugin(loaded_exportplugin)

func disable_plugin():
	remove_export_plugin(loaded_exportplugin)
