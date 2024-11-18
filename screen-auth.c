#include "screens.h"

int ScreenAuth()
{
    char options[][50] = {
        "Log In",
        "Create a new account",
        "Exit",
    };

    int option_count = sizeof(options) / sizeof(options[0]);
    
    char title[50] = "Welcome to ";
    strcat(title, APP_NAME);

    int current_option = 0;
    int finished = 0;
    while (!finished)
    {
        clear_screen();
        hide_cursor();
        show_title(title);
        finished = show_options(options, option_count, &current_option);
    }

    return current_option;
}