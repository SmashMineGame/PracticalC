#ifndef _HASHBROWN_H
#define _HASHBROWN_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct hashbrown hashbrown;

// Creates a new hash table with the given number of
// buckets for values. bucket_count must be > 0.
hashbrown *hb_make(size_t bucket_count);

size_t hb_len(const hashbrown *hb);

void hb_dump(const hashbrown *hb);

void hb_set(hashbrown *hb, const char *key, int val);

bool hb_get(const hashbrown *hb, const char *key, int *value);

bool hb_remove(hashbrown *hb, const char *key);

void hb_free(hashbrown *hb);

#endif