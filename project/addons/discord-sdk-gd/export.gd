@tool
extends  EditorExportPlugin

func _export_file(_path, _type, features) -> void:
	if features[2] == "windows":
		if features[4] == "x86_64":
			add_shared_object("res://addons/discord-sdk-gd/bin/windows/discord_game_sdk.dll",[],"/")
		elif features[4] == "x86":
			add_shared_object("res://addons/discord-sdk-gd/bin/windows/discord_game_sdk_x86.dll",[],"/")
	elif features[2] == "linux":
		add_shared_object("res://addons/discord-sdk-gd/bin/linux/libdiscord_game_sdk.so",[],"/")
	elif features[2] == "macos":
		add_shared_object("res://addons/discord-sdk-gd/bin/macos/libdiscord_game_sdk.dylib",[],"/")
		add_shared_object("res://addons/discord-sdk-gd/bin/macos/libdiscord_game_sdk_aarch64.dylib",[],"/")

func _get_name():
	pass
