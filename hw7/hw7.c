#include "heap.h"
#include <stdio.h>
#include <string.h>

void outputSorted (const Person people [], int numPeople,
                    int (*compare) (const void *pKey1, const void *pKey2)) {
    
    // a1. initialize a Heap with the given compare function
    Heap heap;
    heap_init(&heap, compare, NULL);

    // a2. insert the people into the heap
    for (int i=0; i < numPeople; i++) {
        heap_insert(&heap, &people[i]);
    }

    // a3. extract and output each person from the heap
    Person *currentPerson;
    while (heap_size(&heap) > 0) {
        heap_extract(&heap, (void**)&currentPerson);
        printf("Name: %s, Age: %d, Height: %.2fm\n", 
               currentPerson->name, 
               currentPerson->age, 
               currentPerson->height);
    }

    heap_destroy(&heap);
}

int compareName(const void *pKey1, const void *pKey2) {
    const Person *p1 = (const Person *)pKey1;
    const Person *p2 = (const Person *)pKey2;

    // Sort by name
    return strcmp(p2->name, p1->name);
}

int compareAge(const void *pKey1, const void *pKey2) {
    const Person *p1 = (const Person *)pKey1;
    const Person *p2 = (const Person *)pKey2;

    // Sort by age
    return p2->age - p1->age;
}

int compareHeight(const void *pKey1, const void *pKey2) {
    const Person *p1 = (const Person *)pKey1;
    const Person *p2 = (const Person *)pKey2;

    // Sort by height (precision issues when subtracting doubles with each other)
    if (p2->height > p1->height) return 1;
    if (p2->height < p1->height) return -1;
    return 0;
}

int main() {
    Person people[] = {
        {"Jeff", 23, 1.73},
        {"Sean", 23, 1.75},
        {"Hugh", 61, 1.78},
        {"Joann", 67, 1.60},
        {"Yuka", 21, 1.50}
    };
    
    outputSorted(people, 5, compareHeight);
    return 0;
}