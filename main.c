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