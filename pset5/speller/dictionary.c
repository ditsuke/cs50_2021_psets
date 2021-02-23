// Implements a dictionary's functionality

#include "dictionary.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdint.h>

// Represents a node in a hash table
typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 0.75 * 143091;

// Hash table
node *table[N];

// Ptrs for latest nodes in linked lists
node *listend[N];

// Dictionary size
int dictsize = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word) {
    // Hash value for passed word
    int hashc = hash(word);
    // Bool to tell if word is in dictionary
    bool isIn = false;
    node *llp = table[hashc];
    while (true) {
        int comp = strcasecmp(word, llp->word);
        if (comp == 0) {
            // Break if found
            isIn = true;
            break;
        } else if (comp > 0 && llp->next != NULL) {
            // Advance linked list pos ptr, jump to next iteration
            llp = llp->next;
            continue;
        } else {
            // Break if lexicographic position of word has passed
            break;
        }
    }
    return isIn;
}

// Hashes word to a number using the djb2 algo
unsigned int hash(const char *word) {
    unsigned long hash = 5381;
    int c;

    while ((c = *word++)) {
        c = ((c >= 97 && c <=122) ? c - 97 : (c >= 65 && c <=90) ? c - 65 : c);
        // hash * 33 + c (<<5 uses left shift to achieve this more efficiently)
        hash = ((hash << 5) + hash) + c;
    }
    // Cap hash at N-1 and return
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
    FILE *dictstr;
    dictstr = fopen(dictionary, "r");
    // Return false if unable to open dictionary file
    if (dictstr == NULL) {
        return false;
    }

    // Initialise first nodes and listend ptrs
    for (int i = 0; i < N; ++i) {
        table[i] = calloc(1, sizeof(node));
        listend[i] = table[i];
    }

    char cword[LENGTH + 1];
    // Stores fscanf return, EOF when file has been read
    int word_read = 0;
    do {
        word_read = fscanf(dictstr, "%s\n", cword);
        if (word_read == EOF) {
            break;
        }
        // Increment dictionary size
        ++dictsize;
        // Stores word hash
        unsigned int chash = hash(cword);
        strcpy(listend[chash]->word, cword);
        // Allocate memory for next node in linked list
        listend[chash]->next = calloc(1, sizeof(node));
        // Advance ptr
        listend[chash] = listend[chash]->next;
    } while (true);

    fclose(dictstr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
    return dictsize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
    for (int i = 0; i < N; ++i) {
        node *ll = table[i];
        node *llr;
        while (true) {
            llr = ll;
            if (ll->next != NULL) {
                ll = ll->next;
                free(llr);
            } else {
                free(llr);
                break;
            }
        }
    }
    return true;
}