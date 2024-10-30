#include <stdio.h>
#include "chtbl.h"

int hash(const void* key) {
    return *(const int*)key;
}

int match(const void* key1, const void* key2) {
    return (*(int *)key1 == *(int *)key2);
}

int main() {
    // initailize variables
    int numBuckets = 5;
    double maxLoadFactor = 0.5;
    double resizeMultiplier = 2.0;

    // Initialialize hash table
    CHTbl htbl;
    chtbl_init(&htbl, numBuckets, hash, match, free, maxLoadFactor, resizeMultiplier);

    // Insert new data onto the table
    int *data;
    for (int i = 1; i <= 3; i++) {
        data = (int *)malloc(sizeof(int));
        if (data == NULL) {
            fprintf(stderr, "Failed to allocate memory for data\n");
            chtbl_destroy(&htbl);
            return 1;
        }
        *data = i;

        chtbl_insert(&htbl, data);

        /* Output current state after each insert */
        printf("buckets %d, elements %d, lf %.2f, max lf %.2f, resize multiplier %.1f\n",
               htbl.buckets, htbl.size, (double)htbl.size / htbl.buckets, htbl.maxLoadFactor, htbl.resizeMultiplier);
    }

    // Clean up table
    chtbl_destroy(&htbl);

    return 0;
}