extends DiscordConnector

func _on_user_connected(access_token: String, refresh_token: String, expires_in: int) -> void:
	print_debug("Access token: %s \nRefresh Token: %s \nExpires in: %s" % [access_token, refresh_token, expires_in])
