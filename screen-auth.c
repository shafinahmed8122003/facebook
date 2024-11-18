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

    return show_options(title, options, option_count);
}