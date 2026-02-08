#include"types.h"

/* DISPLAY DATABASE */
int display_database(hash_t *hash)
{
    printf("---------------------------------------------------------\n");

    for(int i = 0; i < 28; i++)
    {
        main_node *temp = hash[i].link;

        while(temp)
        {
            printf("[%d] [%s] %d file/s:",i, temp->word, temp->file_count);
            sub_node *sub = temp->sub_link;

            while(sub)
            {
                printf(" File:%s %d times", sub->file_name, sub->word_count);
                sub = sub->sub_link;
            }

            printf("\n");
            temp = temp->main_link;
        }
    }
    printf("---------------------------------------------------------\n");
}