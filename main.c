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
}

end:
    return 0;
}
