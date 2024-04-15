#include <h/utils/dictionary.h>

Dictionary* create_dictionary(size_t initial_size) {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL; // Return NULL to indicate failure
    }
    dict->entries = (KeyValuePair*)malloc(initial_size * sizeof(KeyValuePair));
    if (dict->entries == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(dict); // Free previously allocated memory
        return NULL; // Return NULL to indicate failure
    }
    dict->size = 0;
    dict->capacity = initial_size;
    return dict; // Return the created dictionary
}

void destroy_dictionary(Dictionary* dict) {
    if (dict != NULL) {
        free(dict->entries);
        free(dict);
    }
}

bool dict_put(Dictionary* dict, uint64_t key, void* value) {
    if (dict == NULL) {
        return false; // Dictionary is not initialized
    }
    if (dict->size >= dict->capacity) {
        // Resize the dictionary if it's full
        dict->capacity *= 2;
        KeyValuePair* new_entries = realloc(dict->entries, dict->capacity * sizeof(KeyValuePair));
        if (new_entries == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            return false; // Return false to indicate failure
        }
        dict->entries = new_entries;
    }
    dict->entries[dict->size].key = key;
    dict->entries[dict->size].value = value;
    dict->size++;

    return true; // Return true to indicate success
}

void* dict_get(Dictionary* dict, uint64_t key) {
    for (size_t i = 0; i < dict->size; ++i) {
        if (dict->entries[i].key == key) {
            return dict->entries[i].value;
        }
    }
    return NULL; // Key not found
}

bool dict_get_first(Dictionary* dict, KeyValuePair* first) {
    if (dict == NULL || dict->size == 0 || first == NULL) {
        return false;
    }
    *first = dict->entries[0];
    return true;
}

bool dict_get_last(Dictionary* dict, KeyValuePair* last) {
    if (dict == NULL || dict->size == 0 || last == NULL) {
        return false;
    }
    *last = dict->entries[dict->size - 1];
    return true;
}

bool dict_get_next(Dictionary* dict, uint64_t key, KeyValuePair* next) {
    if (dict == NULL || dict->size == 0 || next == NULL) {
        return false;
    }
    for (size_t i = 0; i < dict->size - 1; ++i) {
        if (dict->entries[i].key == key) {
            *next = dict->entries[i + 1];
            return true;
        }
    }
    return false;
}

bool dict_remove(Dictionary* dict, uint64_t key) {
    if (dict == NULL) {
        return false;
    }
    for (size_t i = 0; i < dict->size; ++i) {
        if (dict->entries[i].key == key) {
            // Free memory associated with the value
            free(dict->entries[i].value);
            
            // Remove the key-value pair by shifting elements
            for (size_t j = i; j < dict->size - 1; ++j) {
                dict->entries[j] = dict->entries[j + 1];
            }
            dict->size--;
            return true;
        }
    }
    return false; // Key not found
}