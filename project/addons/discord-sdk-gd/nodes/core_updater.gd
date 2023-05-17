## [color=yellow]PLEASE IGNORE![/color] This is a important Node wich gets automatically added as Singleton.
## 
## The DiscordSDKLoader Node automatically gets added as Singleton while installing the addon.
## It has to run in the background to comunicate with Discord.
## You don't need to use it.
##
## @tutorial: https://github.com/vaporvee/discord-sdk-godot/wiki
class_name core_updater
extends Node

func _process(delta) -> void:
	discord_sdk.coreupdate()
