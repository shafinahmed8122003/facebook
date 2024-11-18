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

int create_an_user(Database *db, User *user, char name[], char username[], char password[])
{
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
 * This function generates and returns a unique ID (UUID).
 */
unsigned long long int generate_unique_id()
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

int show_options(char title[], char options[][50], int option_count)
{
    int current_option = 0;
    while (1)
    {
        clear_screen();
        hide_cursor();

        puts(title);
        printf("-----------------------\n");

        for (int i = 0; i < option_count; i++)
        {
            if (current_option == i)
            {
                printf("> %s\n", options[i]);
            }
            else
            {
                printf("  %s\n", options[i]);
            }
        }

        char keys = getch();
        if (keys == 224 || keys == -32)
        {
            keys = getch();
            switch (keys)
            {
            case 72:
                current_option--;
                if (current_option < 0)
                {
                    current_option = option_count - 1;
                }
                break;
            case 80:
                current_option++;
                if (current_option >= option_count)
                {
                    current_option = 0;
                }
                break;
            }
        }
        else if (keys == 13)
        {
            return current_option;
        }
    }
}