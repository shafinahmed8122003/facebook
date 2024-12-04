#include <stdio.h>
#include <string.h>
#include "types.h"
#include "utils.h"
#include "screens.h"

int main()
{
    Database db;
    User user;
    load_data(&db);

screen_auth:
    {
        int choice = ScreenAuth();
        switch (choice)
        {
        case 0:
            goto screen_login;
            break;
        case 1:
            goto screen_signup;
            break;
        default:
            goto end;
        }
    }

screen_login:
    {
        int login_success = ScreenLogin(&db, &user);
        switch (login_success)
        {
        case 1:
            goto screen_mainmenu;
            break;
        default:
            printf("Wrong credentials! Press enter to try again!\n");
            getch();
            goto screen_auth;
        }
    }

screen_signup:
    {
        int signup_success = ScreenSignup(&db, &user);
        switch (signup_success)
        {
        case 1:
            printf("Account created successfully! Press enter to log in!\n");
            getch();
            goto screen_mainmenu;
            break;
        default:
            printf("An error occurred while creating the account! Press enter to try again!\n");
            getch();
            goto screen_auth;
        }
    }

screen_mainmenu:
    {
        int choice = ScreenMainmenu(&user);
        switch (choice)
        {
        case 0:
            goto screen_newsfeed;
            break;
        case 1:
            goto screen_createpost;
            break;
        case 2:
            goto screen_profile;
            break;
        case 3:
            goto screen_search;
            break;
        case 4:
            goto screen_settings;
            break;
        }
    }

screen_profile:
    {
        int choice=ScreenProfile(user);
        switch(choice)
        {
        case 0:
            create_new_buffer();
            clear_screen();
            show_title("Friends List:");
            int count=1;
            for(int i=0; i<TOTAL_USER_NUMBER ; i++)
            {
                for(int j=0; j<100; j++)
                {
                    if(db.users[i].id==user.friends_id[j] && db.users[i].id!=0 )
                    {
                        printf("%d: (@%s) - %s\n", count, db.users[i].username, db.users[i].name);
                        count++;
                    }
                }
            }
            printf("\n");
            printf("Press enter to go back.\n");
            getch();
            kill_current_buffer();
            goto screen_profile;
            break;

        case 1:
            create_new_buffer();
            clear_screen();
            show_title("All Post:");
            count=1;
            for(int i=0; i<TOTAL_USER_NUMBER ; i++)
            {
                for(int j=0; j<100; j++)
                {
                    if(db.posts[i].id==user.posts_id[j] && db.posts[i].id!=0 )
                    {
                        printf("%d: @%s\n",count,user.username);
                        printf("   %s\n ",db.posts[i].content);
                        printf("  Like: %d\n",db.posts[i].likes);
                        count++;
                    }
                }
            }
            printf("\n");
            printf("Press enter to go back.\n");
            getch();
            kill_current_buffer();
            goto screen_profile;
            break;

        default :
            goto screen_mainmenu;
            break;
        }
    }

screen_search:
    {
        int choice = ScreenSearch(&db, &user);
        switch (choice)
        {
        default:
            goto screen_mainmenu;
        }
    }

screen_createpost:
    {
        ScreenCreatePost(&db, &user);
        goto screen_mainmenu;
    }


screen_newsfeed:
    {
        int choice = ScreenNewsFeed(&db, &user);
        switch (choice)
        {
        default:
            goto screen_mainmenu;
        }
    }

screen_settings:
    {
        int choice = ScreenSettings(&db, &user);
        switch (choice)
        {
        case 2:
            delete_user(&db, &user);
            printf("User deleted.\n");
            getch();
            goto screen_auth;
        case 4:
            goto screen_auth;
        default:
            goto screen_mainmenu;
        }
    }

end:
    clear_screen();
    show_cursor();
    return 0;
}
