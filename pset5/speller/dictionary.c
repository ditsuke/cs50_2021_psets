// Implements a dictionary's functionality

#include "dictionary.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

// Linked list end pointers
node *listend[N];

// dictionary size
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
            isIn = true;
            break;  // break if found
        } else if (comp > 0 && llp->next != NULL) {
            llp = llp->next;
            continue;
        } else {
            break;  // break if lexicographic position of word has passed
        }
    }
    return isIn;
}

// Hashes word to a number
unsigned int hash(const char *word) {
    // for N = 676
    unsigned int nhash, c1, c2;
    c1 = ((word[0] >= 97 && word[0] <=122) ? word[0] - 97 : (word[0] >= 65 && word[0] <=90) ? word[0] - 65 : 0);
    c2 = ((word[1] == '\0') ? (0) : ((word[1] >= 97 && word[1] <=122) ? word[1] - 97 : (word[1] >= 65 && word[1] <=90) ? word[1] - 65 : 0));
    nhash = 26 * c1 + 1 * c2;  // Needs case insensitivity (TODO -- done?)
    return nhash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
    FILE *dictstr;
    dictstr = fopen(dictionary, "r");
    // return false if unable to open dictionary file
    if (dictstr == NULL) {
        return false;
    }

    // Initialise first nodes and listend ptrs
    for (int i = 0; i < N; i++) {
        table[i] = malloc(sizeof(node));
        listend[i] = table[i];
        strcpy(listend[i]->word, "");
        listend[i]->next = NULL;
    }

    char cword[LENGTH + 1];
    int word_read = 0;
    do {
        word_read = fscanf(dictstr, "%s\n", cword);
        if (word_read == EOF) {
            break;
        }
        dictsize++;
        unsigned int chash = hash(cword);
        strcpy(listend[chash]->word, cword);
        listend[chash]->next = malloc(sizeof(node));
        listend[chash] = listend[chash]->next;
        strcpy(listend[chash]->word, "");
        listend[chash]->next = NULL;
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
    for (int i = 0; i < N; i++) {
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
