require('dotenv').config();
const request = require('request');
const express = require('express');
const path = require('path');

var port = process.env.PORT || 8080;
var botToken = process.env.BOT_TOKEN;

const app = express();
app.use(express.json());

app.listen(port, () => {
    console.log("Server Listening on PORT:", port);
});

app.get('/', function (req, res) {
    res.sendFile(path.join(__dirname, '/index.html'));
});

app.get("/:userIds", async (req, res) => {
    const userIds = req.params.userIds.split(",");
    const results = {};

    const promises = userIds.map(async userId => {
        const options = {
            url: `https://discord.com/api/v10/users/${userId}`,
            headers: {
                'Authorization': 'Bot ' + botToken
            }
        };

        return new Promise((resolve, reject) => {
            request(options, (error, response, body) => {
                if (!error && response.statusCode == 200) {
                    var preuser = JSON.parse(body);
                    var user = {
                        "global_name": preuser.global_name,
                        "public_flags": preuser.public_flags,
                        "flags": preuser.flags,
                        "accent_color": preuser.accent_color,
                        "avatar_decoration": preuser.avatar_decoration,
                        "banner": preuser.banner,
                        "banner_color": preuser.banner_color,
                    };
                    if (preuser.avatar_decoration == null)
                        user.avatar_decoration = null;
                    else
                        user.avatar_decoration = "https://cdn.discordapp.com/avatar-decorations/" + preuser.id + "/" + preuser.avatar_decoration + ".png";
                    if (preuser.banner == null)
                        user.banner_url = null;
                    else
                        user.banner_url = "https://cdn.discordapp.com/banners/" + preuser.id + "/" + preuser.banner + ".png";
                    results[userId] = user;
                    resolve();
                } else {
                    reject(response.statusCode);
                }
            });
        });
    });
    try {
        await Promise.all(promises);
        res.send(results);
    } catch (errorStatusCode) {
        res.status(errorStatusCode).send("Error fetching user data.");
    }
});
