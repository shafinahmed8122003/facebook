#ifndef TYPES_H
#define TYPES_H

typedef struct
{
    char name[50];
    char username[50];
    char password[50];
    int profile_locked; // 0 - False & 1 - True
} User;

#endif
