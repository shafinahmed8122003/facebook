#include "screens.h"

int ScreenSearch(Database *db, User *user)
{
    char username[50];

    char options1[][50] =
    {
        "Add Friend",
        "See Profile",
        "Go Back",
    };
    int option_count1 = 3;

    char options2[][50] =
    {
        "Go Back",
    };
    int option_count2 = 1;

    clear_screen();
    show_cursor();

    show_title("Search your friends!");
    printf("Friend's username: ");
    scanf(" %[^\n]", username);

    User friend;
    int success = find_user_by_username(db, &friend, username);

    if (success)
    {
        int current_option = 0;

show_result:
        {
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
        }

        if(current_option==0)
        {
            for (int i = 0; i < 100; i++)
            {
                if(user->friends_id[i]==0)
                {
                    user->friends_id[i] = friend.id;
                    update_user_data(db,user);
                    save_data(db);
                    goto show_result;
                }
            }
        }
        else if(current_option==1)
        {
            create_new_buffer();
            int choice;
show_profile:
            {
                choice = ScreenProfile(friend);
            }
            switch(choice)
            {
            case 0:
                create_new_buffer();
                clear_screen();
                show_title("Friends List:");
                int count=1;
                if (!friend.profile_locked)
                {
                    for(int i=0; i<TOTAL_USER_NUMBER ; i++)
                    {
                        for(int j=0; j<100; j++)
                        {
                            if(db->users[i].id==friend.friends_id[j] && db->users[i].id!=0 )
                            {
                                printf("%d: (@%s) - %s\n", count, db->users[i].username, db->users[i].name);
                                count++;
                            }
                        }
                    }
                }
                else
                {
                    printf("Sorry! You can't see this users friends list. The profile is locked!\n");
                }
                printf("\n");
                printf("Press enter to go back.\n");
                getch();
                kill_current_buffer();
                goto show_profile;
            case 1:
                create_new_buffer();

                clear_screen();
                show_title("All Post:");
                count=1;
                if (!friend.profile_locked)
                {
                    for(int i=0; i<TOTAL_USER_NUMBER ; i++)
                    {
                        for(int j=0; j<100; j++)
                        {
                            if(db->posts[i].id==friend.posts_id[j] && db->posts[i].id!=0 )
                            {
                                printf("%d: @%s\n",count,friend.username);
                                printf("   %s\n ",db->posts[i].content);
                                printf("  Like: %d\n",db->posts[i].likes);
                                count++;
                            }
                        }
                    }
                }
                else
                {
                    printf("Sorry! You can't see this users posts. The profile is locked!\n");
                }
                printf("\n");
                printf("Press enter to go back.\n");
                getch();
                kill_current_buffer();
                goto show_profile;
            default:
                kill_current_buffer();
                goto show_result;
            }
        }
        else
        {
            return current_option;
        }

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
