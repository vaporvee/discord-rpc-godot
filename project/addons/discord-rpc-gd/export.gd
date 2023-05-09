@tool
extends  EditorExportPlugin

func _export_file(path, type, features):
	if features[2] == "windows":
		if features[4] == "x86_64":
			add_shared_object("res://addons/discord-sdk-gd/bin/windows/discord-rpc.dll",[],"/")
		elif features[4] == "x86":
			add_shared_object("res://addons/discord-sdk-gd/bin/windows/discord-rpc_x86.dll",[],"/")
	elif features[2] == "linux":
		add_shared_object("res://addons/discord-sdk-gd/bin/linux/libdiscord-rpc.so",[],"/")
	elif features[2] == "macos":
		add_shared_object("res://addons/discord-sdk-gd/bin/macos/libdiscord-rpc.dylib",[],"/")
