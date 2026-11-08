#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "input.h"
#include "requests.h"

void list_providers() {
    printf(
        "Choose one of these providers: \n"
    );
    printf("[discord]:      Discord\n");
    printf("[webhook-dc]:   Discord Webhook\n");
    printf("[gemini]:       Google Gemini\n");
    printf("[openrouter]:   Openrouter\n");
    printf("[github]:       GitHub\n");
    printf("[gitlab]:       GitLab\n");
    printf("[nasa]:         Nasa\n");
    printf("[slack]:        Slack\n");
    printf("[openweather]:  Openweather\n");
    printf("[telegram]:  Telegram\n");
}

int main(int argc, char *argv[])
{
    if (argc > 1) 
    {
        const char *provider = NULL;
        const char *key = NULL;
        char key_buffer[4096];
        bool raw = true;

        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "--provider") == 0)
            {
                if (i + 1 >= argc)
                {
                    printf("--provider requires a value. Use --help for help\n");
                    return 1;
                }

                provider = argv[++i];
            }
            else if (strcmp(argv[i], "--key") == 0)
            {
                if (i + 1 >= argc)
                {
                    printf("--key requires a value. Use --help for help\n");
                    return 1;
                }

                key = argv[++i];
            }
            else if (strcmp(argv[i], "--raw") == 0)
            {
                raw = true;
            }
            else if (strcmp(argv[i], "--help") == 0) 
            {
                printf("Usage: keytester --provider PROVIDER --key KEY\n");
                printf("To list all available providers, use 'keytester providers'\n");
                return 0;
            }
            else if (strcmp(argv[i], "--version") == 0)
            {
                printf("keytester version: 1.0.0\n");
                return 0;
            }
            else if (strcmp(argv[i], "providers") == 0)
            {
                list_providers();
                return 0;
            }
            else
            {
                printf("Unknown argument: %s\n", argv[i]);
                return 1;
            }
        }

        if (provider == NULL)
        {
            printf("ERROR: No provider specified\n");
            return 1;
        }
        if (key == NULL || key[0] == '\0')
        {
            key = getenv("KEYTESTER_KEY");
            
            if (key == NULL || key[0] == '\0')
            {
                if (get_hidden_input("Enter your key: ", 
                                    key_buffer, 
                                    sizeof(key_buffer)) != 0)
                {
                    fprintf(stderr, "Failed to read input");
                    return 1;
                }
                key = key_buffer;
            }
        }

        if (strcmp(provider, "discord") == 0)
        {
            if (key == NULL)
            {
                printf("Discord needs a bot token\n");
                return 1;
            }

            const char *prefix = "Authorization: Bot ";
            size_t header_size = strlen(prefix) + strlen(key) + 1;

            char *auth_header = malloc(header_size);

            if (auth_header == NULL)
            {
                printf("Failed to allocate auth header\n");
                return 1;
            }

            strcpy(auth_header, prefix);
            strcat(auth_header, key);

            make_request("https://discord.com/api/v10/users/@me", auth_header, raw);

            free(auth_header);
        }
        
        else if (strcmp(provider, "webhook-dc") == 0)
        {
            if (key == NULL)
            {
                printf("Discord webhook needs a url\n");
                return 1;
            }

            make_request(key, NULL, raw);

        }

        else if (strcmp(provider, "gemini") == 0)
        {
            if (key == NULL)
            {
                printf("Gemini needs an api key\n");
                return 1;
            }
            const char *prefix = "x-goog-api-key: ";
            size_t header_size = strlen(prefix) + strlen(key) + 1;

            char *auth_header = malloc(header_size);

            if (auth_header == NULL)
            {
                printf("Failed to allocate auth header\n");
                return 1;
            }

            strcpy(auth_header, prefix);
            strcat(auth_header, key);

            make_request("https://generativelanguage.googleapis.com/v1beta/models", auth_header, raw);
            free(auth_header);
        }

        else if (strcmp(provider, "openrouter") == 0)
        {
            if (key == NULL)
            {
                printf("Openrouter needs an api key\n");
                return 1;
            }
            const char *prefix = "Authorization: Bearer ";
            size_t header_size = strlen(prefix) + strlen(key) + 1;

            char *auth_header = malloc(header_size);

            if (auth_header == NULL)
            {
                printf("Failed to allocate auth header\n");
                return 1;
            }

            strcpy(auth_header, prefix);
            strcat(auth_header, key);

            make_request("https://openrouter.ai/api/v1/models", auth_header, raw);
            free(auth_header);            
        }
        
        else if (strcmp(provider, "github") == 0)
        {
            if (key == NULL)
            {
                printf("Github needs an api key\n");
                return 1;
            }
            const char *prefix = "Authorization: Bearer ";
            size_t header_size = strlen(prefix) + strlen(key) + 1;

            char *auth_header = malloc(header_size);

            if (auth_header == NULL)
            {
                printf("Failed to allocate auth header\n");
                return 1;
            }

            snprintf(auth_header, header_size, "%s%s", prefix, key);

            make_request("https://api.github.com/user", auth_header, raw);
            free(auth_header);            
        }
        
        else if (strcmp(provider, "gitlab") == 0)
        {
            if (key == NULL)
            {
                printf("Gitlab needs an api key\n");
                return 1;
            }

            char auth_header[512];

            int written = snprintf(auth_header, sizeof(auth_header), "PRIVATE-TOKEN: %s", key);

            if (written < 0 || (size_t)written >= sizeof(auth_header))

            make_request("https://gitlab.com/api/v4/user", auth_header, raw);
        }
        
        else if (strcmp(provider, "nasa") == 0)
        {
            if (key == NULL)
            {
                printf("Nasa needs an api key\n");
                return 1;
            }

            char url[512];

            int written = snprintf(url, sizeof(url), "https://science.nasa.gov/wp-json/wp/v2/apod-basic/?api_key=%s", key);

            if (written < 0 || (size_t)written >= sizeof(url))
            {
                fprintf(stderr, "Error: URL is too long.\n");
                return 1;
            }

            make_request(url, "", raw);
        }
        
        else if (strcmp(provider, "slack") == 0)
        {
            if (key == NULL)
            {
                printf("Slack needs a bot token\n");
                return 1;
            }
            const char *prefix = "Authorization: Bearer ";
            size_t header_size = strlen(prefix) + strlen(key) + 1;

            char *auth_header = malloc(header_size);

            if (auth_header == NULL)
            {
                printf("Failed to allocate auth header\n");
                return 1;
            }

            snprintf(auth_header, header_size, "%s%s", prefix, key);

            make_request("https://slack.com/api/auth.test", auth_header, raw);
        }
        
        else if (strcmp(provider, "openweather") == 0)
        {
            if (key == NULL)
            {
                printf("Openweather needs an api key\n");
                return 1;
            }

            char url[512];

            int written = snprintf(url, sizeof(url), "https://api.openweathermap.org/data/2.5/weather?q=London&appid=%s", key);

            if (written < 0 || (size_t)written >= sizeof(url))
            {
                fprintf(stderr, "Error: URL is too long.\n");
                return 1;
            }

            make_request(url, "", raw);
        }
        
        else if (strcmp(provider, "telegram") == 0)
        {
            if (key == NULL)
            {
                printf("Telegram needs an api key\n");
                return 1;
            }

            char url[512];

            int written = snprintf(url, sizeof(url), "https://api.telegram.org/bot%s/getMe", key);

            if (written < 0 || (size_t)written >= sizeof(url))
            {
                fprintf(stderr, "Error: URL is too long.\n");
                return 1;
            }

            make_request(url, "", raw);
        }
        
        else {
            printf("Unknown provider: %s\n", provider);
            return 1;
        }
    }
    else {
        printf("No options supplied\n");
        printf("Usage: keytester --provider PROVIDER --key KEY\n");
        printf("To list all available providers, use 'keytester providers'\n");
        }
    
    return 0;
}


