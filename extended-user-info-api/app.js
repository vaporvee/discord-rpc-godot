require('dotenv').config();
const express = require('express');
const axios = require('axios');
const path = require('path');

const port = process.env.PORT || 8080;
const botToken = process.env.BOT_TOKEN;

const app = express();
app.use(express.json());

app.listen(port, () => {
    console.log("Server Listening on PORT:", port);
});

app.get('/', function (req, res) {
    res.sendFile(path.join(__dirname, '/index.html'));
});

const userCache = {};

const delay = ms => new Promise(resolve => setTimeout(resolve, ms));

async function fetchUserDataWithRetry(userId) {
    let retries = 0;
    let delayTime = 1000;

    while (retries < 3) {
        try {
            const response = await axios.get(`https://discord.com/api/v10/users/${userId}`, {
                headers: {
                    'Authorization': 'Bot ' + botToken
                }
            });
            return response.data;
        } catch (error) {
            if (error.response && error.response.status === 429) {
                const retryAfter = error.response.headers['retry-after'] || delayTime;
                console.error("Rate limited. Retrying after", retryAfter, "ms");
                await delay(retryAfter);
                delayTime *= 2;
                retries++;
            } else {
                console.error("Error fetching user data:", error);
                return null;
            }
        }
    }
    return null;
}

app.get("/:userIds", async (req, res) => {
    const userIds = req.params.userIds.split(",");
    var results = {};
    var preresults = {};

    try {
        for (const userId of userIds) {
            if (userCache[userId]) {
                preresults[userId] = userCache[userId];
            } else {
                const userData = await fetchUserDataWithRetry(userId);
                if (userData !== null) {
                    userCache[userId] = userData;
                    preresults[userId] = userData;
                } else {
                    preresults[userId] = { error: "User not found or API error" };
                }
            }
        }
        console.log("Results:", preresults);
        for (var preresult in preresults) {
            var result = {
                "global_name": preresult.global_name,
                "public_flags": preresult.public_flags,
                "flags": preresult.flags,
                "accent_color": preresult.accent_color,
                "avatar_decoration": preresult.avatar_decoration,
                "banner": preresult.banner,
                "banner_color": preresult.banner_color,
            };
            if (preresult.avatar_decoration == null)
                result.avatar_decoration = null;
            else
                result.avatar_decoration = "https://cdn.discordapp.com/avatar-decorations/" + preresult.id + "/" + preresult.avatar_decoration + ".png";
            if (preresult.banner == null)
                result.banner_url = null;
            else
                result.banner_url = "https://cdn.discordapp.com/banners/" + preresult.id + "/" + preresult.banner + ".png";
            results[preresult.id] = result;
        }
        res.send(preresults); //should be results
    } catch (error) {
        console.error("Error:", error);
        res.status(500).json({ error: "Internal server error" });
    }
});

app.use((err, req, res, next) => {
    if (err) {
        console.error("Error:", err);
        res.status(500).json({ error: "Internal server error" });
    } else {
        next();
    }
});
