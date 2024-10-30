/*
 * chtbl.c
 */
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "list.h"
#include "chtbl.h"

int chtbl_init(CHTbl *htbl, int buckets, int(*h)(const void *key), int(*match)(
        const void *key1, const void *key2), void(*destroy)(void*data), 
        double maxLoadFactor, double resizeMultiplier) {

    int i;

    /* Allocate space for the hash table. */
    if ((htbl->table = (List *) malloc(buckets * sizeof(List))) == NULL)
        return -1;

    /* Initialize the buckets. */
    htbl->buckets = buckets;

    for (i = 0; i < htbl->buckets; i++)
        list_init(&htbl->table[i], destroy);

    /* Encapsulate the functions. */
    htbl->h = h;
    htbl->match = match;
    htbl->destroy = destroy;
    htbl->maxLoadFactor = maxLoadFactor;
    htbl->resizeMultiplier = resizeMultiplier;

    /* Initialize the number of elements in the table. */
    htbl->size = 0;

    return 0;
}

void chtbl_destroy(CHTbl *htbl) {

    int i;

    /* Destroy each bucket. */
    for (i = 0; i < htbl->buckets; i++) {
        list_destroy(&htbl->table[i]);
    }

    /* Free the storage allocated for the hash table. */
    free(htbl->table);

    /* No operations are allowed now, but clear the structure as a
     * precaution. */
    memset(htbl, 0, sizeof(CHTbl));
}

int chtbl_insert(CHTbl *htbl, const void *data) {

    void *temp;
    int bucket, retval;

    /* Do nothing if the data is already in the table. */
    temp = (void *) data;

    if (chtbl_lookup(htbl, &temp) == 0)
        return 1;

    /* Hash the key

    Change the method by which hash codes are mapped to buckets to use the 
    multiplication method instead of division method. */

    const double A = 0.618034;
    double hashValue = (double)htbl->h(data);
    double product = hashValue * A;
    double fractional = product - floor(product);
    bucket = (int)(htbl->buckets * fractional);

    /* Insert the data into the bucket. */
    if ((retval = list_ins_next(&htbl->table[bucket], NULL, data)) == 0)
        htbl->size++;

        double loadFactor = (double)htbl->size / htbl->buckets;

        // When calculated load factor exceeds maximum load factor
        if (loadFactor > htbl->maxLoadFactor) {
            // New hash size
            int newBuckets = (int)(htbl->buckets * htbl->resizeMultiplier);

            // Create new table
            List *newTable = (List *)malloc(newBuckets * sizeof(List));
            if (newTable == NULL)
                return -1;

            // init new buckets
            for (int i = 0; i < newBuckets; i++) {
                list_init(&newTable[i], htbl->destroy);
            }

            // Rehash existing elements
            ListElmt *element;
            void *tempData;
            for (int i = 0; i < htbl->buckets; i++) {
                element = list_head(&htbl->table[i]);
                while (element != NULL) {
                    tempData = list_data(element);

                    // Calculation for new bucket with multiplicative method
                    hashValue = (double)htbl->h(tempData);
                    product = hashValue * A;
                    fractional = product - floor(product);
                    int newBucket = (int)(newBuckets * fractional);

                    // If insertion fails
                    if (list_ins_next(&newTable[newBucket], NULL, tempData) != 0) {
                        // clear the bucket
                        for (int j = 0; j < newBuckets; j++) {
                            list_destroy(&newTable[j]);
                        }
                        free(newTable);
                        return -1;
                    }
                    element = list_next(element);
                }
            }

            // Free old table buckets but not data
            for (int i = 0; i < htbl->buckets; i++) {
                void (*temp_destroy)(void *data) = htbl->table[i].destroy;
                htbl->table[i].destroy = NULL;
                list_destroy(&htbl->table[i]);
                htbl->table[i].destroy = temp_destroy;
            }
            
            // Free old table and update htbl with new table
            free(htbl->table);
            htbl->table = newTable;
            htbl->buckets = newBuckets;
        }

    return retval;
}

int chtbl_remove(CHTbl *htbl, void **data) {

    ListElmt *element, *prev;
    int bucket;
    const double A = 0.618034;

    /* Hash the key. */
    double hashValue = (double)htbl->h(*data);
    double product = hashValue * A;
    double fractional = product - floor(product);
    bucket = (int)(htbl->buckets * fractional);

    /* Search for the data in the bucket. */
    prev = NULL;

    for (element = list_head(&htbl->table[bucket]); element != NULL; element
            = list_next(element)) {

        if (htbl->match(*data, list_data(element))) {

            /* Remove the data from the bucket. */
            if (list_rem_next(&htbl->table[bucket], prev, data) == 0) {
                htbl->size--;
                return 0;
            }
            else {
                return -1;
            }
        }

        prev = element;
    }

    /* Return that the data was not found. */

    return -1;
}

int chtbl_lookup(const CHTbl *htbl, void **data) {

    ListElmt *element;
    int bucket;
    const double A = 0.618034;

    /* Hash the key. */
    double hashValue = (double)htbl->h(*data);
    double product = hashValue * A;
    double fractional = product - floor(product);
    bucket = (int)(htbl->buckets * fractional);

    /* Search for the data in the bucket. */
    for (element = list_head(&htbl->table[bucket]); element != NULL; element
            = list_next(element)) {

        if (htbl->match(*data, list_data(element))) {

            /* Pass back the data from the table. */
            *data = list_data(element);
            return 0;
        }
    }

    /* Return that the data was not found. */

    return -1;
}