#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_PHONE_LENGTH 15

// Structure to represent a room
typedef struct Room {
    int room_number;
    int is_available;  // 1 for available, 0 for booked
    int price;  // price per night
    struct Room* next;
} Room;

// Structure to represent a customer
typedef struct Customer {
    int customer_id;
    char name[MAX_NAME_LENGTH];
    int age;
    int room_number;
    int total_amount;
    int days_of_stay;
    int num_guests;
    int num_children;
    int check_in_date;
    int check_out_date;
    char phone_number[MAX_PHONE_LENGTH];
    struct Customer* next;
} Customer;

// Function to calculate the duration of stay (assuming simple logic for now)
int calculateStayDuration(int check_in_date, int check_out_date) {
    return (check_out_date - check_in_date) / 100; // Simplified example, assuming dates are in YYYYMMDD format
}

// Add a customer to the list
void addCustomer(Customer** customerList, int id, char* name, int age, int room_number, int total_amount, int days_of_stay, int num_guests, int num_children, int check_in_date, int check_out_date, char* phone_number) {
    // Check if the customer ID already exists
    Customer* current = *customerList;
    while (current != NULL) {
        if (current->customer_id == id) {
            printf("Error: Customer ID %d already exists.\n", id);
            return;  // Stop and return if ID already exists
        }
        current = current->next;
    }

    // If ID is unique, proceed to add customer
    Customer* newCustomer = (Customer*)malloc(sizeof(Customer));
    newCustomer->customer_id = id;
    strcpy(newCustomer->name, name);
    newCustomer->age = age;
    newCustomer->room_number = room_number;
    newCustomer->total_amount = total_amount;
    newCustomer->days_of_stay = days_of_stay;
    newCustomer->num_guests = num_guests;
    newCustomer->num_children = num_children;
    newCustomer->check_in_date = check_in_date;
    newCustomer->check_out_date = check_out_date;
    strcpy(newCustomer->phone_number, phone_number);
    newCustomer->next = *customerList;
    *customerList = newCustomer;
    printf("Customer added successfully!\n");
}

// Check if the room is available
int checkRoomAvailability(Room* rooms[], int room_number) {
    for (int i = 0; i < 5; i++) {
        Room* current = rooms[i];
        while (current != NULL) {
            if (current->room_number == room_number) {
                return current->is_available;  // 1 for available, 0 for booked
            }
            current = current->next;
        }
    }
    return 0; // Room does not exist
}

// Find a customer by ID
Customer* findCustomerById(Customer* customerList, int customer_id) {
    Customer* current = customerList;
    while (current != NULL) {
        if (current->customer_id == customer_id) {
            return current; // Customer found
        }
        current = current->next;
    }
    return NULL; // Customer not found
}

// Book a room (with customer ID verification)
Room* bookRoom(Room* rooms[], int room_number, int customer_id, Customer* customerList) {
    // Check if customer ID is valid
    Customer* customer = findCustomerById(customerList, customer_id);
    if (customer == NULL) {
        printf("Invalid customer ID: %d. Please enter a valid ID.\n", customer_id);
        return NULL; // If ID is invalid, return NULL
    }

    // Check room availability
    for (int i = 0; i < 5; i++) {
        Room* current = rooms[i];
        while (current != NULL) {
            if (current->room_number == room_number && current->is_available) {
                current->is_available = 0;  // Mark room as booked
                printf("Room %d booked successfully for Customer ID %d.\n", room_number, customer_id);
                return current;
            }
            current = current->next;
        }
    }
    printf("Room %d is not available.\n", room_number);
    return NULL; // Room not available
}

// Main function
int main() {
    // Initialize rooms and customers
    Room* rooms[5];
    for (int i = 0; i < 5; i++) {
        rooms[i] = NULL;  // No rooms initially
    }

    // Sample rooms
    Room* room1 = (Room*)malloc(sizeof(Room));
    room1->room_number = 101;
    room1->is_available = 1;  // Room 101 is available
    room1->price = 100;
    room1->next = NULL;
    rooms[0] = room1;

    Room* room2 = (Room*)malloc(sizeof(Room));
    room2->room_number = 102;
    room2->is_available = 1;  // Room 102 is available
    room2->price = 120;
    room2->next = NULL;
    rooms[1] = room2;

    Customer* customerList = NULL;  // No customers initially

    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Customer\n");
        printf("2. Book Room\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int id, age, room_number, days_of_stay, num_guests, num_children, check_in_date, check_out_date;
                char name[MAX_NAME_LENGTH], phone_number[MAX_PHONE_LENGTH];

                printf("Enter Customer ID: ");
                scanf("%d", &id);
                printf("Enter Full Name: ");
                scanf(" %[^\n]", name);
                printf("Enter Age: ");
                scanf("%d", &age);
                printf("Enter Room Number: ");
                scanf("%d", &room_number);
                printf("Enter Number of Guests: ");
                scanf("%d", &num_guests);
                printf("Enter Number of Children: ");
                scanf("%d", &num_children);
                printf("Enter Phone Number: ");
                scanf("%s", phone_number);
                printf("Enter Check-In Date (YYYYMMDD): ");
                scanf("%d", &check_in_date);
                printf("Enter Check-Out Date (YYYYMMDD): ");
                scanf("%d", &check_out_date);

                // Calculate the days of stay
                days_of_stay = calculateStayDuration(check_in_date, check_out_date);

                // Assuming a fixed price per night for simplicity
                int total_amount = 100 * days_of_stay;

                addCustomer(&customerList, id, name, age, room_number, total_amount, days_of_stay, num_guests, num_children, check_in_date, check_out_date, phone_number);
                break;
            }

            case 2: {
                int room_number, customer_id;

                printf("Enter Room Number to Book: ");
                scanf("%d", &room_number);

                // Check room availability before asking for details
                if (checkRoomAvailability(rooms, room_number) == 0) {
                    printf("Invalid request: Room is not available or does not exist.\n");
                } else {
                    // Ask for customer ID and check if it exists
                    printf("Enter Customer ID: ");
                    scanf("%d", &customer_id);

                    // Book the room only if the customer ID is valid
                    Room* bookedRoom = bookRoom(rooms, room_number, customer_id, customerList);
                    if (bookedRoom != NULL) {
                        printf("Room booked successfully!\n");
                    }
                }
                break;
            }

            case 3: {
                printf("Exiting the program.\n");
                exit(0);
            }

            default: {
                printf("Invalid choice. Please try again.\n");
                break;
            }
        }
    }

    return 0;
}
