// JavaScript: Calculate the sum of an array
// This file contains INTENTIONAL ERRORS for analysis

// VERSION 1: Original errors from assignment
function calculateSum(arr) {
    let total = o;  // ERROR 1: letter 'o' instead of 0
    for (let num of arr) {
        total += num;
    }
    return total;
}

let numbers = [1, 2, 3, 4, 5];
let result = calculate Sum(numbers);  // ERROR 2: space in function name
console.log("Sum in JavaScript:", result);


// VERSION 2: Additional error - Missing bracket
/*
function calculateSumV2(arr) {
    let total = 0;
    for (let num of arr) {
        total += num;
    // ERROR 3: Missing closing bracket
    return total;
}
*/


// VERSION 3: Additional error - Invalid property name
/*
let obj = {
    1name: "test"  // ERROR 4: Property name starts with number
};
*/


// VERSION 4: Additional error - Unexpected token
/*
function calculateSumV4(arr) {
    let total = 0;
    for (let num of arr) {
        total += num;
    }
    return total
}  // ERROR 5: Missing semicolon can cause issues in some contexts

let result = calculateSumV4([1,2,3])
console.log(result)
*/


// CORRECTED VERSION (uncomment to test)
/*
function calculateSumCorrect(arr) {
    let total = 0;  // Fixed: Changed 'o' to 0
    for (let num of arr) {
        total += num;
    }
    return total;
}

let numbers = [1, 2, 3, 4, 5];
let result = calculateSumCorrect(numbers);  // Fixed: Removed space
console.log("Sum in JavaScript:", result);
*/