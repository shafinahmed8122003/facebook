#include "screens.h"

int ScreenProfile(User user)
{
    char options[][50]=
    {
        "See Friends",
        "See Posts",
        "Go Back",
    };
    int option_count=3;
    int current_option=0;

    int finished=0;
    while(!finished)
    {
        clear_screen();
        hide_cursor();

        char username[100] = "@";
        strcat(username, user.username);

        show_title_in_box(user.name);
        show_title(username);
        printf("\n");
        finished=show_options(options,option_count,&current_option);
    }
    
    return current_option;
}

