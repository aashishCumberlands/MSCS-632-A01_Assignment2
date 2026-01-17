"""
Python: Type Systems and Closures Demonstration
Demonstrates: Dynamic typing, closures, variable scope
"""

print("=" * 60)
print("PYTHON: Type Systems and Closures Demo")
print("=" * 60)

# ============================================================
# PART 1: CLOSURES AND SCOPE
# ============================================================

def create_multiplier(factor):
    """
    Outer function that returns a closure.
    The inner function 'captures' the factor variable.
    """
    count = 0  # Variable in enclosing scope
    
    def multiply(x):
        """Inner function (closure) that captures 'factor' and 'count'"""
        nonlocal count  # Allows modification of enclosing scope variable
        count += 1
        print(f"  Multiply called {count} times")
        return x * factor
    
    return multiply

print("\n--- Closures Demo ---")
times_three = create_multiplier(3)
times_five = create_multiplier(5)

print("Using times_three closure:")
print(f"  Result: {times_three(10)}")  # 30
print(f"  Result: {times_three(20)}")  # 60

print("\nUsing times_five closure:")
print(f"  Result: {times_five(10)}")   # 50
print(f"  Result: {times_five(7)}")    # 35

# ============================================================
# PART 2: DYNAMIC TYPING
# ============================================================

def flexible_calculator(a, b, operation):
    """Function that works with different types dynamically"""
    if operation == "add":
        return a + b
    elif operation == "multiply":
        return a * b
    elif operation == "concat":
        return str(a) + str(b)

print("\n--- Dynamic Typing Demo ---")
print(f"Int addition: {flexible_calculator(5, 3, 'add')}")  # 8
print(f"Float addition: {flexible_calculator(5.5, 2.5, 'add')}")  # 8.0
print(f"String concat: {flexible_calculator('Hello', 'World', 'concat')}")  # HelloWorld
print(f"List addition: {flexible_calculator([1, 2], [3, 4], 'add')}")  # [1,2,3,4]

# ============================================================
# PART 3: TYPE CHECKING AND DYNAMIC TYPES
# ============================================================

print("\n--- Runtime Type Checking ---")
value = 42
print(f"value = {value}, type = {type(value).__name__}")

value = "Now I'm a string"
print(f"value = {value}, type = {type(value).__name__}")

value = [1, 2, 3]
print(f"value = {value}, type = {type(value).__name__}")

value = {"key": "dict"}
print(f"value = {value}, type = {type(value).__name__}")

# ============================================================
# PART 4: VARIABLE SCOPE
# ============================================================

print("\n--- Variable Scope Demo ---")

global_var = "I'm global"

def scope_demo():
    local_var = "I'm local"
    print(f"  Inside function - local_var: {local_var}")
    print(f"  Inside function - global_var: {global_var}")
    
    # Demonstrating scope in if statement
    if True:
        if_var = "I'm in if block"
    
    # In Python, if_var is accessible outside the if block (function scope)
    print(f"  After if block - if_var: {if_var}")

scope_demo()
print(f"Outside function - global_var: {global_var}")
# print(local_var)  # This would cause NameError

# ============================================================
# PART 5: TYPE STRENGTH (Strong Typing)
# ============================================================

print("\n--- Type Strength Demo ---")
try:
    result = "5" + 3  # This will raise TypeError
except TypeError as e:
    print(f"  Error: {e}")
    print("  Python doesn't allow implicit type coercion")
    print(f"  Correct way: {'5' + str(3)} or {int('5') + 3}")

print("\n" + "=" * 60)