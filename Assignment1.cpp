/*
Assignment 1
Sarah Miller
I couldn't figure out how to open my text file in my source code. However I think my code's logic still stands.
I would love to have some advice on how to open the input text file in my code please. 
*/

#include <iostream> // input output stream
#include <fstream> // file stream

const int MAX_SIZE = 100; // Maximum size of the array

// Function to check if a certain integer exists in the array and return the index
int findIndex(const int arr[], int size, int num) { // function takes parameters of an array, the size of the array and the number.
    for (int i = 0; i < size; ++i) { // this for loop iterates through the array 
        if (arr[i] == num) { // if the number is found then the following happens:
            return i; // Return the index if number is found
        }
    }
    return -1; // Return -1 if number is not found
}

// Function to modify the value of an integer at a specific index in the array
void modifyValue(int arr[], int size, int index, int newValue, int& oldValue) { // function that takes in the array, size of the array, index, new value and oldvalue. An exception
    if (index < 0 || index >= size) { // if the index is less than 0 or is greater than the array size the following exception will be thrown:
        throw std::out_of_range("Index out of bounds."); 
    }
    
    oldValue = arr[index]; // Store the old value before modification
    arr[index] = newValue; // Modify the value at the specified index
}

// Function to add a new integer to the end of the array
void addInteger(int arr[], int& size, int newValue) { // function that adds an integer. Takes in account of the array, the size of array and the new input Value. 
    if (size >= MAX_SIZE) { // If the new input value is greater than the max size of my array, the exception will be thrown:
        throw std::overflow_error("Array is full, cannot add more elements.");
    }
    
    arr[size++] = newValue; // Adds the new integer to the end of the array
}

// Function to replace the value at a specific index with 0 or remove it altogether
void replaceOrRemove(int arr[], int size, int index, bool remove) { // function that has parameters of the array, the size of the array, the index and the ability to remove a value.
    if (index < 0 || index >= size) { // if index is less than 0 or if the index is bigger than the size of the array the following exception will be thrown:
        throw std::out_of_range("Index out of bounds.");
    }
    
    if (remove) { // 
        for (int i = index; i < size - 1; ++i) {
            arr[i] = arr[i + 1]; // Shift elements to the left to remove the integer
        }
        size--; // Decrease the size of the array
    } else {
        arr[index] = 0; // Replace the value at the specified index with 0
    }
}

int main() {
    int arr[MAX_SIZE]; // One-dimensional array
    int size = 0; // Size of the array
    
    std::ifstream inputFile("A1input.txt"); // Open the input file
    
    // Check if the file opened successfully
    if (!inputFile) {
        std::cerr << "Error: Unable to open the input file." << std::endl;
        return 1; // Return error code
    }
    
    // Read data from the file into the array
    int num;
    while (inputFile >> num && size < MAX_SIZE) {
        arr[size++] = num; // Read and store the number in the array, then increment the size
    }
    
    // Close the input file
    inputFile.close();
    
    // Function to check if a certain integer exists in the array and return the index
    int numToFind = 5; // selected integer to test if it exists in the array
    int index = findIndex(arr, size, numToFind); // index = findIndex function
    if (index != -1) { 
        std::cout << "Number " << numToFind << " found at index " << index << std::endl;
    } else {
        std::cout << "Number " << numToFind << " not found in the array." << std::endl;
    }
    
    // Function to modify the value of an integer at a specific index in the array
    int oldValue; // the previous value will be stored here
    int newIndex = 2;
    int newValue = 10;
    try { // try and catch block
        modifyValue(arr, size, newIndex, newValue, oldValue);
        std::cout << "Old value: " << oldValue << ", New value: " << arr[newIndex] << std::endl;
    } catch (const std::out_of_range& e) { // when the value is not in the expected range an error message will occur.
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    // Function to add a new integer to the end of the array
    int newValueToAdd = 12;
    try {
        addInteger(arr, size, newValueToAdd);
        std::cout << "New value added to the end: " << arr[size - 1] << std::endl;
    } catch (const std::overflow_error& e) { // An error will appear when an arthimetic overflow has occured.
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    // Function to replace the value at a specific index with 0 or remove it altogether
    int indexToReplace = 1; 
    bool remove = false;
    try {
        replaceOrRemove(arr, size, indexToReplace, remove); // function that takes in account of the array, size, index to replace, and removal of one.
        std::cout << "Value at index " << indexToReplace << " replaced with 0: " << arr[indexToReplace] << std::endl; // this will replaces index with a 0
    } catch (const std::out_of_range& e) { // if the index is out of range the following message will occur as an error.
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    int indexToRemove = 3;
    remove = true;
    try {
        replaceOrRemove(arr, size, indexToRemove, remove);
        std::cout << "Value at index " << indexToRemove << " removed." << std::endl; // removes index rather than replaces it.
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0; // Return success code
}
