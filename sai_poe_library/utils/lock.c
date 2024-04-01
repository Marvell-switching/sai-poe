#include "inc/lock.h"

void rwlock_excl_acquire(rwlock_excl_t *lock) {
    pthread_rwlock_wrlock(&lock->rwlock);
}

void rwlock_excl_release(rwlock_excl_t *lock) {
    pthread_rwlock_unlock(&lock->rwlock);
}

void rwlock_excl_init(rwlock_excl_t *lock) {
    pthread_rwlock_init(&lock->rwlock, NULL);
}

void rwlock_excl_destroy(rwlock_excl_t *lock) {
    pthread_rwlock_destroy(&lock->rwlock);
}