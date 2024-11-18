#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "types.h"
#include "constants.h"

void initialize_database(Database *db);
void save_data(Database *db);
void load_data(Database *db);
void clear_screen();
void hide_cursor();
void show_cursor();
int find_user_using_username_password(Database *db, User *user, char username[], char password[]);
int create_an_user(Database *db, User *user, char name[], char username[], char password[]);
unsigned long long int generate_unique_id();
int show_options(char title[], char options[][50], int option_count);

#endif