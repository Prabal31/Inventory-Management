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



// Function prototypes
void insert(void);
void search(void);
void update(void);
void print(void);
void clear_input(void);
void get_string_input(const char *prompt, char *str, int length);
int get_int_input(const char *prompt);
int is_valid_integer(const char *str);
int is_valid_name(const char *str);
struct part *find_part(int number);


// Inventory list starts empty
struct part *inventory = NULL;

// Main function
int main(void) {
    char code;

    // Display a welcome message and menu options
    printf("*****************************************\n");
    printf("* Welcome to the Inventory Management System *\n");
    printf("*****************************************\n");

    // Continuously prompt user for operations until they choose to quit
    while (1) {
        printf("\n");
        printf("Menu Options:\n");
        printf("  i - Insert a new part\n");
        printf("  s - Search for a part\n");
        printf("  u - Update a part's quantity\n");
        printf("  p - Print all parts\n");
        printf("  q - Quit the program\n");
        printf("Enter your choice: ");

        scanf(" %c", &code); // Read user input for the operation code
        clear_input(); // Clear any leftover input in the buffer
        code = tolower(code); // Convert the input to lowercase for consistency

        // Perform the action based on the user input
        switch (code) {
        case 'i':
            insert();
            break;
        case 's':
            search();
            break;
        case 'u':
            update();
            break;
        case 'p':
            print();
            break;
        case 'q':
            printf("Exiting program. Goodbye!\n");
            return 0; // Exit the program
        default:
            printf("Error: Invalid operation code. Please try again.\n");
        }
    }
}

// Function to get a valid integer input from the user
int get_int_input(const char *prompt) {
    char buffer[100]; // Buffer to hold user input
    int value;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline character
            if (is_valid_integer(buffer)) {
                value = atoi(buffer); // Convert the string to an integer
                return value;
            } else {
                printf("Invalid input. Please enter a valid integer.\n");
            }
        } else {
            clear_input();
            printf("Error reading input. Please try again.\n");
        }
    }
}
// Function to get a valid string input from the user
void get_string_input(const char *prompt, char *str, int length) {
    while (1) {
        printf("%s", prompt);
        if (fgets(str, length, stdin) != NULL) {
            str[strcspn(str, "\n")] = '\0'; // Remove trailing newline character

            // Validate that the string does not contain numbers
            if (is_valid_name(str)) {
                return;
            } else {
                printf("Invalid input. Part name should not contain numbers.\n");
            }
        } else {
            clear_input();
            printf("Error reading input. Please try again.\n");
        }
    }
}

// Function to clear the input buffer
void clear_input(void) {
    while (getchar() != '\n')
        ; // Discard remaining characters in the input buffer
}

// Function to check if a string is a valid integer
int is_valid_integer(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return 0; // Invalid integer
        }
        str++;
    }
    return 1; // Valid integer
}

// Function to check if a string is a valid part name
int is_valid_name(const char *str) {
    while (*str) {
        if (isdigit(*str)) {
            return 0; // Invalid name (contains numbers)
        }
        str++;
    }
    return 1; // Valid name (no numbers)
}


// Function to insert a new part into the inventory
void insert(void) {
    struct part *new_part, *prev, *cur;
    int number;

    // Allocate memory for the new part
    new_part = (struct part *)malloc(sizeof(struct part));
    if (new_part == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    // Get a valid part number from the user
    number = get_int_input("Enter part number: ");

    // Find the correct position to insert the new part in the list
    for (cur = inventory, prev = NULL;
         cur != NULL && number > cur->number;
         prev = cur, cur = cur->next)
        ;

    // Check if the part already exists
    if (cur != NULL && number == cur->number) {
        printf("Error: Part with this number already exists.\n");
        free(new_part);
        return;
    }

    new_part->number = number;

    // Get the name of the new part from the user
    get_string_input("Enter part name: ", new_part->name, NAME_LEN + 1);

    // Get the initial quantity on hand from the user
    new_part->on_hand = get_int_input("Enter quantity on hand: ");

    // Insert the new part in the correct position in the list
    new_part->next = cur;
    if (prev == NULL)
        inventory = new_part;
    else
        prev->next = new_part;
}

// Function to search for a part by its number
void search(void) {
    int number;
    struct part *p;

    number = get_int_input("Enter part number to search: ");

    p = find_part(number);
    if (p != NULL) {
        // Display the details of the found part
        printf("\nPart found:\n");
        printf("  Part Number: %d\n", p->number);
        printf("  Part Name: %s\n", p->name);
        printf("  Quantity on Hand: %d\n", p->on_hand);
    } else {
        printf("Error: Part not found.\n");
    }
}


// Function to update the quantity of a part
void update(void) {
    int number, change;
    struct part *p;

    number = get_int_input("Enter part number to update: ");

    p = find_part(number);
    if (p != NULL) {
        // Get the change in quantity and update the part's quantity
        change = get_int_input("Enter change in quantity:");
        p->on_hand = change;
        printf("Part quantity updated successfully.\n");
    } else {
        printf("Error: Part not found.\n");
    }
}

// Function to print all parts in the inventory
void print(void) {
    struct part *p;

    // Print a table header
    printf("\nPart Inventory:\n");
    printf("-------------------------------------------------------------\n");
    printf("| %-10s | %-20s | %-15s |\n", "Part Number", "Part Name", "Quantity on Hand");
    printf("-------------------------------------------------------------\n");

    // Print each part's details
    for (p = inventory; p != NULL; p = p->next)
        printf("| %-10d | %-20s | %-15d |\n", p->number, p->name, p->on_hand);

    printf("-------------------------------------------------------------\n");
}


// Function to find a part by its number
struct part *find_part(int number) {
    struct part *p;

    // Traverse the list to find the part with the specified number
    for (p = inventory; p != NULL && p->number != number; p = p->next)
        ;
    return p; // Return the found part or NULL if not found
}