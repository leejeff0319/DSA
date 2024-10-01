#include <iostream>
#include <cstdlib>
#include <chrono>
#include <iomanip>
#include <fstream>

int *insert(int *array, int length, int index, int value){
    // no index or invalid input --> return a null pointer
    if (index < 0 || index > length){                                                       // O(1)
        return nullptr;                                                                     // O(1)
    }

    // an array doesn't already exist
    if (length == 0){                                                                       // O(1)
        // declare newArray and allocate memory equal to a single int variable
        int* newArray = (int*)malloc(sizeof(int));                                          // O(1)

        // return null pointer if cannot create newArray (or newArray doesn't exist)
        if (!newArray){                                                                     // O(1)
            return nullptr;                                                                 // O(1)
        }
        
        // place given value as first index of newArray and return it
        newArray[0] = value;                                                                // O(1)
        return newArray;                                                                    // O(1)
    } else{
        // if length of array is not 0 --> allocate enough memory for array length + 1 (for insert)
        int* newArray = (int*)malloc(sizeof(int) * (length+1));                             // O(1)                                       

        if (!newArray){                                                                     // O(1)                                                        
            return nullptr;                                                                 // O(1)                                                           
        }                                                                   
        
        // Copy original array into newArray up to where new value is inserted
        for (int i = 0; i < index; ++i){                                                    // O(n)
            newArray[i] = array[i];                                                         // O(1)
        }

        // Insert new value into the specified index
        newArray[index] = value;                                                            // O(1)

        // Copy the rest of the array following the newly inserted value
        for (int i = index; i<length ; ++i){                                                // O(n)
            newArray[i+1] = array[i];                                                       // O(1)
        }

        // Free up memory allocated (prevent memory leak) and return resulting array (with insert)
        free(array);                                                                        // O(1)

        return newArray;                                                                    // O(1)
    }
}

int main(){
    // declare constant
    const int INSERTS_PER_READING = 1000;                                                   // O(1)
    
    // set seed for random
    srand(time(0));                                                                         // O(1)

    // Open file to save data
    std::ofstream profilingData("profiling_data.txt");                                      // O(1)
    
    // Output header
    profilingData <<"Array Length           " << "Seconds per insert" << std::endl;         // O(1)

    // delcare empty array and length variable
    int* array = nullptr;                                                                   // O(1)
    int length = 0;                                                                         // O(1)

    // Loop through the insert into array 60 times
    for (int i = 0; i < 60; ++i){                                                           // O(1)
        auto startTime = std::chrono::system_clock::now();                                  // O(1)

        // Insert a random value into a random index (0, length) up to specified amount of times
        for (int i =0; i < INSERTS_PER_READING; ++i){                                       // O(1)
            int index = rand() % (length + 1);                                              // O(1)
            int value = rand();                                                             // O(1)
            array = insert(array, length, index, value);                                    // O(n)

            // increase length of array each time
            ++length;                                                                       // O(1)
        }

        auto stopTime = std::chrono::system_clock::now();                                   // O(1)

        // calculate elapsed time using a double (minimum precision of at least 15 decimals)
        std::chrono::duration<double> elapsedTime = stopTime - startTime;
        double timePerInsert = elapsedTime.count() / INSERTS_PER_READING; 

        // write data to file
        profilingData << length << "                  " << 
        std::fixed << std::setprecision(6) << timePerInsert << std::endl;                   // O(1)
    }

    // free up allocated memory (prevent memory leak)
    free(array);                                                                            // O(1)
    return 0;
}