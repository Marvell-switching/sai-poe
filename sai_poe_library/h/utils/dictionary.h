#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    uint64_t key;
    void* value;
} KeyValuePair;

typedef struct {
    KeyValuePair* entries;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary* create_dictionary(size_t initial_size);
void destroy_dictionary(Dictionary* dict);
bool dict_put(Dictionary* dict, uint64_t key, void* value);
void* dict_get(Dictionary* dict, uint64_t key);
bool dict_get_first(Dictionary* dict, KeyValuePair* first);
bool dict_get_last(Dictionary* dict, KeyValuePair* last);
bool dict_get_next(Dictionary* dict, uint64_t key, KeyValuePair* next);
bool dict_remove(Dictionary* dict, uint64_t key);

#endif /* DICTIONARY_H */
