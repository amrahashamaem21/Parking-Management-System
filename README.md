# Parking-Management-System
This project is a console-based Parking Management System built using C++. It simulates a real-world parking structure consisting of multiple blocks, rows, and slots. Each block manages its own parking data, and the system allows efficient vehicle parking, removal, searching, and smart allocation.
The main focus of this project is to demonstrate strong use of Object-Oriented Programming concepts along with dynamic memory management.

Features
Create parking blocks manually or load from file
Add rows and slots dynamically
Park and remove vehicles
Display full parking structure
Resize parking slots in a row
Search for a vehicle
Empty a row or entire block
Transfer vehicles between blocks
Merge vehicles from one block into another
Smart allocation based on distance
Load coordinates for blocks
Object Oriented Programming Concepts Used
1. Encapsulation

All data members such as slots, rows, and coordinates are kept private inside the class.
They are accessed and modified only through public member functions.

Example
The slot structure and row information cannot be directly accessed from main.

2. Constructors and Destructor
Default constructor initializes empty parking block
Parameterized constructor initializes block with given rows
Copy constructor performs deep copy
Move constructor transfers ownership of memory
Destructor frees all dynamically allocated memory

This ensures proper memory handling and avoids memory leaks.

3. Copy and Move Semantics
Copy assignment operator creates a deep copy of another object
Move assignment operator transfers resources without copying

This improves efficiency and avoids unnecessary memory usage.

4. Dynamic Memory Management
2D dynamic array of strings is used for slots
Arrays are resized using functions like add_rows and resize_slot
Memory is properly deleted before reallocation
5. Abstraction

Complex operations are hidden behind simple function calls.

Example

park_car() handles validation and parking logic
smart_allocate() automatically finds the best slot
6. Modularity

Each task is handled by a separate function.

Examples

add_slots() for slot creation
search_vehicle() for searching
transfer_vehicles() for copying data between blocks

This makes the code easy to manage and extend.

7. Use of Classes and Objects
Each parking block is represented as an object
Multiple blocks are stored as an array of objects
Each object manages its own data independently
File Handling

The program supports file input for:

Loading parking structure
Loading block coordinates

This allows reuse of saved configurations.

Smart Allocation Logic

The system calculates distance between desired block and available slots using coordinates.
The nearest available slot is selected automatically.

How to Run
Compile the program using a C++ compiler
Run the executable
Use the menu to perform operations
Initialize system before performing any action
Notes
Indexing in code starts from 0 but user input starts from 1
Memory is carefully managed using constructors and destructor
Invalid inputs are handled with basic validation
