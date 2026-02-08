#ifndef INVERTED_H
#define INVERTED_H


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define RESET       "\033[0m"
#define RED         "\033[0;31m"
#define GREEN       "\033[0;32m"
#define YELLOW      "\033[0;33m"
#define BLUE        "\033[0;34m"
#define MAGENTA     "\033[0;35m"
#define CYAN        "\033[0;36m"

#define SUCCESS 1
#define FAILURE 0

typedef struct node
{
    char file_name[50];
    struct node *link;
    
} slist;


typedef struct sub_node
{
    int word_count;
    char file_name[50];
    struct sub_node *sub_link;
} sub_node;

typedef struct main_node
{
    int file_count;
    char word[50];
    sub_node *sub_link;
    struct main_node *main_link;
    
} main_node;


typedef struct hash_table
{
    int index;
    main_node *link; 
} hash_t;

int get_index(char *word);
int insert_at_last(slist **head, char *filename);
int search_file(slist *head, char *filename);
int hash_function(char *word, int size);
int read_and_validate(int argc, char *argv[], slist **head);

int create_database(hash_t *hash, char *filename);
int display_database(hash_t *hash);
int search_word(hash_t *hash);
int save_database(hash_t *hash, char *backup);
int update_database(hash_t *hash,int size,char *word, char *file_name);

#endif