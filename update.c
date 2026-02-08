#include"types.h"

/*UPDATE THE DATABASE TO FILE*/
int update_database(hash_t *hash, int size,char *word,char *file_name)
{
    int index = hash_function(word, size);

    main_node *temp = hash[index].link;
    main_node *prev = NULL;

  
    //1. Search if main-node (word) exists
    while (temp)
    {
        if (strcmp(temp->word, word) == 0)
        {
            // word exists → check sub-node (file)
            sub_node *s = temp->sub_link;
            sub_node *s_prev = NULL;

            while (s)
            {
                if (strcmp(s->file_name, file_name) == 0)
                {
                    // file exists → increase count
                    s->word_count++;
                    return 1;
                }
                s_prev = s;
                s = s->sub_link;
            }

            // file not found → create new sub-node
            sub_node *new_sub = malloc(sizeof(sub_node));
            strcpy(new_sub->file_name, file_name);
            new_sub->word_count = 1;
            new_sub->sub_link = temp->sub_link;  // insert at head
            temp->sub_link = new_sub;

            temp->file_count++;  // new file added
            return SUCCESS;
        }

        prev = temp;
        temp = temp->main_link;
    }

    // 2. Word not found → create new main-node
    main_node *new_main = malloc(sizeof(main_node));
    strcpy(new_main->word, word);
    new_main->file_count = 1;

    // create first sub-node
    sub_node *first_sub = malloc(sizeof(sub_node));
    strcpy(first_sub->file_name, file_name);
    first_sub->word_count = 1;
    first_sub->sub_link = NULL;

    new_main->sub_link = first_sub;

    // insert the main node at head of bucket
    new_main->main_link = hash[index].link;
    hash[index].link = new_main;
    return SUCCESS;
}

/*creating the hash table*/
int hash_function(char *word, int size)
{
    int sum = 0;
    for (int i = 0; word[i]; i++)
        sum += word[i];
    return sum % size;
}
