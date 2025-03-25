extends DiscordConnector

func _on_user_connected(access_token: String, refresh_token: String, expires_in: int) -> void:
	print_debug("Access token: %s \nRefresh Token: %s \nExpires in: %s" % [access_token, refresh_token, expires_in])

func _on_user_updated() -> void:
	print_debug("USER UPDATED")

func _on_user_connection_failed(error: String) -> void:
	push_error("User connection failed! Error: %s", error)

func _on_user_update_failed(error: String) -> void:
	push_error("User update failed! Error: %s", error)
