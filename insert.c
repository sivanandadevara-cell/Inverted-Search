#include "types.h"

/*add the files*/
int insert_at_last(slist **head, char *filename)
{
   // Step 1: Create new node
   slist *new = malloc(sizeof(slist));
   if (new == NULL)
   {
      printf(RED"Memory allocation failed for %s\n"RESET, filename);
      return FAILURE;
   }

   // Step 2: Initialize new node
   strcpy(new->file_name,filename);
   new->link = NULL;

   // Step 3: If list empty → new node becomes head
   if (*head == NULL)
   {
      *head = new;
      return SUCCESS;
   }

   // Step 4: Traverse to last node
   slist *temp = *head;
   while (temp->link != NULL)
   {
      temp = temp->link;
   }

   // Step 5: Attach at end
   temp->link = new;

   return SUCCESS;
}


//duplicate files checking...
int search_file(slist *head, char *filename)
{
   while (head != NULL)
   {
      if (strcmp(head->file_name, filename) == 0)
      {
        // File found
        return SUCCESS;
      }
      head = head->link;
   }
   // File not found
   return FAILURE;
}

/*checking the validation*/
int read_and_validate(int argc, char *argv[], slist **head)
{
    
    if(argc == 1)
    {
        printf(RED"[FAILURE] No input files provided.\n"RESET);
        printf(RED"[INFO] Usage : ./a.out <file1.txt> <file2.txt> ...\n"RESET);
        return FAILURE;
    }

    // Loop through all filenames given in command line
    for (int i = 1; i < argc; i++)
    {
        // Check if file has .txt extension
        char *extn = strrchr(argv[i], '.');
        if (extn == NULL || strcmp(extn, ".txt") != 0)
        {
            printf(RED"This file '%s' — not a .txt file.\n"RESET, argv[i]);
            continue;
        }

        //opening file
        FILE *fptr = fopen(argv[i], "r");
        if (fptr == NULL)
        {
            printf(RED"This file '%s' — unable to open.\n"RESET, argv[i]);
            continue;
        }

        // Check if file is empty
        fseek(fptr, 0, SEEK_END);
        if (ftell(fptr) == 0)
        {
            printf(RED"This file '%s' — empty file.\n"RESET, argv[i]);
            fclose(fptr);
            continue;
        }
        rewind(fptr);

        // Check if file already exists in list (avoid duplicates)
        if (search_file(*head, argv[i]) == SUCCESS)
        {
            printf(RED"Repeated '%s' — duplicate file.\n"RESET, argv[i]);
            fclose(fptr);
            continue;
        }

        // Add file to linked list
        insert_at_last(head, argv[i]);

        fclose(fptr);
    }
    return SUCCESS;
}

/*converting the ASCII to interger with special characters*/
int get_index(char *word)
{
    if(word[0] >= 'A' && word[0] <= 'Z')
        return word[0] - 'A';
    else if(word[0] >= 'a' && word[0] <= 'z')
        return word[0] - 'a';
    else if(word[0] >= '0' && word[0] <= '9') 
        return 26;
    else 
        return 27;
}
