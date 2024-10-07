#include "list.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

void appendTerm(List *pPolynomial, double constant) {
    ListElmt *element = pPolynomial->tail;              // Get tail of list

    // Allocate memory for the constant
    double *new_constant = (double *)malloc(sizeof(double));
    if (new_constant == NULL) {                         // In case of invalidd input
        std::cout << "Invalid input found" << '\n';
        exit(EXIT_FAILURE);
    }

    *new_constant = constant;                           // Set new constant variable to given value

    // Append new_constant to end of the list
    if (list_ins_next(pPolynomial, element, new_constant) !=0) {
        std::cout << "Could not append term" << 'n';
        exit(EXIT_FAILURE);
    }
}

void display(List *pPolynomial) {
    ListElmt *element = pPolynomial->head;               // Start with the first term
    
    int exponent = list_size(pPolynomial) -1;           // Starting/highest exponent is number of exponents -1 because final term is a constant
    int firstTerm = true;

    while (element != NULL) {
        double coeff = *(double *)(element->data);      // coefficient is current term in the list

        // Insert + and - signs in between each term
        if (coeff != 0.0) {                             // Skip all 0.0 values
            if (coeff > 0 && !firstTerm) {              // Exclude very first term
                std::cout << " + ";
            } else if (coeff < 0) {
                std::cout << " - ";
                coeff = -coeff;                         // Remove negative sign as it was printed above
            }
            
            // Print whole numbers with ".0"
            std::cout << std::fixed << std::setprecision(1); 

            // Print correct exponent values on x
            if (exponent == 0) {        
                std::cout << coeff;                     // Constant term
            } else if (exponent == 1) {
                std::cout << coeff << "x";              // x with no exponents
            } else {
                std::cout << coeff << "x^" << exponent; // x with corresponding exponents
            }
    
            firstTerm = false;                              // Set to 0 after first loop (after first term)
        }
        element = element->next;
        exponent--;
        
    } 

    std::cout << std::endl;
}

double evaluate() {
    return 0;
}

int main() {
    List polynomial;

    // Initialize polynomial
    list_init(&polynomial, free);                       // clean up data

    // Append terms
    appendTerm(&polynomial, 6.0);
    appendTerm(&polynomial, 0.0);
    appendTerm(&polynomial, -5.3);
    appendTerm(&polynomial, 3.1);

    // Display polynomial
    display(&polynomial);

    // Clean up list
    list_destroy(&polynomial);

    return 0;
}