extends DiscordConnector

@onready var discord_activity: DiscordActivity = $DiscordActivity

func _on_authenticated(access_token: String, refresh_token: String, expires_in: int) -> void:
	print_debug("Access token: %s \nRefresh Token: %s \nExpires in: %s" % [access_token, refresh_token, expires_in])

func _on_authentication_failed(error: String) -> void:
	push_error("Auth failed! Error: " + error)

func _on_connection_error(error: String) -> void:
	push_error(error)

func _on_connection_ready() -> void:
	print_debug("CONNECTION READY")
	discord_activity.update()
