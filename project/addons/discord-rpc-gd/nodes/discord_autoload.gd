## This is a GDscript Node wich gets automatically added as Autoload while installing the addon.
## 
## It can run in the background to comunicate with Discord.
## You don't need to use it. If you remove it make sure to run [code]Engine.get_singleton("DiscordRPC").run_callbacks()[/code] in a [code]_process[/code] function.
##
## @tutorial: https://github.com/vaporvee/discord-rpc-godot/wiki
extends Node

@onready var discord_rpc: Object = Engine.get_singleton("DiscordRPC")

func _ready() -> void:
	pass

func  _process(_delta) -> void:
	discord_rpc.run_callbacks()
