/*
Name:D SIVANANDA KUMAR
Reg no:25017_071
Project Name:INVERTED SEARCH
Project Description: This project demonstrates how to create an inverted index, which is commonly used in search 
engines to map words to the documents.The purpose of storing an index is to optimize speed and performance in finding 
relevant documents for a search query. Without an index, the search engine would scan every document in the corpus, 
which would require considerable time and computing power.

An inverted index is an index data structure storing a mapping from content, such as words or numbers, to its
locations in a database file, or in a document or a set of documents. The purpose of an inverted index is to allow
fast full text searches, at the cost of increased processing when a document is added to the database. The inverted
file may be the database file itself, rather than its index. It is the most popular data structure used in document
retrieval systems, used on a large scale for example in search engines
*/
#include "types.h"

int main(int argc,char *argv[])
{
    slist *head=NULL;
    slist *temp = head;
    hash_t hash[28];

    for(int i = 0; i < 28; i++)
        hash[i].link = NULL;

    // Step 1: Read and validate input files
    if (read_and_validate(argc, argv, &head) == FAILURE)
    {
        printf(RED"File validation failed....\n"RESET);
        return 0;
    }

    printf(GREEN"\nFiles validated and added to linked list successfully.\n"RESET);

    int choice;
    char filename[50];
    char backup[50];
    char cont = 'y';

    while(cont == 'y' || cont == 'Y')
    {
        printf(BLUE"\n1.Create DATABASE\n"RESET);
        printf(YELLOW"2.Display Database\n"RESET);
        printf(MAGENTA"3.Save DATABASE\n"RESET);
        printf(CYAN"4.Search\n"RESET);
        printf(GREEN"5.Update DATABASE\n"RESET);
        printf(RED"6.Exit\n"RESET);
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf(GREEN"Enter the file name: "RESET);
                scanf("%s", filename);
                create_database(hash, filename);
                break;

            case 2:
                display_database(hash);
                break;

            case 3:
                printf(MAGENTA"Enter the file name to save database: "RESET);
                scanf("%s", backup);
                save_database(hash, backup);
                break;
            case 4:
                search_word(hash);
                break;
            case 5: 
            {
                char word[50];
                char file_name[50];

                printf(YELLOW"Enter the word to update: "RESET);
                scanf("%s", word);

                printf(CYAN"Enter the file name where the word is found: "RESET);
                scanf("%s", file_name);

                int size = 28;  // number of buckets in your hash table

                update_database(hash, size, word, file_name);
                printf(GREEN"Database updated successfully.\n"RESET);
                break;
            }
            
            case 6:
                printf(RED"Exit\n"RESET);
                return 0;

            default:
                printf(YELLOW"Invalid choice!\n"RESET);
        }

        printf(BLUE"Do you want to continue??? Enter Y/y to continue: "RESET);
        scanf(" %c", &cont);
    }
    return 0;
}    