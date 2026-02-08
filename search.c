#include"types.h"

/*SEARCH WORD IN  DATABASE*/
int search_word(hash_t *hash)
{
    char word[50];
    printf(BLUE"Enter the word you want search: "RESET);
    scanf("%s", word);

    int index = get_index(word);
    if(index == -1)
    {
        printf(RED"Invalid word\n"RESET);
        return 0;
    }

    main_node *temp = hash[index].link;

    while(temp)
    {
        if(strcmp(temp->word, word) == 0)
        {
            printf(CYAN"String %s is present in %d file(s)\n"RESET, word, temp->file_count);

            sub_node *sub = temp->sub_link;

            while(sub)
            {
                printf("In File: %s %d time(s)\n", sub->file_name, sub->word_count);
                sub = sub->sub_link;
            }
            return 1;
        }

        temp = temp->main_link;
    }
    printf(RED"Word not found!\n"RESET);
}
