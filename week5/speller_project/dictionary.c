// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// I chose a prime number at 150k - 200k range because it will guarante us with less collisions
const unsigned int TABLE_SIZE = 200003;

// Prime number for Polynomial Rolling Hash algorithm
const unsigned int PRIME_HASH = 31;

// Hash table
node *table[TABLE_SIZE];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word to obtain its hash value
    unsigned int index = hash(word);
    // Search the hash table at the location specified by the word’s hash value
    for (node *ptr = table[index]; ptr != NULL; ptr = ptr->next)
    {
        // Compare the strings in a case-insensitve way with strcasecmp()
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
    }
    // Return false if no word is found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    if (word == NULL)
    {
        return 1;
    }
    unsigned int sum = 0;
    // Traverse through the word and add each character ASCII number to sum
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Polynomial Rolling Hash Algorithm
        sum = (sum * PRIME_HASH + tolower(word[i])) % TABLE_SIZE;
    }
    // Return sum for index value
    return sum;
}
// Polynomial rolling hash adapted from reference:
// https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        printf("Cannot open file.\n");
        return false;
    }
    // Create a buffer array for each word from dictionary
    char buffer[LENGTH + 1];
    // Read each word in the file
    while (fscanf(source, "%45s", buffer) == 1)
    {
        // Create space for a new hash table
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Memory error.\n");
            return false;
        }
        // Copy the word into the new node
        strcpy(n->word, buffer);
        // Hash the word to obtain its hash value
        unsigned int index  = hash(buffer);
        // Insert the new node into the hash table (using the index specified by its hash value)
        n->next = table[index];
        table[index] = n;
    }
    // Close the dictionary file
    fclose(source);
    // Load is successful
    return true;
}

unsigned int size(void)
{
    unsigned int counter = 0;
    // Loop through all buckets
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        // Traverse the linked list at table[i]
        for (node *ptr = table[i]; ptr != NULL; ptr = ptr->next)
        {
            counter++;
        }
    }
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // For each bucket in the hash table
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        // Traverse the linked list at table[i]
        for (node *ptr = table[i]; ptr != NULL;)
        {
            // Temporarily store the current node pointer
            node *tmp = ptr;
            // Move on to the next node before freeing
            ptr = ptr->next;
            // Free the current (old) node
            free(tmp);
        }
    }
    return true;
}
