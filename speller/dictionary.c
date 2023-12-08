// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

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
int word_count;

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    // somehow loop through the linked list
    node *tmp_address = table[index];
    while (tmp_address != NULL)
    {
        if (strcasecmp(tmp_address->word, word) == 0)
        {
            return true;
        }
        else
        {
            tmp_address = tmp_address->next;
        }
    }
    return false;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    bool success = false;
    char word[LENGTH + 1];
    FILE *file = fopen(dictionary, "r");

    // TODO
    while (fscanf(file, "%s", word) != EOF)
    {
        node *string = calloc(1, sizeof(node));
        if (string == NULL)
        {
            unload();
            return false;
        }
        if (string != NULL)
        {
            strcpy(string->word, word);
            int index = hash(word);
            node *head = table[index];
            if (table[index] == NULL)
            {
                table[index] = string;
                success = true;
                word_count++;
            }
            else
            {
                node *tmp_add = table[index];
                table[index] = string;
                string->next = tmp_add;
                success = true;
                word_count++;
            }
        }
    }
    printf("%i\n", word_count);
    fclose(file);
    return success;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (word_count > 0)
    {
        return word_count;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *current_address = table[i];
        while (current_address != NULL)
        {
            node *tmp_address = current_address;
            current_address = current_address->next;
            free(tmp_address);
        }
        if (current_address == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
