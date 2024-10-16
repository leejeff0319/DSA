#include <iostream>
#include <stdio.h>
#include <string.h>
#include "qksort.h"

#define MAX_STRING_LENGTH 100

typedef struct Car_ {
	char make [MAX_STRING_LENGTH];
	char model [MAX_STRING_LENGTH];
	int mpg;	/* Miles per gallon */
} Car;

int compareCarsByMakeThenModel(const void *car1, const void *car2) {
    const Car *c1 = (const Car *)car1;
    const Car *c2 = (const Car *)car2;

    // Compare by make
    int compare = strcmp(c1->make, c2->make);           // strcmp compares two strings alphabetically
    if (compare != 0) {                                 // if two strings aren't equivalent values
        return compare;                                 // < 0 means c1 is alphabetically smaller
    }

    // return model if make is same
    return strcmp(c1->model, c2->model);                       
}

int compareCarsByDescendingMPG(const void *car1, const void *car2) {
    const Car *c1 = (const Car *)car1;
    const Car *c2 = (const Car *)car2;

    // compare mpg if make is same
    if (c1->mpg < c2->mpg) {                            // same as strcmp but for integers
        return 1;                                       // except <0 means c2 is smaller
    } else if (c1->mpg > c2->mpg) {
        return -1;                                      // results flipped since desc instead of asc
    } else{
        return 0;
    }
}

int compareCarsByMakeThenDescendingMPG(const void *car1, const void *car2) {
    const Car *c1 = (const Car *)car1;
    const Car *c2 = (const Car *)car2;

    // Compare by make
    int compare = strcmp(c1->make, c2->make);           // strcmp compares two strings alphabetically
    if (compare != 0) {                                 // if two strings aren't equivalent values
        return compare;                                 // < 0 means c1 is alphabetically smaller
    }

    // If make is same, compare mpg (desc)
    return compareCarsByDescendingMPG(car1, car2);
}

void displayCars(const Car cars[], int numCars) {
    for (int i = 0; i < numCars; i++) {
        printf("%s %s, MPG: %d\n", cars[i].make, cars[i].model, cars[i].mpg);
    }
}

int main() {
    Car cars[] = {
        {"Toyota", "Camry", 33},
        {"Ford", "Focus", 40},`
        {"Honda", "Accord", 34},
        {"Ford", "Mustang", 31},
        {"Honda", "Civic", 39},
        {"Toyota", "Prius", 48},
        {"Honda", "Fit", 35},
        {"Toyota", "Corolla", 35},
        {"Ford", "Taurus", 28}
    };
    
    int numCars = sizeof(cars)/sizeof(cars[0]);

    // Output (dis`laying make, model, and MPG) the cars in original unsorted order
    std::cout << "1: Original order" << std::endl;;
    displayCars(cars,numCars);

    // Output the cars sorted (using qksort from the book) by make then model.
    std::cout << "\n2. Sorted: Make then Model" << std::endl;
    qksort(cars, numCars, sizeof(Car), 0, numCars - 1, compareCarsByMakeThenModel);
    displayCars(cars,numCars);

    // Output the cars sorted (using qksort from the book) by descending MPG.
    std::cout << "\n3. Descending MPG" << std::endl;;
    qksort(cars, numCars, sizeof(Car), 0, numCars - 1, compareCarsByDescendingMPG);
    displayCars(cars,numCars);

    // Output the cars sorted (using qksort from the book) by make then descending MPG.
    std::cout << "\n4. Make then Descending MPG" << std::endl;;
    qksort(cars, numCars, sizeof(Car), 0, numCars - 1, compareCarsByMakeThenDescendingMPG);
    displayCars(cars,numCars);

    return 0;
}