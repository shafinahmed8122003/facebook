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
int find_user_using_id(Database *db, User *user, USER_ID id);
int create_an_user(Database *db, User *user, char name[], char username[], char password[]);
USER_ID generate_unique_id();
int show_options(char options[][50], int option_count, int *current_option);
void draw_line(int length);
void show_title(char title[]);
void show_title_in_box(char title[]);
int find_user_by_username(Database *db, User *user, char username[]);
time_t get_current_time();
void create_post(Database *db, User *user, char post_content[]);
void create_new_buffer();
void kill_current_buffer();
void update_user_data(Database *db, User *user);
void delete_user(Database *db, User *user);

#endif
