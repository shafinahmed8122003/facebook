#include "screens.h"

int ScreenSettings(Database *db, User *user)
{
    char options[][50] =
    {
        "Change Name",
        "Lock/Unlock Profile",
        "Delete Account",
        "Go Back",
        "Log Out",
    };

    int option_count = sizeof(options) / sizeof(options[0]);

    int current_option = 0;

show_options:
    {
        int finished = 0;
        while (!finished)
        {
            clear_screen();
            hide_cursor();

            show_title("Settings");
            finished = show_options(options, option_count, &current_option);
        }
    }

    if (current_option == 0)
    {
        create_new_buffer();
        clear_screen();
        show_cursor();

        printf("Enter your new name: ");
        scanf(" %[^\n]", user->name);

        update_user_data(db, user);
        save_data(db);

        kill_current_buffer();
        current_option = 0;
        goto show_options;
    }
    else if (current_option == 1)
    {
        while (1)
        {
            create_new_buffer();
            clear_screen();
            hide_cursor();

            if (user->profile_locked == 0)
            {
                show_title("Profile locked: False");
                printf("\nYour profile is currently public!\n");
                printf("Press enter to lock your profile!\n");

                int keys = getch();
                if (keys == 13)
                {
                    user->profile_locked = 1;
                    update_user_data(db, user);
                    save_data(db);
                    break;
                }
            }
            else
            {
                show_title("Profile locked: True");
                printf("\nYour profile is currently locked!\n");
                printf("Press enter to unlock your profile!\n");

                int keys = getch();
                if (keys == 13)
                {
                    user->profile_locked = 0;
                    update_user_data(db, user);
                    save_data(db);
                    break;
                }
            }
        }

        kill_current_buffer();
        current_option = 0;
        goto show_options;
    }
    else if (current_option == 2)
    {
        while (1)
        {
            create_new_buffer();
            clear_screen();
            hide_cursor();

            show_title("Are you sure you want to delete your account?");
            printf(" - Press enter to confirm.\n");
            printf(" - Press esc (escape) to go back.\n");

            int keys = getch();
            if (keys == 13)
            {
                return current_option;
            }
            else if (keys == 27)
            {
                break;
            }
        }

        kill_current_buffer();
        current_option = 0;
        goto show_options;
    }

    return current_option;
}
