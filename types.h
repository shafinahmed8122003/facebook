#ifndef TYPES_H
#define TYPES_H

#include "constants.h"

typedef struct
{
    unsigned long long int id;
    char name[50];
    char username[50];
    char password[50];
    int profile_locked; // 0 - False & 1 - True
    int posts_id[100];
    int friends_id[100];
    int notifications_id[100];
} User;

typedef struct
{
    unsigned long long int id;
    char content[100];
    unsigned long long int timestamp;
    int author_id;
    int likes;
    int comments_id[100];
    int shares;
} Post;

typedef struct
{
    unsigned long long int id;
    char content[100];
    unsigned long long int timestamp;
    int author_id;
} Comment;

typedef struct
{
    unsigned long long int id;
    char content[100];
    unsigned long long int timestamp;
} Notification;

typedef struct
{
    User users[TOTAL_USER_NUMBER];
    Post posts[TOTAL_POST_NUMBER];
    Comment comments[TOTAL_COMMENT_NUMBER];
    Notification notifications[TOTAL_NOTIFICATION_NUMBER];
} Database;

#endif
