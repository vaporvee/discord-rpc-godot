@tool
extends EditorPlugin

func _enter_tree():
	add_autoload_singleton("Discord", "res://addons/discord-rpc-gd/loadaddon.gd")

func disable_plugin():
	remove_autoload_singleton("Discord")
