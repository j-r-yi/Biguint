# Biguint Calculator Project

## Overview

The Biguint Calculator Project implements a high-precision arithmetic system using dynamically allocated memory to handle arbitrarily large unsigned and signed integers. The project consists of two main classes, `Biguint` and `Bigint`, which support a wide range of arithmetic and comparison operations. This project is ideal for applications that require precise calculations with large numbers, such as cryptography, scientific computations, and factorial or power operations.

## Features

### Biguint Class (`Biguint.h`)
The `Biguint` class handles operations on large non-negative integers. Key features include:

#### Constructors and Destructor
- Create a `Biguint` with:
  - A default value.
  - A string representation of digits.
  - A copy of another `Biguint`.
- Properly manage dynamically allocated memory with a destructor.

#### Arithmetic Operations
- Addition (`+=`), subtraction (`-=`), multiplication (`*=`), division (`/=`), and modulus (`%=`) with another `Biguint` or a single digit.
- Increment (`++`) and decrement (`--`) operators.
- Power operations for raising a `Biguint` to an integer power.

#### Logical and Comparison Operations
- Compare two `Biguint` objects with:
  - `<`, `<=`, `==`, `!=`, `>=`, and `>` operators.
  - A `compare` method to return the relationship as an integer.
- Shift operations (`<<` and `>>`) for left and right bitwise shifts.

#### Other Utilities
- Dynamically adjust memory with the `reserve` method.
- Access individual digits with the subscript operator (`[]`).
- Support for I/O via `<<` and `>>` operators for convenient interaction.

---

### Bigint Class (`Bigint.h`)
The `Bigint` class extends `Biguint` to include support for signed integers. Key features include:

#### Constructors
- Initialize a `Bigint` from:
  - An integer.
  - A string with optional leading `-`.

#### Arithmetic and Comparison
- Perform addition (`+=`) and comparisons for signed integers.
- Handle signed numbers seamlessly, using the `_is_neg` field to track negativity.

#### Logical Utilities
- Use `compare` to evaluate relationships between two `Bigint` objects.

#### Input and Output
- Stream operators (`<<`, `>>`) for signed integers.

---

### Non-Member Operators
Both `Biguint` and `Bigint` support intuitive arithmetic and comparison via overloaded operators:
- **Arithmetic**: `+`, `-`, `*`, `/`, `%`
- **Comparison**: `<`, `<=`, `==`, `!=`, `>=`, `>`
- **Shift**: `<<`, `>>`

---

## How to Use

1. **Biguint Usage**:
   - Create a `Biguint` with a default value, a string of digits, or another `Biguint`.
   - Perform arithmetic operations, including addition, subtraction, multiplication, and division.
   - Use logical operators to compare `Biguint` objects.

2. **Bigint Usage**:
   - Initialize a `Bigint` with a signed integer or string.
   - Perform signed arithmetic and comparisons.
   - Stream values using `<<` and `>>`.

3. **Dynamic Memory Management**:
   - Use `reserve` to allocate memory for large numbers.
   - Memory is managed automatically, ensuring efficiency.

4. **I/O**:
   - Easily input and output numbers using the overloaded stream operators.

---

## Project Structure

- **Header Files**
  - `Biguint.h`: Core class for large unsigned integer calculations.
  - `Bigint.h`: Derived class for signed integer support.
- **Non-Member Functions**
  - Arithmetic, comparison, and shift operators for seamless operations.

---

## Dependencies

- Standard libraries:
  - `<cstdlib>`: Memory management.
  - `<string>`: String handling.
  - `<iostream>`: Input and output.

---

## Future Enhancements

- Implement additional mathematical operations such as factorials and GCD.
- Extend functionality for floating-point numbers.
- Add a command-line interface or GUI for user interaction.


