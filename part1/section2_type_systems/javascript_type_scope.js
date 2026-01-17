/**
 * JavaScript: Type Systems and Closures Demonstration
 * Demonstrates: Dynamic typing, closures, variable scope, type coercion
 */

console.log("=".repeat(60));
console.log("JAVASCRIPT: Type Systems and Closures Demo");
console.log("=".repeat(60));

// ============================================================
// PART 1: CLOSURES AND SCOPE
// ============================================================

function createMultiplier(factor) {
    let count = 0; // Variable in enclosing scope
    
    return function(x) {
        count++;
        console.log(`  Multiply called ${count} times`);
        return x * factor;
    };
}

console.log("\n--- Closures Demo ---");
const timesThree = createMultiplier(3);
const timesFive = createMultiplier(5);

console.log("Using timesThree closure:");
console.log(`  Result: ${timesThree(10)}`);  // 30
console.log(`  Result: ${timesThree(20)}`);  // 60

console.log("\nUsing timesFive closure:");
console.log(`  Result: ${timesFive(10)}`);   // 50
console.log(`  Result: ${timesFive(7)}`);    // 35

// ============================================================
// PART 2: DYNAMIC TYPING
// ============================================================

function flexibleCalculator(a, b, operation) {
    switch(operation) {
        case "add":
            return a + b;
        case "multiply":
            return a * b;
        case "concat":
            return String(a) + String(b);
        default:
            return null;
    }
}

console.log("\n--- Dynamic Typing Demo ---");
console.log(`Number addition: ${flexibleCalculator(5, 3, "add")}`);  // 8
console.log(`Float addition: ${flexibleCalculator(5.5, 2.5, "add")}`);  // 8.0
console.log(`String concat: ${flexibleCalculator("Hello", "World", "concat")}`);
console.log(`Array addition: ${flexibleCalculator([1, 2], [3, 4], "add")}`);  // "1,23,4" (!!)

// ============================================================
// PART 3: TYPE COERCION (Weak Typing)
// ============================================================

console.log("\n--- Type Coercion Demo ---");
console.log(`"5" + 3 = ${"5" + 3}`);      // "53" (string concatenation)
console.log(`"5" - 3 = ${"5" - 3}`);      // 2 (numeric subtraction)
console.log(`"5" * 3 = ${"5" * 3}`);      // 15 (numeric multiplication)
console.log(`true + 1 = ${true + 1}`);    // 2 (boolean coercion)
console.log(`false + 1 = ${false + 1}`);  // 1
console.log(`"5" == 5: ${"5" == 5}`);     // true (type coercion)
console.log(`"5" === 5: ${"5" === 5}`);   // false (strict equality)

// ============================================================
// PART 4: RUNTIME TYPE CHECKING
// ============================================================

console.log("\n--- Runtime Type Checking ---");
let value = 42;
console.log(`value = ${value}, type = ${typeof value}`);

value = "Now I'm a string";
console.log(`value = ${value}, type = ${typeof value}`);

value = [1, 2, 3];
console.log(`value = ${value}, type = ${typeof value}`);  // "object" (!!)

value = {key: "dict"};
console.log(`value = ${JSON.stringify(value)}, type = ${typeof value}`);

// ============================================================
// PART 5: VARIABLE SCOPE (var vs let vs const)
// ============================================================

console.log("\n--- Variable Scope Demo ---");

// Global scope
var globalVar = "I'm global (var)";
let globalLet = "I'm global (let)";

function scopeDemo() {
    var functionVar = "I'm function scoped";
    let blockLet = "I'm block scoped";
    
    console.log(`  Inside function - functionVar: ${functionVar}`);
    console.log(`  Inside function - blockLet: ${blockLet}`);
    
    if (true) {
        var ifVar = "I'm var in if";  // Function scoped!
        let ifLet = "I'm let in if";  // Block scoped!
        console.log(`  Inside if - ifVar: ${ifVar}`);
        console.log(`  Inside if - ifLet: ${ifLet}`);
    }
    
    console.log(`  After if - ifVar: ${ifVar}`);  // Accessible (var)
    // console.log(ifLet);  // Error: ifLet is not defined (let)
}

scopeDemo();
console.log(`Outside function - globalVar: ${globalVar}`);
// console.log(functionVar);  // Error: not defined

// ============================================================
// PART 6: HOISTING
// ============================================================

console.log("\n--- Hoisting Demo ---");

console.log(`  varVariable before declaration: ${typeof varVariable}`); // undefined
var varVariable = "I'm hoisted";

// console.log(letVariable);  // Error: Cannot access before initialization
let letVariable = "I'm not hoisted";

console.log("\n" + "=".repeat(60));