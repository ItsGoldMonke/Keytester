#include <string.h>
#include <stdio.h>
#include "requests.h"

void list_providers() {
    printf(
        "Choose one of these providers: \n"
    );
    printf("[discord]: Discord\n");
    printf("[webhook-dc]: Discord Webhook\n");
    printf("[gemini]: Google Gemini\n");
    printf("[openrouter]: Openrouter\n");
}

int main(int argc, char *argv[])
{
    printf("Hello world! \n");
    make_request("https://httpbin.org/get", "");
    if (argc > 1) 
    {
        for (int i = 0; i < argc; i++)
        {
            if (strcmp(argv[i], "--provider") == 0)
            {
                if (strcmp(argv[i+1], "discord") == 0)
                {
                    printf("Discord\n");
                    make_request("https://discord.com/api/v10/users/@me", "Authorization: Bot ");
                }
            }
            else {
                if (strcmp(argv[i], "providers") == 0)
                {
                    list_providers();
                }
            }
        }
        
    }
    
    return 0;
}


