# List342 C++ Linked List Implementation

This C++ project implements a versatile linked list class called `List342`. The linked list is templated, allowing it to store elements of any data type. The class provides essential functionalities such as insertion, removal, merging, and comparison. The project also includes operator overloads for enhanced usability.

## Key Components

### 1. List342 Class
- **Constructors:**
  - Default Constructor: Initializes an empty list.
  - Copy Constructor: Creates a copy of the provided list.

- **Member Functions:**
  - `BuildList`: Reads elements from a file, avoiding duplicates.
  - `Insert`: Inserts elements in sorted order.
  - `Remove`: Removes a specified element.
  - `Peek`: Retrieves data without removing an element.
  - `Size`: Returns the number of elements.
  - `DeleteList`: Clears the list.
  - `Merge`: Merges the list with another.
  - `operator+`: Merges two lists using the addition operator.
  - `operator+=`: Merges two lists in place using the addition assignment operator.
  - `operator==`: Compares two lists for equality.
  - `operator!=`: Compares two lists for inequality.
  - `operator=`: Assigns one list to another.

- **Helper Functions:**
  - `recursiveMerge`: Recursively merges two sorted lists.

### 2. Node Struct
- Template structure representing a node in the linked list.
- Contains a pointer to data of type `T` and a pointer to the next node.

### 3. Operator Overloads
- Overloaded the stream insertion operator (`<<`) for easy printing of the list.

### 4. Template Functions
- Template functions for friend functions and member functions ensure flexibility.

## Lessons Learned

### 1. Templating
Learning to implement a templated linked list provides a deep understanding of how to create flexible data structures that can handle various data types.

### 2. Memory Management
Dealing with dynamic memory allocation and deallocation through node creation and deletion contributes to improved memory management skills.

### 3. File Handling
Implementing file input for building the list enhances skills in reading and processing external data.

### 4. Operator Overloading
Understanding and implementing operator overloads (e.g., `+`, `+=`, `==`, `!=`, `=`) improves the ability to create expressive and intuitive interfaces for user-defined types.

### 5. Algorithmic Thinking
Implementing sorting and merging algorithms (e.g., `recursiveMerge`) enhances algorithmic thinking and problem-solving skills.

### 6. Copy Constructors and Assignment Operators
Implementing copy constructors and assignment operators deepens understanding of object-oriented programming concepts and ensures proper handling of object copies.

### 7. Testing and Debugging
Thorough testing of various functionalities and handling potential edge cases improves debugging and testing skills.

### 8. Documentation
Creating a README to explain the project structure and functionality enhances documentation skills, aiding future maintainability and collaboration.

This project not only provides a practical implementation of a linked list but also reinforces fundamental C++ concepts and best practices, making it a valuable learning experience.
