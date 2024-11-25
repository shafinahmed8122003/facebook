#include "screens.h"

int ScreenNewsFeed(Database *db, User *user)
{
    char options[][50] = {
        "Like",
        "Share",
        "See Profile",
        "Previews Post",
        "Next Post",
        "Go Back",
    };

    int option_count = sizeof(options) / sizeof(options[0]);

    int current_post_index = 0;
    int current_option = 4;

    int post_length = 0;
    for (int i = 0; i < TOTAL_POST_NUMBER; i++)
    {
        if (db->posts[i].id != 0)
        {
            post_length++;
        }
    }

show_post:
{

    char auther_username[50];

    for (int i = 0; i < TOTAL_POST_NUMBER; i++)
    {
        if (db->posts[current_post_index].author_id == db->users[i].id)
        {
            strcpy(auther_username, db->users[i].username);
            break;
        }
    }

    int finished = 0;
    while (!finished)
    {
        clear_screen();
        hide_cursor();

        printf("+-\n");
        printf("| \033[1;7;93m @%s \033[0m\n", auther_username);
        printf("+-\n");
        printf("| \n");
        printf("| -> %s\n", db->posts[current_post_index].content);
        printf("| \n");
        printf("+-\n");
        printf("| Likes: %2d | Shares: 0\n", db->posts[current_post_index].likes);
        printf("+-\n");

        printf("\n");

        finished = show_options(options, option_count, &current_option);
    }

    if (current_option == 0)
    {
        db->posts[current_post_index].likes++;
        save_data(db);
        goto show_post;
    }
    else if (current_option == 2 || current_option == 5)
    {
        return current_option;
    }
    else if (current_option == 4)
    {
        if (current_post_index < post_length - 1)
        {
            current_post_index++;
        }
        goto show_post;
    }
    else if (current_option == 3)
    {
        if (current_post_index > 0)
        {
            current_post_index--;
        }
        goto show_post;
    }
}
}
