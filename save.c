#include "types.h"

/*SAVE DATABASE TO FILE*/
int save_database(hash_t *hash, char *backup)
{
    FILE *fp = fopen(backup, "w");

    for(int i = 0; i < 28; i++)
    {
        main_node *temp = hash[i].link;

        while(temp)
        {
            fprintf(fp, "#;%s;%d;", temp->word, temp->file_count);

            sub_node *sub = temp->sub_link;

            while(sub)
            {
                fprintf(fp, "%s;%d;", sub->file_name, sub->word_count);
                sub = sub->sub_link;
            }
            fprintf(fp, "#\n");
            temp = temp->main_link;
        }
    }

    fclose(fp);
    printf(GREEN"Database is saved\n"RESET);
}
