#ifndef SCREENS_H
#define SCREENS_H

#include <stdio.h>
#include "utils.h"

int ScreenAuth();
int ScreenLogin(Database *db, User *user);
int ScreenSignup(Database *db, User *user);
int ScreenMainmenu(User *user);

#endif