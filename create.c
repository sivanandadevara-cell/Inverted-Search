#include"types.h"

/* CREATE DATABASE */
int create_database(hash_t *hash, char *filename)
{
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf(RED"File %s cannot be opened\n"RESET, filename);
        return 0;
    }

    char word[50];

    while(fscanf(fp, "%s", word) != EOF)
    {
        int index = get_index(word);
        if(index == -1)
            continue;

        main_node *temp = hash[index].link;
        main_node *prev = NULL;

        // ---------- Search for existing main node ----------
        while(temp)
        {
            if(strcmp(temp->word, word) == 0)
                break;
            prev = temp;
            temp = temp->main_link;
        }

        // CASE 1: Word already exists → update sub list
        if(temp)
        {
            sub_node *sub = temp->sub_link;
            sub_node *sub_prev = NULL;

            // --- Search sub list for filename ---
            while(sub)
            {
                if(strcmp(sub->file_name, filename) == 0)
                    break;
                sub_prev = sub;
                sub = sub->sub_link;
            }

            // filename exists → increase count
            if(sub)
            {
                sub->word_count++;
            }
            else
            {
                // filename not found → create new sub node
                sub_node *new_sub = malloc(sizeof(sub_node));
                strcpy(new_sub->file_name, filename);
                new_sub->word_count = 1;
                new_sub->sub_link = temp->sub_link;
                temp->sub_link = new_sub;

                temp->file_count++;
            }
        }
        // CASE 2: Word does NOT exist → create new main + sub
        else
        {
            // create main node
            main_node *new_main = malloc(sizeof(main_node));
            strcpy(new_main->word, word);
            new_main->file_count = 1;
            new_main->main_link = hash[index].link;

            // create first sub node
            sub_node *new_sub = malloc(sizeof(sub_node));
            strcpy(new_sub->file_name, filename);
            new_sub->word_count = 1;
            new_sub->sub_link = NULL;

            new_main->sub_link = new_sub;

            // insert main at head
            hash[index].link = new_main;
        }
    }

    fclose(fp);
    printf(GREEN"Database created for %s\n"RESET, filename);
    return 1;
}
