// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <strings.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = (LENGTH + 1) * 'z';
int word_count = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Hash word to obtain hash value
    int index = hash(word);
    //Access linked list at that index in the hash table

    //Traverse linked list looking for the word

    node *traverse = table[index];
    while ( traverse != NULL)
    {
        if (strcasecmp (traverse->word, word) == 0)
        {
            return true;
        }
        traverse = traverse->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    return (sum % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open a dictionary file
    FILE *df = fopen (dictionary, "r'") ;
    if(df == NULL)
    {
        return false;
    }
    //Read strings from a file one at a time
    char word[LENGTH + 1] ;
    while (fscanf(df, "%s", word) != EOF)
    {
        // Create a new node for each word

        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        strcpy(new_node->word , word);
        new_node->next = NULL;

        // Hash word to obtain hash value

        int index = hash(word);

        // Insert node into hash table at that location
        if(table[index] == NULL)
        {
            table[index] = new_node;
        }
        else
        {
        new_node->next = table[index];
        table[index] = new_node;
        }
        word_count++;
    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    for ( int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = cursor;
        while ( cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
