// Implements a dictionary's functionality using a hash table

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
// Using a prime number like 10007 helps reduce collisions
const unsigned int N = 10007;

// Hash table
node *table[N];

// Global variable to keep track of dictionary size
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word to get the index
    unsigned int index = hash(word);

    // Access the linked list at that index
    node *cursor = table[index];

    // Traverse the linked list
    while (cursor != NULL)
    {
        // Compare word case-insensitively
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number (djb2 algorithm)
unsigned int hash(const char *word)
{
    unsigned long hash_val = 5381;
    int c;

    while ((c = tolower(*word++)))
    {
        hash_val = ((hash_val << 5) + hash_val) + c; // hash * 33 + c
    }

    return hash_val % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Buffer to store each word read from file
    char word_buffer[LENGTH + 1];

    // Read each word until end of file
    while (fscanf(file, "%s", word_buffer) != EOF)
    {
        // Allocate memory for a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            return false;
        }

        // Copy word into the node
        strcpy(new_node->word, word_buffer);

        // Get hash index
        unsigned int index = hash(word_buffer);

        // Insert node into the hash table (at the head of the list)
        new_node->next = table[index];
        table[index] = new_node;

        // Increment the word counter
        word_count++;
    }

    // Close dictionary file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over every bucket in the hash table
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        // Free the linked list at this bucket
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    return true;
}
