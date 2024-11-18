#include "screens.h"

int ScreenLogin(Database *db, User *user)
{
    char username[50];
    char password[50];

    clear_screen();
    show_cursor();

    show_title("Please enter your credentials!");
    printf("Username: ");
    scanf(" %[^\n]", &username);
    printf("Password: ");
    scanf(" %[^\n]", &password);
    printf("\n");

    int login_success = find_user_using_username_password(db, user, username, password);

    return login_success;
}