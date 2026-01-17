// C++: Calculate the sum of an array
// This file contains INTENTIONAL ERRORS for analysis

#include <iostream>
using namespace std;

// VERSION 1: Original errors from assignment
int calculateSum(int arr[], int size)
{
    int total = o; // ERROR 1: letter 'o' instead of 0
    for (int i = o; i < size; i++)
    { // ERROR 2: letter 'o' instead of 0
        total += arr[i];
    }
    return total;
}

int main()
{
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[o]); // ERROR 3: letter 'o'
    int result = calculateSum(numbers, size);
    cout << "Sum in C++"
            " << result << endl;  // ERROR 4: missing << operator
        return o; // ERROR 5: letter 'o' instead of 0
}

// VERSION 2: Additional error - Missing semicolon
/*
int addNumbers(int a, int b) {
    int sum = a + b  // ERROR 6: Missing semicolon
    return sum;
}
*/

// VERSION 3: Additional error - Undeclared variable
/*
int useUndeclared() {
    cout << value << endl;  // ERROR 7: 'value' not declared
    return 0;
}
*/

// VERSION 4: Additional error - Type mismatch
/*
int returnWrongType() {
    return "hello";  // ERROR 8: Returning string from int function
}
*/

// CORRECTED VERSION (uncomment to test)
/*
#include <iostream>
using namespace std;

int calculateSumCorrect(int arr[], int size) {
    int total = 0;  // Fixed: Changed 'o' to 0
    for (int i = 0; i < size; i++) {  // Fixed: Changed 'o' to 0
        total += arr[i];
    }
    return total;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);  // Fixed: Changed 'o' to 0
    int result = calculateSumCorrect(numbers, size);
    cout << "Sum in C++: " << result << endl;  // Fixed: Added << operator
    return 0;  // Fixed: Changed 'o' to 0
}
*/