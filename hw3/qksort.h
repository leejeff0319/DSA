#ifndef QKSORT_H
   #define QKSORT_H

   #ifdef __cplusplus
   extern "C" {
   #endif

   int qksort(void *data, int size, int esize, int i, int k,
              int (*compare)(const void *key1, const void *key2));

   #ifdef __cplusplus
   }
   #endif

   #endif