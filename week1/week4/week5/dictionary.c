#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // Required for strcasecmp

#include "dictionary.h"

// ---------------------------------------------------------------------------
// HASH TABLE CONFIGURATION
// ---------------------------------------------------------------------------
// Using a larger N for better performance. 
// 10007 is a prime number that helps distribute words more evenly.
#define N 10007

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// ---------------------------------------------------------------------------
// GLOBALS
// ---------------------------------------------------------------------------
node *table[N];
unsigned int word_count = 0; // Global counter for size()

// ---------------------------------------------------------------------------
// TODO 1: hash()
// ---------------------------------------------------------------------------
unsigned int hash(const char *word)
{
    // Using the djb2 hash algorithm for better distribution
    unsigned long hash_val = 5381;
    int c;
    while ((c = tolower(*word++)))
    {
        hash_val = ((hash_val << 5) + hash_val) + c; /* hash * 33 + c */
    }
    return hash_val % N;
}

// ---------------------------------------------------------------------------
// TODO 2: load()
// ---------------------------------------------------------------------------
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    // Read words one by one until EOF
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory for a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return false;
        }

        // Copy word into node
        strcpy(n->word, word);

        // Hash the word to find its bucket
        unsigned int index = hash(word);

        // Prepend node to the linked list in that bucket
        n->next = table[index];
        table[index] = n;

        // Increment the global word counter
        word_count++;
    }

    // Close the file
    fclose(file);
    return true;
}

// ---------------------------------------------------------------------------
// TODO 3: check()
// ---------------------------------------------------------------------------
bool check(const char *word)
{
    // Hash the word to find the bucket index
    unsigned int index = hash(word);

    // Walk the linked list in that bucket
    for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
    {
        // Compare case-insensitively
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }

    return false;
}

// ---------------------------------------------------------------------------
// TODO 4: size()
// ---------------------------------------------------------------------------
unsigned int size(void)
{
    // Return the count calculated during load()
    return word_count;
}

// ---------------------------------------------------------------------------
// TODO 5: unload()
// ---------------------------------------------------------------------------
bool unload(void)
{
    // Loop over all N buckets
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        // Free every node in this bucket's linked list
        while (cursor != NULL)
        {
            node *next_node = cursor->next; // Save the pointer to next BEFORE freeing
            free(cursor);
            cursor = next_node;
        }
    }

    return true;
}
