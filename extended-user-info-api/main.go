package main

import (
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"os"
	"strings"

	"github.com/gin-gonic/gin"
	"github.com/joho/godotenv"
)

func main() {
	r := gin.Default()
	r.GET("/*userID", func(c *gin.Context) {
		if c.Param("userID") == "/" {
			c.Writer.WriteHeader(http.StatusOK)
			c.Writer.Write([]byte("<html><body>Please provide a Discord user id after the slash. <a href=\"https://github.com/vaporvee/discord-sdk-godot/\">GitHub project</a></body></html>"))
			return
		} else {
			godotenv.Load()
			bot_token := os.Getenv("BOT_TOKEN")
			var params string
			params = strings.TrimLeft(c.Param("userID"), "/")
			client := &http.Client{}
			req, err := http.NewRequest("GET", "https://discord.com/api/v10/users/"+params, nil)
			if err != nil {
				fmt.Println("Error creating HTTP request:", err)
				return
			}
			req.Header.Add("Authorization", "Bot "+bot_token)
			req.Header.Add("Content-Type", "application/json")
			res, err := client.Do(req)
			if err != nil {
				fmt.Println("Error sending HTTP request:", err)
				return
			}
			body, err := io.ReadAll(res.Body)
			if err != nil {
				fmt.Println("Error reading HTTP response body:", err)
				return
			}
			var jsonMap map[string]interface{}
			json.Unmarshal([]byte(string(body)), &jsonMap)
			c.JSON(http.StatusOK, jsonMap)
		}
	})
	r.Run()
}
