#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 26

struct Trie {
    int count;
    struct Trie *children[SIZE];
};

void insert(struct Trie **ppTrie, char *word) {
    if (*ppTrie == NULL) {
        *ppTrie = (struct Trie *)malloc(sizeof(struct Trie));
        (*ppTrie)->count = 0;
        for (int i = 0; i < SIZE; i++) {
            (*ppTrie)->children[i] = NULL;
        }
    }

    if (*word == '\0') {
        (*ppTrie)->count++;
        return;
    }

    int index = *word - 'a';
    insert(&((*ppTrie)->children[index]), word + 1);
}

int numberOfOccurances(struct Trie *pTrie, char *word) {
    if (pTrie == NULL) {
        return 0;
    }
    if (*word == '\0') {
        return pTrie->count;
    }
    int index = *word - 'a';
    return numberOfOccurances(pTrie->children[index], word + 1);
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < SIZE; i++) {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

int main(void) {
    struct Trie *trie = NULL;

    // Read the number of the words in the dictionary
    // Parse line by line, and insert each word into the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg", "ucf", "no", "corg", "corg"};
    int numWords = sizeof(pWords) / sizeof(pWords[0]);

    for (int i = 0; i < numWords; i++) {
        insert(&trie, pWords[i]);
    }

    char *uniqueWords[] = {"notaword", "ucf", "no", "note", "corg"};
    int numUniqueWords = sizeof(uniqueWords) / sizeof(uniqueWords[0]);

    for (int i = 0; i < numUniqueWords; i++) {
        printf("\t%s : %d\n", uniqueWords[i], numberOfOccurances(trie, uniqueWords[i]));
    }

    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
}


