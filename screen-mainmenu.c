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

    
    char title[50] = "Peach Be Upon You, ";
    strcat(title, user->name);

    return show_options(title, options, option_count);
}