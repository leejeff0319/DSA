#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "list.h"

void addLargeNumbers(const char *pNum1, const char *pNum2) {
    // initialize stacks
    Stack stack1, stack2, resultStack;
    stack_init(&stack1, free);
    stack_init(&stack2, free);
    stack_init(&resultStack, free);

    // Read the numerals of the first number and store them on one stack
    for (int i = 0; i < strlen(pNum1); i++) {         // Read from last char of the string
        char *digit = (char *)malloc(sizeof(char));
        *digit = pNum1[i];
        stack_push(&stack1, digit);
    }

    // Read the numerals of the second number and store them on another stack
    for (int i = 0; i < strlen(pNum2); i++) {
        char *digit = (char *)malloc(sizeof(char));
        *digit = pNum2[i];
        stack_push(&stack2, digit);
    }
    
    // Initialize carry variable
    int carry = 0;

    // While at least one stack is not empty
    while (stack_size(&stack1) > 0 || stack_size(&stack2) > 0 || carry > 0) {
        int num1_digit = 0, num2_digit = 0;

        // Pop a numeral from each nonempty stack 
        if (stack_size(&stack1) > 0) {
            char *top;
            stack_pop(&stack1, (void **)&top);
            num1_digit = *top - '0';                        // Convert from char to int
            free(top);
        }

        if (stack_size(&stack2)> 0) {
            char *top;
            stack_pop(&stack2, (void **)&top);
            num2_digit = *top - '0';                        // Convert from char to int
            free(top);
        }

        // Add them to result
        int result = num1_digit + num2_digit + carry;
        carry = result / 10;                                // Carry is either 1 or 0 (truncated)
        result %= 10;                                       // Result is one's digit

        /* Push the unit part of addition onto resultStack */
        char *result_digit = (char *)malloc(sizeof(char));
        *result_digit = (result % 10) + '0';                // Convert from int back to char
        stack_push(&resultStack, result_digit);
    }

    // Pop numbers from resultStack and display them 
    printf("%s + %s = ", pNum1, pNum2);
    while (list_size(&resultStack) > 0) {
        char *top;
        stack_pop(&resultStack, (void **)&top);
        printf("%c", *top);
        free(top);
    }
    printf("\n");

    // Destroy stacks
    stack_destroy(&stack1);
    stack_destroy(&stack2);
    stack_destroy(&resultStack);
}

int main() {
    addLargeNumbers("592", "3784");
    addLargeNumbers("21309124087670231230213", "21841201231233112312231");
    addLargeNumbers("9223372036854775809", "9223372036854775809");
    addLargeNumbers("88223372036854775809", "12223372036854775809");
    return 0;
}