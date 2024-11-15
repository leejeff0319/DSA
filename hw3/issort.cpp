/*
 * issort.c
 */
extern "C" {
#include <stdlib.h>
#include <string.h>
}
#include "sort.h"

int issort(void *data, int size, int esize,
        int (*compare)(const void *key1, const void *key2))
{
    char *a = static_cast<char*>(data);
    void *key;
    int   i,
          j;

    /* Allocate storage for the key element. */
    if ((key = (char *)malloc(esize)) == NULL)
        return -1;

    /* Repeatedly insert a key element among the sorted elements. */
    for (j = 1; j < size; j++) {
        memcpy(key, &a[j * esize], esize);
        i = j - 1;

        /* Determine the position at which to insert the key element. */
        while (i >= 0 && compare(&a[i * esize], key) > 0) {
            memcpy(&a[(i + 1) * esize], &a[i * esize], esize);
            i--;
        }

        memcpy(&a[(i + 1) * esize], key, esize);
    }

    /* Free the storage allocated for sorting. */
    free(key);

    return 0;
}
