# Python: Calculate the sum of an array
# This file contains INTENTIONAL ERRORS for analysis

# VERSION 1: Original errors from assignment
def calculate_sum(arr):
    total = o  # ERROR 1: letter 'o' instead of 0
    for num in arr:
        total += num
    return total

numbers = [1, 2, 3, 4, 5]
result = calculate_sum(numbers)
print("Sum in Python:", result)


# VERSION 2: Additional error - Missing colon
"""
def calculate_sum_v2(arr)  # ERROR 2: Missing colon
    total = 0
    for num in arr:
        total += num
    return total
"""


# VERSION 3: Additional error - Bad indentation
"""
def calculate_sum_v3(arr):
total = 0  # ERROR 3: No indentation
    for num in arr:
        total += num
    return total
"""


# VERSION 4: Additional error - Invalid variable name
"""
def calculate_sum_v4(arr):
    2total = 0  # ERROR 4: Variable name starts with number
    for num in arr:
        total += num
    return total
"""


# CORRECTED VERSION (uncomment to test)
"""
def calculate_sum_correct(arr):
    total = 0  # Fixed: Changed 'o' to 0
    for num in arr:
        total += num
    return total

numbers = [1, 2, 3, 4, 5]
result = calculate_sum_correct(numbers)
print("Sum in Python:", result)
"""