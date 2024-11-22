#include "utils.h"

void initialize_database(Database *db)
{
    for (int i = 0; i < TOTAL_USER_NUMBER; i++)
    {
        db->users[i].id = 0;
        db->users[i].username[0] = '\0';
        db->users[i].name[0] = '\0';
        db->users[i].password[0] = '\0';
        db->users[i].profile_locked = 0;
    }
    for (int i = 0; i < TOTAL_COMMENT_NUMBER; i++)
    {
        db->comments[i].id = 0;
        db->comments[i].content[0] = '\0';
        db->comments[i].timestamp = 0;
        db->comments[i].author_id = 0;
    }
    for (int i = 0; i < TOTAL_POST_NUMBER; i++)
    {
        db->posts[i].id = 0;
        db->posts[i].content[0] = '\0';
        db->posts[i].timestamp = 0;
        db->posts[i].author_id = 0;
        db->posts[i].likes = 0;
        db->posts[i].shares = 0;
    }
    for (int i = 0; i < TOTAL_NOTIFICATION_NUMBER; i++)
    {
        db->notifications[i].id = 0;
        db->notifications[i].content[0] = '\0';
        db->notifications[i].timestamp = 0;
    }
}

void save_data(Database *db)
{
    FILE *file = fopen(DATABASE_FILE, "wb");

    if (file == NULL)
    {
        printf("Error creating database!\n");
        exit(1);
    }

    fwrite(db, DATABASE_SIZE, 1, file);
    fclose(file);
}

/*
 * This function tries to load data from the database.
 * If the file does not exist, it initializes the database and saves it.
 */
void load_data(Database *db)
{
    FILE *file = fopen(DATABASE_FILE, "rb");

    if (file == NULL)
    {
        fclose(file);
        initialize_database(db);
        save_data(db);
        return;
    }

    fread(db, DATABASE_SIZE, 1, file);
    fclose(file);
}

void clear_screen()
{
    printf("\033[H\033[J");
}

void hide_cursor()
{
    printf("\033[?25l");
}

void show_cursor()
{
    printf("\033[?25h");
}

/* This function looks for a user using the provided username and password.
 * If found, returns 1;
 * Otherwise, returns 0;
 */
int find_user_using_username_password(Database *db, User *user, char username[], char password[])
{
    strlwr(username); // Converts to lowercase

    for (int i = 0; i < TOTAL_USER_NUMBER; i++)
    {
        if (strcmp(username, db->users[i].username) == 0 && strcmp(password, (*db).users[i].password) == 0)
        {
            user->id = db->users[i].id;
            strcpy(user->name, db->users[i].name);
            strcpy(user->username, db->users[i].username);
            strcpy(user->password, db->users[i].password);
            user->profile_locked = db->users[i].profile_locked;

            for (int j = 0; j < TOTAL_POST_NUMBER; j++)
            {
                user->posts_id[j] = db->users[i].posts_id[j];
            }

            for (int j = 0; j < TOTAL_FRIEND_NUMBER; j++)
            {
                user->friends_id[j] = db->users[i].friends_id[j];
            }

            for (int j = 0; j < TOTAL_NOTIFICATION_NUMBER; j++)
            {
                user->notifications_id[j] = db->users[i].notifications_id[j];
            }

            return 1;
        }
    }

    return 0;
}

int find_user_using_id(Database *db, User *user, USER_ID id)
{
    for (int i = 0; i < TOTAL_USER_NUMBER; i++)
    {
        if (id == db->users[i].id)
        {
            user->id = db->users[i].id;
            strcpy(user->name, db->users[i].name);
            strcpy(user->username, db->users[i].username);
            strcpy(user->password, db->users[i].password);
            user->profile_locked = db->users[i].profile_locked;

            for (int j = 0; j < TOTAL_POST_NUMBER; j++)
            {
                user->posts_id[j] = db->users[i].posts_id[j];
            }

            for (int j = 0; j < TOTAL_FRIEND_NUMBER; j++)
            {
                user->friends_id[j] = db->users[i].friends_id[j];
            }

            for (int j = 0; j < TOTAL_NOTIFICATION_NUMBER; j++)
            {
                user->notifications_id[j] = db->users[i].notifications_id[j];
            }

            return 1;
        }
    }

    return 0;
}

