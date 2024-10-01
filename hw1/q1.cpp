#include <iostream>
#include <cstdlib>
#include <chrono>
#include <iomanip>
#include <fstream>

int *insert(int *array, int length, int index, int value){
    // no index or invalid input --> return a null pointer
    if (index < 0 || index > length){
        return nullptr;
    }

    // an array doesn't already exist
    if (length == 0){
        // declare newArray and allocate memory equal to a single int variable
        int* newArray = (int*)malloc(sizeof(int));

        // return null pointer if cannot create newArray (or newArray doesn't exist)
        if (!newArray){
            return nullptr;     
        }
        
        // place given value as first index of newArray and return it
        newArray[0] = value;
        return newArray;
    } else{
        // if length of array is not 0 --> allocate enough memory for array length + 1 (for insert)
        int* newArray = (int*)malloc(sizeof(int) * (length+1));

        if (!newArray){
            return nullptr;
        }
        
        // Copy original array into newArray up to where new value is inserted
        for (int i = 0; i < index; ++i){
            newArray[i] = array[i];
        }

        // Insert new value into the specified index
        newArray[index] = value;

        // Copy the rest of the array following the newly inserted value
        for (int i = index; i<length ; ++i){
            newArray[i+1] = array[i];
        }

        // Free up memory allocated (prevent memory leak) and return resulting array (with insert)
        free(array);

        return newArray;
    }
}

int main(){
    // declare constant
    const int INSERTS_PER_READING = 1000;
    
    // set seed for random
    srand(time(0));

    // Open file to save data
    std::ofstream profilingData("profiling_data.txt");
    
    // Output header
    profilingData <<"Array Length           " << "Seconds per insert" << std::endl;

    // delcare empty array and length variable
    int* array = nullptr;
    int length = 0;

    // Loop through the insert into array 60 times
    for (int i = 0; i < 60; ++i){
        auto startTime = std::chrono::system_clock::now();

        // Insert a random value into a random index (0, length) up to specified amount of times
        for (int i =0; i < INSERTS_PER_READING; ++i){
            int index = rand() % (length + 1);
            int value = rand();
            array = insert(array, length, index, value);

            // increase length of array each time
            ++length;
        }

        auto stopTime = std::chrono::system_clock::now();

        // calculate elapsed time using a double (minimum precision of at least 15 decimals)
        std::chrono::duration<double> elapsedTime = stopTime - startTime;
        double timePerInsert = elapsedTime.count() / INSERTS_PER_READING; 

        // write data to file
        profilingData << length << "                  " << 
        std::fixed << std::setprecision(6) << timePerInsert << std::endl;
    }

    // free up allocated memory (prevent memory leak)
    free(array);
    return 0;
}