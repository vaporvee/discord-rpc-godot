@tool
extends  EditorExportPlugin

func _export_file(_path, _type, features) -> void:
    if features.find("windows",0) != -1:
        if features.find("x86_64",0) != -1:
            add_shared_object("res://addons/discord-sdk-gd/bin/windows/discord_game_sdk.dll",[],"/")
        elif features.find("x86",0) != -1:
            add_shared_object("res://addons/discord-sdk-gd/bin/windows/discord_game_sdk_x86.dll",[],"/")
    elif features.find("linux",0) != -1:
        add_shared_object("res://addons/discord-sdk-gd/bin/linux/libdiscord_game_sdk.so",[],"/")
    elif features.find("macos",0) != -1:
        add_shared_object("res://addons/discord-sdk-gd/bin/macos/libdiscord_game_sdk.dylib",[],"/")
        add_shared_object("res://addons/discord-sdk-gd/bin/macos/libdiscord_game_sdk_aarch64.dylib",[],"/")

func _get_name():
    pass
