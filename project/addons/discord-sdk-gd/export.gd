@tool
extends  EditorExportPlugin

func _export_file(path, type, features):
	if path[2] == "windows":
		add_shared_object("res://addons/discord-sdk-gd/bin/windows/discord_game_sdk.dll",[],"/")
	elif path[2] == "linux":
		add_shared_object("res://addons/discord-sdk-gd/bin/linux/discord_game_sdk.so",[],"/")
	elif path[2] == "macos":
		add_shared_object("res://addons/discord-sdk-gd/bin/macos/discord_game_sdk.dylib",[],"/")
