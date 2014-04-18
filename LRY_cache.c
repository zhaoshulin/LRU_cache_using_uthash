#include <string.h>
#include <stdio.h>
#include "uthash.h"
#include <stdlib.h>
#include "LRY_cache.h"

#define MAX_CACHE_SIZE 100000

struct CacheEntry {
    char *key;
    char *value;
    UT_hash_handle hh;
};
struct CacheEntry *cache = NULL;

char find_in_cache(char *key)
{
    struct CacheEntry *entry;
    HASH_FIND_STR(cache, key, entry);
    if (entry) {
        printf("<%s,%s> cache hit!\n", key, entry->value);
        // remove it (so the subsequent add will throw it on the front of the list)
        HASH_DELETE(hh, cache, entry);
        HASH_ADD_KEYPTR(hh, cache, entry->key, strlen(entry->key), entry);
        return *entry->value;
    }

    printf("key=%s cache miss!\n", key);
    return -1;
}

void add_to_cache(char *key, char *value)
{
    struct CacheEntry *entry, *tmp_entry;
    entry = malloc(sizeof(struct CacheEntry));
    entry->key = strdup(key);
    entry->value = strdup(value);
    HASH_ADD_KEYPTR(hh, cache, entry->key, strlen(entry->key), entry);

    printf(" <%s,%s> add to cache succeed!\n",key, value);

    // prune the cache to MAX_CACHE_SIZE
   // if (HASH_COUNT(cache) >= MAX_CACHE_SIZE) {
     //   HASH_ITER(hh, cache, entry, tmp_entry) {
            // prune the first entry (loop is based on insertion order so this deletes the oldest item)
       //     HASH_DELETE(hh, cache, entry);
         //   free(entry->key);
           // free(entry->value);
          //  free(entry);
           // break;
       // }
   // }
}

int main(void)
{
	printf("main is ok\n");
    char *test_key1 = "a";
    char *test_value1 = "b";

    char *test_key2 = "x";
    char *test_value2 = "y";

    add_to_cache(test_key1, test_value1);
    add_to_cache(test_key2, test_value2);

    find_in_cache("a");
    find_in_cache("c");
	return 0;
	}
