#include "screens.h"

void ScreenCreatePost(Database *db, User *user)
{
    char post_content[100];

    char options[][50] = {
        "Publish",
        "Cancel",
    };

    int option_count = sizeof(options) / sizeof(options[0]);

    clear_screen();
    show_cursor();

    show_title("Create a new post!");
    printf("Enter your post (Upto 100 characters)\n: ");
    scanf(" %[^\n]", &post_content);

    int current_option = 0;
    int finished = 0;
    while (!finished)
    {
        clear_screen();
        hide_cursor();        
        show_title("Are you sure?");

        finished = show_options(options, option_count, &current_option);
    }

    clear_screen();
    if (current_option == 0)
    {
        create_post(db, user, post_content);
        printf("Post created successfully!\n");
    } 
    else
    {
        printf("Post creation canceled!\n");
    }

    printf("Press enter to continue!\n");
    getch();
}