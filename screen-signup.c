#include "screens.h"

int ScreenSignup(Database *db, User *user)
{
    char name[50];
    char username[50];
    char password[50];

    clear_screen();
    show_cursor();

    show_title("Starting a new journey!");
    printf("Name: ");
    scanf(" %[^\n]", &name);
    printf("Username: ");
    scanf(" %[^\n]", &username);
    printf("Password: ");
    scanf(" %[^\n]", &password);
    printf("\n");

    int signup_success = create_an_user(db, user, name, username, password);

    return signup_success;
}
