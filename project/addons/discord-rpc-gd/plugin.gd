@tool
extends EditorPlugin

func _enter_tree():
	add_autoload_singleton("discord_coreupdater", "res://addons/discord-rpc-gd/discord_coreupdater.gd")
	

func disable_plugin():
	remove_autoload_singleton("discord_coreupdater")
