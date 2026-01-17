/**
 * C++: Type Systems and Closures Demonstration
 * Demonstrates: Static typing, lambdas (closures), strict scope
 */

#include <iostream>
#include <functional>
#include <string>
#include <vector>

using namespace std;

// ============================================================
// PART 1: CLOSURES (Lambdas and Functors)
// ============================================================

// Function object (functor) - traditional way
class Multiplier
{
private:
    int factor;
    mutable int count;

public:
    Multiplier(int f) : factor(f), count(0) {}

    int operator()(int x) const
    {
        count++;
        cout << "  Multiply called " << count << " times" << endl;
        return x * factor;
    }
};

// Modern C++ lambda - returns a closure
auto createMultiplierLambda(int factor)
{
    return [factor, count = 0](int x) mutable
    {
        count++;
        cout << "  Lambda multiply called " << count << " times" << endl;
        return x * factor;
    };
}

// ============================================================
// PART 2: STATIC TYPING - Function Overloading
// ============================================================

// Different functions for different types (compile-time polymorphism)
int calculate(int a, int b)
{
    cout << "  Called int version" << endl;
    return a + b;
}

double calculate(double a, double b)
{
    cout << "  Called double version" << endl;
    return a + b;
}

string calculate(string a, string b)
{
    cout << "  Called string version" << endl;
    return a + b;
}

// ============================================================
// PART 3: TEMPLATES - Type-Safe Generic Programming
// ============================================================

template <typename T>
T add(T a, T b)
{
    return a + b;
}

// ============================================================
// PART 4: VARIABLE SCOPE
// ============================================================

int globalVar = 100; // Global scope

void scopeDemo()
{
    int localVar = 50; // Local to function
    cout << "  Inside function - localVar: " << localVar << endl;
    cout << "  Inside function - globalVar: " << globalVar << endl;

    if (true)
    {
        int ifVar = 25; // Block scoped!
        cout << "  Inside if - ifVar: " << ifVar << endl;
    }

    // cout << ifVar;  // Compile Error: ifVar not in scope
}

// ============================================================
// MAIN FUNCTION
// ============================================================

int main()
{
    cout << string(60, '=') << endl;
    cout << "C++: Type Systems and Closures Demo" << endl;
    cout << string(60, '=') << endl;

    // PART 1: Closures
    cout << "\n--- Closures Demo (Functor) ---" << endl;
    Multiplier timesThree(3);
    Multiplier timesFive(5);

    cout << "Using timesThree functor:" << endl;
    cout << "  Result: " << timesThree(10) << endl; // 30
    cout << "  Result: " << timesThree(20) << endl; // 60

    cout << "\nUsing timesFive functor:" << endl;
    cout << "  Result: " << timesFive(10) << endl; // 50

    // Lambda closures
    cout << "\n--- Closures Demo (Lambda) ---" << endl;
    auto lambdaMultiplier = createMultiplierLambda(4);
    cout << "Using lambda closure:" << endl;
    cout << "  Result: " << lambdaMultiplier(5) << endl;  // 20
    cout << "  Result: " << lambdaMultiplier(10) << endl; // 40

    // PART 2: Static Typing
    cout << "\n--- Static Typing Demo (Overloading) ---" << endl;
    cout << "Int calculation: " << calculate(5, 3) << endl;
    cout << "Double calculation: " << calculate(5.5, 2.5) << endl;
    cout << "String calculation: " << calculate(string("Hello"), string("World")) << endl;

    // PART 3: Templates
    cout << "\n--- Template Demo ---" << endl;
    cout << "Template add<int>: " << add<int>(10, 20) << endl;
    cout << "Template add<double>: " << add<double>(10.5, 20.5) << endl;
    // cout << add<int>(10, 20.5);  // Compile Error: type mismatch

    // PART 4: Type Safety
    cout << "\n--- Type Safety Demo ---" << endl;
    int num = 5;
    // num = "hello";  // Compile Error: cannot assign string to int
    // string result = 5 + "hello";  // Compile Error: type mismatch
    cout << "Type safety enforced at compile time" << endl;

    // PART 5: Variable Scope
    cout << "\n--- Variable Scope Demo ---" << endl;
    scopeDemo();
    cout << "Outside function - globalVar: " << globalVar << endl;
    // cout << localVar;  // Compile Error: not in scope

    // PART 6: Strict Typing Example
    cout << "\n--- No Implicit Type Coercion ---" << endl;
    string str = "5";
    int intNum = 3;
    // auto result = str + intNum;  // Compile Error
    cout << "Must explicitly convert: " << str + to_string(intNum) << endl;
    cout << "Or: " << stoi(str) + intNum << endl;

    cout << "\n"
         << string(60, '=') << endl;

    return 0;
}