int create_an_user(Database *db, User *user, char name[], char username[], char password[])
{
    strlwr(username); // Converts to lowercase

    // This part checks whether the username is unique or not
    int username_unique = 1;
    for (int i = 0; i < TOTAL_USER_NUMBER; i++)
    {
        if (strcmp(db->users[i].username, username) == 0)
        {
            username_unique = 0;
        }
    }

    if (username_unique)
    {
        for (int i = 0; i < TOTAL_USER_NUMBER; i++)
        {
            if (db->users[i].username[0] == '\0')
            {
                db->users[i].id = generate_unique_id();
                strcpy(db->users[i].name, name);
                strcpy(db->users[i].username, username);
                strcpy(db->users[i].password, password);
                db->users[i].profile_locked = 0;

                save_data(db);

                user->id = db->users[i].id;
                strcpy(user->name, db->users[i].name);
                strcpy(user->username, db->users[i].username);
                strcpy(user->password, db->users[i].password);
                user->profile_locked = db->users[i].profile_locked;

                for (int j = 0; j < TOTAL_POST_NUMBER; j++)
                {
                    user->posts_id[j] = db->users[i].posts_id[j];
                }

                for (int j = 0; j < TOTAL_FRIEND_NUMBER; j++)
                {
                    user->friends_id[j] = db->users[i].friends_id[j];
                }

                for (int j = 0; j < TOTAL_NOTIFICATION_NUMBER; j++)
                {
                    user->notifications_id[j] = db->users[i].notifications_id[j];
                }

                return 1;
            }
        }
    }

    return 0;
}

/*
 * This function generates and returns a unique ID (USER_ID).
 */
USER_ID generate_unique_id()
{
    static int initialized = 0;

    // Initialize random seed once
    if (!initialized)
    {
        srand((unsigned int)time(NULL));
        initialized = 1;
    }

    // Generate unique ID: current time + random number
    time_t now = time(NULL);
    unsigned long long unique_id = ((unsigned long long)now * 1000000) + (rand() % 1000000);

    return unique_id;
}

int show_options(char options[][50], int option_count, int *current_option)
{
    for (int i = 0; i < option_count; i++)
    {
        if (*current_option == i)
        {
            printf("\033[1;7;93m  %s  \033[0m\n", options[i]);
        }
        else
        {
            printf(" %s\n", options[i]);
        }
    }

    char keys = getch();
    if (keys == 224 || keys == -32)
    {
        keys = getch();
        switch (keys)
        {
        case 72:
            (*current_option)--;
            if (*current_option < 0)
            {
                *current_option = option_count - 1;
            }
            break;
        case 80:
            (*current_option)++;
            if (*current_option >= option_count)
            {
                *current_option = 0;
            }
            break;
        }
    }
    else if (keys == 13)
    {
        return 1;
    }
    return 0;
}

void draw_line(int length)
{
    for (int i = 0; i < length + 2; i++)
    {
        printf("-");
    }
}

void show_title(char title[])
{
    printf(" %s \n", title);
    draw_line(strlen(title));
    printf("\n");
}

void show_title_in_box(char title[])
{
    printf("+");
    draw_line(strlen(title));
    printf("+");
    printf("\n");
    printf("| %s |\n", title);
    printf("+");
    draw_line(strlen(title));
    printf("+");
    printf("\n");
}

int find_user_by_username(Database *db, User *user, char username[])
{
    strlwr(username);

    int success = 0;
    for (int i = 0; i < TOTAL_USER_NUMBER; i++)
    {
        if (strcmp(username, db->users[i].username) == 0)
        {
            success = 1;
            user->id = db->users[i].id;
            strcpy(user->name, db->users[i].name);
            strcpy(user->username, db->users[i].username);
            strcpy(user->password, db->users[i].password);
            user->profile_locked = db->users[i].profile_locked;

            for (int j = 0; j < TOTAL_POST_NUMBER; j++)
            {
                user->posts_id[j] = db->users[i].posts_id[j];
            }

            for (int j = 0; j < TOTAL_FRIEND_NUMBER; j++)
            {
                user->friends_id[j] = db->users[i].friends_id[j];
            }

            for (int j = 0; j < TOTAL_NOTIFICATION_NUMBER; j++)
            {
                user->notifications_id[j] = db->users[i].notifications_id[j];
            }
        }
    }

    return success;
}

time_t get_current_time()
{
    return time(NULL);
}

void create_post(Database *db, User *user, char post_content[])
{
    Post post;
    post.id = generate_unique_id();
    strcpy(post.content, post_content);
    post.timestamp = get_current_time();
    post.author_id = user->id;
    post.likes = 0;
    post.shares = 0;

    for (int i = 0; i < TOTAL_POST_NUMBER; i++)
    {
        if (db->posts[i].id == 0) // Means empty slot
        {
            db->posts[i].id = post.id;
            strcpy(db->posts[i].content, post.content);
            db->posts[i].timestamp = post.timestamp;
            db->posts[i].author_id = post.author_id;
            db->posts[i].likes = post.likes;
            db->posts[i].shares = post.shares;
            break;
        }
    }

    for (int i = 0; i < TOTAL_USER_NUMBER; i++)
    {
        if (db->users[i].id == user->id)
        {
            for (int j = 0; j < TOTAL_POST_NUMBER; j++)
            {
                if (db->users[i].posts_id[j] == 0)
                {
                    db->users[i].posts_id[j] = post.id;
                    break;
                }
            }
            break;
        }
    }

    save_data(db);
    find_user_by_username(db, user, user->username);
}
