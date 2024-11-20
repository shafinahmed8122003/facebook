#include "screens.h"

int ScreenMainmenu(User *user)
{
    char options[][50] = {
        "News Feed",
        "Create Post",
        "Profile",
        "Search",
        "Notifications",
        "Settings",
    };

    int option_count = sizeof(options) / sizeof(options[0]);

    
    char title[50] = "Peace Be Upon You, ";
    strcat(title, user->name);

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