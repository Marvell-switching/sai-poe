/*
 *  Copyright (C) 2024, MARVELL. All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may
 *    not use this file except in compliance with the License. You may obtain
 *    a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *    THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR
 *    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 *    LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 *    FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 *    See the Apache Version 2.0 License for specific language governing
 *    permissions and limitations under the License.
 *
 */

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
