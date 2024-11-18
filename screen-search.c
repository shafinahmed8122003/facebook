#include "screens.h"
#include <windows.h>

int ScreenSearch(Database *db, User *user)
{
    char username[50];

    char options1[][50] = {
        "Add Friend",
        "See Profile",
        "Go Back",
    };
    int option_count1 = sizeof(options1) / sizeof(options1[0]);

    char options2[][50] = {
        "Go Back",
    };
    int option_count2 = sizeof(options2) / sizeof(options2[0]);

    clear_screen();
    show_cursor();

    show_title("Search your friends!");
    printf("Friend's username: ");
    scanf(" %[^\n]", username);

    int second = 0;
    while (second < 4)
    {
        clear_screen();
        printf("We are searching your friend");
        for (int i = 0; i < second; i++)
        {
            printf(".");
        }
        Sleep(500);
        second++;
    }

    User friend;
    int success = find_user_by_username(db, &friend, username);

    if (success)
    {
        int current_option = 0;
        int finished = 0;
        while (!finished)
        {
            clear_screen();
            hide_cursor();
            show_title("Friend Found!");

            char title[100] = "Friend's name: ";
            strcat(title, friend.name);
            show_title_in_box(title);
            printf("\n");

            finished = show_options(options1, option_count1, &current_option);
        }

        return current_option;
    }
    else
    {
        int current_option = 0;
        int finished = 0;
        while (!finished)
        {
            clear_screen();
            hide_cursor();
            
            show_title("Friend not found!");
            printf("No user found with the username '%s'\n", username);
            printf("\n");

            finished = show_options(options2, option_count2, &current_option);
        }

        return 2; // Go back to the main menu
    }
}