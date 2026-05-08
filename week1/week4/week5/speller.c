#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Node yapısı
typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
} node;

// Bucket sayısı (N). Ne kadar büyükse o kadar hızlı çalışır.
const unsigned int N = 10000;
node *table[N];
unsigned int word_count = 0;

// Hash Fonksiyonu
unsigned int hash(const char *word) {
    unsigned long hash_val = 5381;
    int c;
    while ((c = tolower(*word++))) {
        hash_val = ((hash_val << 5) + hash_val) + c;
    }
    return hash_val % N;
}

// Sözlüğü Yükle
bool load(const char *dictionary) {
    FILE *file = fopen(dictionary, "r");
    if (file == NULL) return false;

    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF) {
        node *n = malloc(sizeof(node));
        if (n == NULL) return false;
        
        strcpy(n->word, word);
        unsigned int h = hash(word);
        n->next = table[h];
        table[h] = n;
        word_count++;
    }
    fclose(file);
    return true;
}

// Kelime sayısını döndür
unsigned int size(void) {
    return word_count;
}

// Kelimeyi kontrol et
bool check(const char *word) {
    node *cursor = table[hash(word)];
    while (cursor != NULL) {
        if (strcasecmp(cursor->word, word) == 0) return true;
        cursor = cursor->next;
    }
    return false;
}

// Hafızayı boşalt
bool unload(void) {
    for (int i = 0; i < N; i++) {
        node *cursor = table[i];
        while (cursor != NULL) {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
