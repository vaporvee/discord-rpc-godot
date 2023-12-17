## This is a GDscript Node wich gets automatically added as Autoload while installing the addon.
## 
## It can run in the background to comunicate with Discord.
## You don't need to use it unless you are using EditorPresence. If you remove it make sure to run [code]DiscordSDK.run_callbacks()[/code] in a [code]_process[/code] function.
##
## @tutorial: https://github.com/vaporvee/discord-sdk-godot/wiki
@tool
extends Node

func  _process(_delta) -> void:
	if GDExtensionManager.get_loaded_extensions().has("res://addons/discord-sdk-gd/bin/discord-rpc-gd.gdextension"):
		if ProjectSettings.get_setting("DiscordSDK/EditorPresence/enabled",false) && Engine.is_editor_hint():
			if DiscordSDK.app_id != 1108142249990176808:
				DiscordSDK.app_id = 1108142249990176808
				DiscordSDK.details = ProjectSettings.get_setting("application/config/name")
				DiscordSDK.state = "Editing: \""+ str(get_tree().edited_scene_root.scene_file_path).replace("res://","") +"\""
				DiscordSDK.large_image = "godot"
				DiscordSDK.large_image_text = str(Engine.get_version_info().string)
				DiscordSDK.start_timestamp = int(Time.get_unix_time_from_system())
				DiscordSDK.refresh()
		if DiscordSDK.app_id == 1108142249990176808 || !Engine.is_editor_hint():
			DiscordSDK.run_callbacks()
