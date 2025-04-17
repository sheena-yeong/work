// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>  // For free()
#include <string.h>  // For strcmp
#include <strings.h> // For strcasecmp()

#include "dictionary.h"

int word_count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash word to obtain a hash value
    int hash_value = hash(word); // Find out hash value of word you want to spell-check
    node *cursor =
        table[hash_value]; // Create a cursor and start pointing at the start of the table

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) ==
            0) // Compare the word that cursor is pointing at to word you want to spell-check
        {
            return true;
        }
        else
        {
            cursor = cursor->next; // Point cursor at where the next is currently pointing at
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    // NULL-ify the hash table, as node *table[N]; creates N number of pointers to garbage values
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Open dictionary file
    FILE *dict_file = fopen(dictionary, "r");
    if (dict_file == NULL)
    {
        printf("Unable to open dictionary file.\n");
        return false;
    }

    // Read strings from file one at a time
    char buffer[45];
    while (
        fscanf(dict_file, "%s", buffer) !=
        EOF) // fscanf will check till end of file. So you want it to continue while its not at EOF
    {
        // Create a new node for each word
        node *new_word = malloc(sizeof(node));
        if (new_word == NULL)
        {
            return false;
        }
        int hash_value = hash(buffer);      // Hash word to obtain a hash value
        strcpy(new_word->word, buffer);     // Copy string from buffer to new node
        new_word->next = table[hash_value]; // Connect to existing chain (or NULL in 1st iteration).
                                            // This is like saying "Point new_word->next to wherever
                                            // table[hash_value] is currently pointing at now"
        table[hash_value] = new_word;       // Make new node the head of the chain
        word_count++;
    }
    fclose(dict_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Free everything using 2 variables tmp and cursor

    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
