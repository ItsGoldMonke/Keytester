# Keytester

Keytester is a program that can test if your api keys work. It supports multiple services, right now being 10+, but continuously expanding.
It is written in C, using the `libcurl` library for requests.

This is my first ever C program, so expect some bugs to possibly exist. I made it for HackClub's [Terra](https://terra.hackclub.com) program.

# Screenshot

![Screenshot showing the program in action](images/showcase.png)

## Key providers:

The following api providers are implemented right now:

| Service            | Parameter         | Endpoint                                                             |
| ------------------ | ----------------- | -------------------------------------------------------------------- |
| Discord (bots)     | `discord`         | https://discord.com/api/v10/users/@me                                |
| Discord (webhooks) | `webhook-discord` | The webhook's url                                                    |
| Google gemini      | `gemini`          | https://generativelanguage.googleapis.com/v1beta/models              |
| Openrouter         | `openrouter`      | https://openrouter.ai/api/v1/models                                  |
| GitHub             | `github`          | https://api.github.com/user                                          |
| GitLab             | `gitlab`          | https://gitlab.com/api/v4/user                                       |
| NASA               | `nasa`            | https://api.nasa.gov/planetary/apod?api_key=<key>                    |
| Slack              | `slack`           | https://slack.com/api/auth.test                                      |
| OpenWeather        | `openweather`     | https://api.openweathermap.org/data/2.5/weather?q=London&appid=<key> |
| Telegram (bots)    | `telegram`        | https://api.telegram.org/bot<key>/getMe                              |

The endpoints used are meant to be least intrusive to the key owner, so they only affect limits if it is the only option available.

# Requirements

Currently this project requires you to be on a linux system. Windows support is planned to be implemented later.

# Usage:

To use the program, you should first download it from github releases or [build it from source](#building-from-source)
Then locate the downloaded/built file, and give it excecutable permissions:

```
chmod +x ./keytester
```

Then run the file:

```
./keytester --help # Shows command usage
./keytester providers # Lists all providers
./keytester --provider discord --key <your token> # Tests a discord bot token.
./keytester --provider gitlab # Tests a gitlab key by checking environment variables, and if none found prompting the user.
```

# Building from source

To build from source you need the following dependencies:
`curl`, `make` and `gcc` (Often added with `base-devel` on Arch-like systems or `build-essential` on Debian)

Firstly, clone the repository:

```
git clone https://github.com/ItsGoldMonke/Keytester.git
cd Keytester
```

Then compile the project:

```
make
```

Then your binary should be built as `bin/keytester`.

# Disclaimer

You should only use this with your OWN keys, tokens, and links, or ones you are permitted to use.

# Credits

This project was heavily inspired by [Keylyzer](https://github.com/SyscallX-18113/Keylyzer), as it inspired me to make a similar program.
