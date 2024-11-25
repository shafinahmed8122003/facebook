#ifndef TYPES_H
#define TYPES_H

#include "constants.h"

typedef unsigned long long int USER_ID;

// db.users[0].name

typedef struct
{
    USER_ID id;
    char name[50];
    char username[50];
    char password[50];
    int profile_locked; // 0 - False & 1 - True
    USER_ID posts_id[100];
    USER_ID friends_id[100];
    USER_ID notifications_id[100];
} User;

typedef struct
{
    USER_ID id;
    char content[100];
    time_t timestamp;
    USER_ID author_id;
    int likes;
    USER_ID comments_id[100];
    int shares;
} Post;

typedef struct
{
    USER_ID id;
    char content[100];
    time_t timestamp;
} Notification;

typedef struct
{
    User users[TOTAL_USER_NUMBER];
    Post posts[TOTAL_POST_NUMBER];
    Notification notifications[TOTAL_NOTIFICATION_NUMBER];
} Database;

#endif
