#include <string.h>
#include <stdio.h>
#include <time.h>
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
        const char *provider = NULL;
        const char *key = NULL;

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
                printf("%s\n", provider);
            }
            else if (strcmp(argv[i], "--key") == 0)
            {
                if (i + 1 >= argc)
                {
                    printf("--key requires a value. Use --help for help\n");
                    return 1;
                }

                key = argv[++i];
                printf("%s\n", key);
            }
            else
            {
                printf("Unknown argument: %s\n", argv[i]);
                return 1;
            }
        }
        
    }
    
    return 0;
}


