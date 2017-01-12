/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// create word to be read in load function 
char word[LENGTH + 1];

// define node structure
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

// create hashtable
node* hashtable[SIZE];

// create numwords count
unsigned int numwords = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    // which bucket would the word be in?
    // first loop through word and make lowercase
    char lower_word[strlen(word) + 1];
    strcpy(lower_word, word);
    
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        lower_word[i] = tolower(lower_word[i]);
    }
    
    int index = hash_function(lower_word);
    
    node* cursor = hashtable[index];
    
    // check if word is in dictionary at index
    while(cursor != NULL)
    {
        // traverse through linked list comparing word
        bool are_words_equal = strcmp(lower_word, cursor->word) == 0;
        if (are_words_equal)
        {
            return true;
        }
        
        cursor = cursor->next;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // initialize hashtable indices to point to NULL
    for (int i = 0; i < SIZE; i++)
    {
        hashtable[i] = NULL;
    }
    
    // open dictionary file
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        fclose(fp);
        return false;
    }
    
    // read in each word from the dictionary
    
    // previous while condition was "while(feof)", that did not work because it could allocate
    // more memory than needed for new_node(s).
    // It's better to read using fscanf and check if it was a valid read
    
    while(fscanf(fp, "%s", word) == 1)
    {
        // create new node for each word
        node* new_node = malloc(sizeof(node));
        
        // check if malloc failed
        if (new_node == NULL)
        {
            printf("Could not allocate space for word: %s.\n", word);
            return false;
        }
        
        // copy read word from dictionary into new_node
        strcpy(new_node->word, word);
        
        // initialize new_node's next pointer to NULL
        new_node->next = NULL;
        
        // get hash code for each word
        int index = hash_function(new_node->word);
        
        // create head pointer of hashtable index
        node* head = hashtable[index];
        
        // if head of hashtable[index] = NULL, then place new_node at beginning of linked list
        if (head == NULL)
        {
            hashtable[index] = new_node;
        // if hashtable[index] not equal to NUll then insert new_node as first in list
        // by pointing new_node->next to head of list and then making hashtable[index] point to new_node
        // to make new_node new head of list
        } else if (head != NULL)
        {
            new_node->next = head;
            hashtable[index] = new_node;
        }
        
        numwords++;
    }
    
    // check to see if any file errors
    if (ferror(fp))
    {
        return false;
    }
    
    // close dictionary file
    fclose(fp);
    
    // return that dictionary was loaded successfully
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return numwords;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // for each element of hashtable array
    // loop through and free each node of linked list at that hashtable index
    for (int i = 0, n = SIZE; i < n; i++)
    {
        // get head of list for each element
        node* cursor = hashtable[i];
        
        // progress cursor while freeing previous node with temp node
        while(cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}

/**
 * Determines placement of string in hashtable. Returns index of location in hashtable.
 */
unsigned int hash_function(const char* key)
{
    int sum = 0;

    for (int i = 0; key[i] != '\0'; i++)
    {
        sum += key[i];
    }

    return sum % SIZE;
}