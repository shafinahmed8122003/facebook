#ifndef TYPES_H
#define TYPES_H

typedef struct
{
    int id;
    char name[50];
    char username[50];
    char password[50];
    int profile_locked; // 0 - False & 1 - True
    int posts_id[500];
    int friends_id[500];
    int notifications_id[500];
} User;

typedef struct
{
    int id;
    char content[500];
    unsigned long long int timestamp;
    int author_id;
    int likes;
    int comments_id[500];
    int shares;
} Post;

typedef struct
{
    int id;
    char content[500];
    unsigned long long int timestamp;
    int author_id;
} Comment;

typedef struct
{
    int id;
    char content[500];
    unsigned long long int timestamp;
} Notification;

typedef struct
{
    User users[500];
    Post posts[1000000];
    Comment comments[1000000];
    Notification notifications[1000000];
} Database;

#endif
