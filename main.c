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
    case 3:
        goto screen_search;
        break;
    case 5:
        goto screen_settings;
        break;
    default:
        goto end;
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
