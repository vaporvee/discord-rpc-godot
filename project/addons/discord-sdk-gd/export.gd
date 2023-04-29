@tool
extends  EditorExportPlugin

func _export_file(path, type, features):
	if features[2] == "windows":
		add_shared_object("res://addons/discord-sdk-gd/bin/windows/discord_game_sdk.dll",[],"/")
	elif features[2] == "linux":
		add_shared_object("res://addons/discord-sdk-gd/bin/linux/libdiscord_game_sdk.so",[],"/")
	elif features[2] == "macos":
		add_shared_object("res://addons/discord-sdk-gd/bin/macos/libdiscord_game_sdk.dylib",[],"/")
