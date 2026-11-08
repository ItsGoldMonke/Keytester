# Keytester

Keytester is a program that can test if your api keys work. It supports multiple services, right now being 10+, but continuously expanding.
It is written in C, using the `libcurl` library for requests.

This is my first ever C program, so expect some bugs to possibly exist. I made it for HackClub's [Terra](https://terra.hackclub.com) program.

# Screenshot

![Screenshot showing the program in action](images/showcase.png)

## Key providers:

The following api providers are implemented right now:

| Service            | Parameter         |
| ------------------ | ----------------- |
| Discord (bots)     | `discord`         |
| Discord (webhooks) | `webhook-discord` |
| Google gemini      | `gemini`          |
| Openrouter         | `openrouter`      |
| GitHub             | `github`          |
| GitLab             | `gitlab`          |
| Nasa               | `nasa`            |
| Slack              | `slack`           |
| OpenWeather        | `openweather`     |
| Telegram (bots)    | `telegram`        |

# Credits

This project was heavily inspired by [Keylyzer](https://github.com/SyscallX-18113/Keylyzer), as it inspired me to make a similar program.
