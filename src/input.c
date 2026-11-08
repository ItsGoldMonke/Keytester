#include "input.h"
#include <stdio.h>
#include <string.h>

#ifdef _WIN32

#include <conio.h>
#include <io.h>

#else
#include <termios.h>
#include <unistd.h>

#endif

int get_hidden_input(char *prompt, char *buffer, size_t size)
{
    if (buffer == NULL || size < 2)
    {
        return 1;
    }

    printf("%s", prompt);
    fflush(stdout);

#ifdef _WIN32

    if (!_isatty(_fileno(stdin)))
    {
        return 1;
    }

    size_t i = 0;
    int overflow = 0;

    while (1)
    {
        int c = _getch();

        if (c == '\r')
            break;

        if (c == '\b')
        {
            if (i > 0)
                i--;
            continue;
        }

        if (c == 3) // Ctrl+C
            return 1;

        if (i < size - 1)
            buffer[i++] = (char)c;
        else
            overflow = 1;
    }

    buffer[i] = '\0';
    printf("\n");

    if (overflow)
    {
        return 1;
    }




#else

    if (!isatty(STDIN_FILENO))
    {
        return 1;
    }
    
    struct termios old_terminal, new_terminal;
    
    if (tcgetattr(STDIN_FILENO, &old_terminal) != 0)
    {
        return 1;
    }
    new_terminal = old_terminal;
    new_terminal.c_lflag &= ~ECHO;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_terminal) != 0)
    {
        return 1;
    }
    
    char *result = fgets(buffer, (int)size, stdin);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_terminal);
    printf("\n");

    if (result == NULL)
    {
        return 1;
    }
    buffer[strcspn(buffer, "\r\n")] = '\0';

#endif

    return 0;
}