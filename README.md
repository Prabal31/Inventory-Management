# Warehouse Inventory Management System

This project demonstrates the use of linked lists and structures in C to manage a database of parts stored in a warehouse. Each part is represented by a structure containing its part number, name, and quantity.

## Features

The program supports the following operations:
1. **Add a new part**: Insert a new part into the database with its part number, name, and initial quantity.
2. **Search for a part**: Given a part number, print the name of the part and the current quantity on hand.
3. **Update part quantity**: Given a part number, change the quantity on hand.
4. **Display all parts**: Print all information in the database.
5. **Quit the program**: Terminate program execution.

## Code Representation

The following codes represent each operation:
- `i`: Insert a new part
- `s`: Search for a part
- `u`: Update part quantity
- `p`: Print all parts
- `q`: Quit the program

## Data Structure

The parts are stored in a linked list, where each node contains the following structure:

```c
struct part {
    int number;                 // Part number
    char name[NAME_LEN+1];      // Part name
    int on_hand;                // Quantity on hand
    struct part *next;          // Pointer to the next node
};

struct part *inventory = NULL;  // Pointer to the first node in the list
