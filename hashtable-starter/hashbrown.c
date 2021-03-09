#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "hashbrown.h"
#include "kvp_list.h"

struct hashbrown
{
    size_t len;

    size_t bucket_count;
    kvp_node *bucket_heads[];
};

uint64_t string_hash(const char *key)
{
    // Shamelessly stolen from https://stackoverflow.com/a/2624210,
    // which is itself a variation on Java's String hash.
    // That's discussed nicely here:
    // https://computinglife.wordpress.com/2008/11/20/why-do-hash-functions-use-prime-numbers/

    uint64_t hash = 7;
    for (size_t i = 0; i < strlen(key); i++)
    {
        hash = hash * 31 + key[i];
    }

    return hash;
}

hashbrown *hb_make(size_t bucket_count)
{
    // bucket_heads is a flexible array member, so we have
    // to explicitly calculate the space we need for its
    // elements. Just using calloc here for the side-effect
    // of it zeroing the memory.
    hashbrown *hb = calloc(1, sizeof(hashbrown) + sizeof(kvp_node *) * bucket_count);
    hb->bucket_count = bucket_count;

    return hb;
}

size_t hb_len(const hashbrown *hb)
{
    return hb->len;
}

// Returns the index to use in the bucket_heads array for a given
// key in the given hashtable.
size_t hb_get_bucket_idx(const hashbrown *hb, const char *key)
{
    // The hash could be anything a uint64_t can handle, so we
    // mod down by the bucket count of the given table to get
    // a valid array index.
    return string_hash(key) % hb->bucket_count;
}

void hb_dump(const hashbrown *hb)
{
    printf("Hash brown @ %p – %zu buckets, %zu entries\n", hb, hb->bucket_count, hb->len);
    if (hb->len != 0)
    {
        printf("Non-empty buckets:\n");
        for (size_t i = 0; i < hb->bucket_count; i++)
        {
            kvp_node *bucket_head = hb->bucket_heads[i];
            if (bucket_head)
            {
                printf("[%zu]: ", i);
                kvp_list_print(bucket_head);
            }
        }
    }

    printf("\n");
}

void hb_set(hashbrown *hb, const char *key, int val)
{
    size_t ind = hb_get_bucket_idx(hb, key);

    if (hb->bucket_heads[ind] == NULL)
    {
        hb->bucket_heads[ind] = kvp_node_make(key, val);
        hb->len++;
        return;
    }

    kvp_node *bucket_list = hb->bucket_heads[ind];
    kvp_node *node = kvp_list_find(bucket_list, key);
    if (node != NULL)
    {
        node->value = val;
        return;
    }

    kvp_list_insert(bucket_list, key, val);
    hb->len++;
}

bool hb_get(const hashbrown *hb, const char *key, int *value)
{
    size_t ind = hb_get_bucket_idx(hb, key);

    if (hb->bucket_heads[ind] == NULL)
    {
        return false;
    }

    kvp_node *bucket_list = hb->bucket_heads[ind];
    kvp_node *node = kvp_list_find(bucket_list, key);
    if (node == NULL)
    {
        return false;
    }
    *value = node->value;
    return true;
}

bool hb_remove(hashbrown *hb, const char *key)
{
    size_t ind = hb_get_bucket_idx(hb, key);

    if (hb->bucket_heads[ind] == NULL)
    {
        return false;
    }

    kvp_node *bucket_list = hb->bucket_heads[ind];
    kvp_node *node = kvp_list_find(bucket_list, key);

    if (node == NULL)
    {
        return false;
    }

    if (node == hb->bucket_heads[ind])
    {
        hb->bucket_heads[ind] = node->next;
    }

    kvp_list_remove(node);
    hb->len--;

    return true;
}

void hb_free(hashbrown *hb)
{
    for (size_t i = 0; i < hb->bucket_count; i++)
    {
        if (hb->bucket_heads[i] != NULL)
        {
            kvp_list_free(hb->bucket_heads[i]);
        }
    }
    free(hb);
}