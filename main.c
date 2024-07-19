//
// Created by Prabh Manchanda on 2024-07-19.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define the maximum length for part names
#define NAME_LEN 25

// Structure to represent each part in the inventory
struct part {
    int number;        // Unique identifier for the part
    char name[NAME_LEN + 1];  // Name of the part (up to NAME_LEN characters)
    int on_hand;       // Quantity of the part currently in stock
    struct part *next; // Pointer to the next part in the linked list
};