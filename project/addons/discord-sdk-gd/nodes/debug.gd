## This is a Debug Node wich will show (only if the project runs) some usefull info and buttons/input
extends Node

const DebugNodeGroup = preload("res://addons/discord-sdk-gd/nodes/Debug.tscn")

func _ready():
	add_child(DebugNodeGroup.instantiate())
