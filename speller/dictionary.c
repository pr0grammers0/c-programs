// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>

// Represents number of buckets in a hash table
#define N 26
int B = 0;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // TODO
        node *newnode = malloc(sizeof(node));
        if (newnode == NULL)
        {
            unload();
            return false;
        }
        strcpy(newnode->word, word);
        newnode->next = hashtable[hash(word)];
        hashtable[hash(word)] = newnode;
        B++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return B;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int len = strlen(word);
    bool flag = false;
    node *cursor = hashtable[hash(word)];
    while (cursor != NULL)
    {
        if (strlen(cursor->word) == len)
        {
            for (int i = 0; i < len; i++)
                if (tolower(cursor->word[i]) != tolower(word[i]))
                {
                    flag = false;
                    break;
                }
                else
                {
                    flag = true;
                }
        }
        if (flag)
        {
            return flag;
        }
        cursor = cursor->next;
        
    }
    return flag;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        while (hashtable[i] != NULL)
        {
            node *tmp = hashtable[i];
            hashtable[i] = hashtable[i]->next;
            free(tmp);
        }
    }
    return true;
}
