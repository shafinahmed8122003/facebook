#ifndef SCREENS_H
#define SCREENS_H

#include <stdio.h>
#include "utils.h"

// All the screen functions prototype

int ScreenAuth();
int ScreenLogin(Database *db, User *user);
int ScreenSignup(Database *db, User *user);
int ScreenMainmenu(User *user);
int ScreenSearch(Database *db, User *user);
void ScreenCreatePost(Database *db, User *user);
int ScreenNewsFeed(Database *db, User *user);
int ScreenSettings(Database *db, User *user);
int ScreenProfile(User user);

#endif
