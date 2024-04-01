#include "pthread.h"

typedef struct {
    pthread_rwlock_t rwlock;
} rwlock_excl_t;

void rwlock_excl_acquire(rwlock_excl_t *lock);

void rwlock_excl_release(rwlock_excl_t *lock);

void rwlock_excl_init(rwlock_excl_t *lock);

void rwlock_excl_destroy(rwlock_excl_t *lock);