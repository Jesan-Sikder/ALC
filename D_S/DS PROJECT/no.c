#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NON_AC 0
#define AC 1
#define VIP 2

typedef struct Room {
    int room_number;
    int floor;
    int type;
    int price;
    int is_available;
    struct Room* next;
} Room;

typedef struct Customer {
    int customer_id;
    char name[100];
    int age;
    int room_number;
    int total_amount;
    int days_of_stay;
    int num_guests;
    int num_children;
    int check_in_date;
    int check_out_date;
    char phone_number[15];
    struct Customer* next;
} Customer;

typedef struct User {
    int user_id;
    char username[50];
    char password[50];
    char email[100];
    struct User* next;
} User;

typedef struct Wishlist {
    int room_number;
    struct Wishlist* next;
} Wishlist;

// Function prototypes
void initializeRooms(Room* rooms[]);
void displayRooms(Room* rooms[], int type);
int getPrice(int type);
Room* bookRoom(Room* rooms[], int room_number);
void addCustomer(Customer** customerList, int id, char* name, int age, int room_number, int total_amount, int days_of_stay, int num_guests, int num_children, int check_in_date, int check_out_date, char* phone_number);
void viewBookingDetails(Customer* customerList);
void displayVIPFacilities();
void signUp(User** userList);
User* signIn(User* userList);
void addToWishlist(Wishlist** wishlist, int room_number);
void viewWishlist(Wishlist* wishlist);
int checkRoomAvailability(Room* rooms[], int room_number);
void cancelBooking(Customer** customerList, int customer_id);
void extendStay(Customer* customerList, int customer_id);
int calculateStayDuration(int check_in_date, int check_out_date);
int isValidDate(int date);

void initializeRooms(Room* rooms[])  {
    for (int i = 0; i < 2; i++) {  // Floors 1 and 2: Non-AC rooms
        for (int j = 0; j < 10; j++) {
            Room* newRoom = (Room*)malloc(sizeof(Room));
            newRoom->room_number = (i + 1) * 100 + j + 1;
            newRoom->floor = i + 1;
            newRoom->type = NON_AC;
            newRoom->price = 1000;
            newRoom->is_available = 1;
            newRoom->next = NULL;

            if (rooms[i] == NULL || rooms[i]->room_number > newRoom->room_number) {
                newRoom->next = rooms[i];
                rooms[i] = newRoom;
            } else {
                Room* current = rooms[i];
                while (current->next != NULL && current->next->room_number < newRoom->room_number) {
                    current = current->next;
                }
                newRoom->next = current->next;
                current->next = newRoom;
            }
        }
    }

    for (int i = 0; i < 10; i++) {  // Floor 3: AC rooms
        Room* newRoom = (Room*)malloc(sizeof(Room));
        newRoom->room_number = 300 + i + 1;
        newRoom->floor = 3;
        newRoom->type = AC;
        newRoom->price = 2000;
        newRoom->is_available = 1;
        newRoom->next = NULL;

        Room* current = rooms[2];
        if (current == NULL || current->room_number > newRoom->room_number) {
            newRoom->next = current;
            rooms[2] = newRoom;
        } else {
            while (current->next != NULL && current->next->room_number < newRoom->room_number) {
                current = current->next;
            }
            newRoom->next = current->next;
            current->next = newRoom;
        }
    }

    for (int i = 0; i < 2; i++) {  // Floors 4 and 5: VIP rooms
        for (int j = 0; j < 10; j++) {
            Room* newRoom = (Room*)malloc(sizeof(Room));
            newRoom->room_number = (i + 4) * 100 + j + 1;
            newRoom->floor = i + 4;
            newRoom->type = VIP;
            newRoom->price = 5000;
            newRoom->is_available = 1;
            newRoom->next = NULL;

            Room* current = rooms[i + 3];
            if (current == NULL || current->room_number > newRoom->room_number) {
                newRoom->next = current;
                rooms[i + 3] = newRoom;
            } else {
                while (current->next != NULL && current->next->room_number < newRoom->room_number) {
                    current = current->next;
                }
                newRoom->next = current->next;
                current->next = newRoom;
            }
        }
    }
}
// Display rooms by type (Non-AC, AC, VIP)

void displayRooms(Room* rooms[], int type) {
    for (int i = 0; i < 5; i++) {
        Room* current = rooms[i];
        while (current != NULL) {
            if (current->type == type && current->is_available) {
                printf("Room %d (Floor %d): Price: %d\n", current->room_number, current->floor, current->price);
            }
            current = current->next;
        }
    }
}

// Get the price of the room based on its type
int getPrice(int type) {
    switch (type) {
        case NON_AC: return 1000;
        case AC: return 2000;
        case VIP: return 5000;
        default: return 0;
    }
}

// Calculate the number of days between check-in and check-out
int calculateStayDuration(int check_in_date, int check_out_date) {
    int check_in_day = check_in_date % 100;
    int check_in_month = (check_in_date / 100) % 100;
    int check_in_year = check_in_date / 10000;

    int check_out_day = check_out_date % 100;
    int check_out_month = (check_out_date / 100) % 100;
    int check_out_year = check_out_date / 10000;

    int days_in_check_in = check_in_year * 365 + check_in_month * 30 + check_in_day;
    int days_in_check_out = check_out_year * 365 + check_out_month * 30 + check_out_day;

    return days_in_check_out - days_in_check_in;
}

// Check if the room is available
int checkRoomAvailability(Room* rooms[], int room_number) {
    for (int i = 0; i < 5; i++) {
        Room* current = rooms[i];
        while (current != NULL) {
            if (current->room_number == room_number && current->is_available) {
                return 1; // Room is available
            }
            current = current->next;
        }
    }
    return 0; // Room not available
}

// Book a room
Room* bookRoom(Room* rooms[], int room_number) {
    for (int i = 0; i < 5; i++) {
        Room* current = rooms[i];
        while (current != NULL) {
            if (current->room_number == room_number && current->is_available) {
                current->is_available = 0;  // Mark room as booked
                return current;
            }
            current = current->next;
        }
    }
    return NULL;
}

void addCustomer(Customer** customerList, int id, char* name, int age, int room_number, int total_amount, int days_of_stay, int num_guests, int num_children, int check_in_date, int check_out_date, char* phone_number) {
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
}

// View booking details
void viewBookingDetails(Customer* customerList) {
    printf("\nBooking Details:\n");
    Customer* current = customerList;
    while (current != NULL) {
        printf("Customer ID: %d\n", current->customer_id);
        printf("Name: %s\n", current->name);
        printf("Room Number: %d\n", current->room_number);
        printf("Total Amount: %d\n", current->total_amount);
        printf("Stay Duration: %d days\n", current->days_of_stay);
        printf("Check-In Date: %d\n", current->check_in_date);
        printf("Check-Out Date: %d\n", current->check_out_date);
        printf("Phone Number: %s\n", current->phone_number);
        current = current->next;
    }
}
void displayVIPFacilities() {
    printf("VIP rooms include extra amenities such as:\n");
    printf("- 24/7 Room Service\n");
    printf("- Complimentary Snacks\n");
    printf("- Personalized Concierge\n");
}
// Sign-up for the user system
void signUp(User** userList) {
    User* newUser = (User*)malloc(sizeof(User));
    printf("Enter Username: ");
    scanf("%s", newUser->username);
    printf("Enter Password: ");
    scanf("%s", newUser->password);
    printf("Enter Email: ");
    scanf("%s", newUser->email);

    srand(time(NULL));
    newUser->user_id = rand() % 1000;
    newUser->next = *userList;
    *userList = newUser;
    printf("User signed up successfully. Your User ID is %d\n", newUser->user_id);
}

// Sign-in to the system
User* signIn(User* userList) {
    char username[50], password[50];
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    User* current = userList;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0) {
            printf("Welcome %s!\n", current->username);
            return current;
        }
        current = current->next;
    }
    printf("Invalid credentials. Please try again.\n");
    return NULL;
}



void addToWishlist(Wishlist** wishlist, int room_number) {
    Wishlist* newRoom = (Wishlist*)malloc(sizeof(Wishlist));
    newRoom->room_number = room_number;
    newRoom->next = *wishlist;
    *wishlist = newRoom;
}


// View wishlist
void viewWishlist(Wishlist* wishlist) {
    printf("\nWishlist:\n");
    Wishlist* current = wishlist;
    while (current != NULL) {
        printf("Room Number: %d\n", current->room_number);
        current = current->next;
    }
}

// Date validation function
int isValidDate(int date) {
    int day = date % 100;
    int month = (date / 100) % 100;
    int year = date / 10000;

    if (month < 1 || month > 12 || day < 1 || day > 31) {
        return 0; // Invalid date
    }

    // Handle days per month
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) return 0;
    } else if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            if (day > 29) return 0; // Leap year
        } else {
            if (day > 28) return 0;
        }
    }

    return 1; // Valid date
}
// Cancel Booking
void cancelBooking(Customer** customerList, int customer_id) {
    Customer* current = *customerList;
    Customer* previous = NULL;

    while (current != NULL) {
        if (current->customer_id == customer_id) {
            if (previous == NULL) {
                *customerList = current->next;
            } else {
                previous->next = current->next;
            }
            printf("Booking with Customer ID %d has been cancelled.\n", customer_id);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Booking not found for Customer ID %d.\n", customer_id);
}

// Extend Stay
void extendStay(Customer* customerList, int customer_id) {
    Customer* current = customerList;
    while (current != NULL) {
        if (current->customer_id == customer_id) {
            int additional_days;
            printf("Enter additional days to extend the stay: ");
            scanf("%d", &additional_days);

            current->days_of_stay += additional_days;
            current->total_amount += current->days_of_stay * getPrice(AC); // Assuming the room is AC
            printf("Stay extended by %d days. New total amount: %d\n", additional_days, current->total_amount);
            return;
        }
        current = current->next;
    }
    printf("Booking not found for Customer ID %d.\n", customer_id);
}

int main() {
    Room* rooms[5] = {NULL};
    Customer* customerList = NULL;
    User* userList = NULL;
    Wishlist* wishlist = NULL;

    initializeRooms(rooms);

    int option;
    User* currentUser = NULL;

    while (1) {
        printf("\n==================== Hotel Management System ====================\n");
        printf("1. Sign Up\n");
        printf("2. Sign In\n");
        printf("3. View Rooms (Non-AC, AC, VIP)\n");
        printf("4. Book a Room\n");
        printf("5. View Booking Details\n");
        printf("6. View VIP Facilities\n");
        printf("7. Add to Wishlist\n");
        printf("8. View Wishlist\n");
        printf("9. Cancel Booking\n");
        printf("10. Extend Stay\n");
        printf("11. Exit\n");
        printf("==================================================================\n");
        printf("Select an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                signUp(&userList);
                break;

            case 2:
                currentUser = signIn(userList);
                if (currentUser == NULL) {
                    printf("Sign-in failed. Please check your credentials.\n");
                }
                break;

            case 3:
                if (currentUser != NULL) {
                    int roomType;
                    printf("\nSelect room type to view:\n");
                    printf("1. Non-AC\n2. AC\n3. VIP\n");
                    printf("Enter choice: ");
                    scanf("%d", &roomType);
                    if (roomType == 1) {
                        displayRooms(rooms, NON_AC);
                    } else if (roomType == 2) {
                        displayRooms(rooms, AC);
                    } else if (roomType == 3) {
                        displayRooms(rooms, VIP);
                    } else {
                        printf("Invalid room type!\n");
                    }
                } else {
                    printf("Please sign in to view rooms.\n");
                }
                break;

            case 4:
                if (currentUser != NULL) {
                    int room_number;
                    printf("Enter the room number to book: ");
                    scanf("%d", &room_number);
                    if (checkRoomAvailability(rooms, room_number)) {
                        Room* bookedRoom = bookRoom(rooms, room_number);
                        if (bookedRoom != NULL) {
                            printf("Room %d booked successfully!\n", room_number);
                            int check_in_date, check_out_date;
                            printf("Enter check-in date (YYYYMMDD): ");
                            scanf("%d", &check_in_date);
                            printf("Enter check-out date (YYYYMMDD): ");
                            scanf("%d", &check_out_date);
                            if (!isValidDate(check_in_date) || !isValidDate(check_out_date)) {
                                printf("Invalid date entered!\n");
                            } else {
                                addCustomer(&customerList, rand() % 1000, "John Doe", 30, room_number, 0, 3, 2, 1, check_in_date, check_out_date, "1234567890");
                            }
                        }
                    }
                } else {
                    printf("Please sign in to book a room.\n");
                }
                break;

            case 5:
                viewBookingDetails(customerList);
                break;

            case 6:
                displayVIPFacilities();
                break;

            case 7:
                if (currentUser != NULL) {
                    int room_number;
                    printf("Enter room number to add to wishlist: ");
                    scanf("%d", &room_number);
                    addToWishlist(&wishlist, room_number);
                    printf("Room %d added to wishlist.\n", room_number);
                }
                break;

            case 8:
                viewWishlist(wishlist);
                break;

            case 9:
                if (currentUser != NULL) {
                    int customer_id;
                    printf("Enter Customer ID to cancel booking: ");
                    scanf("%d", &customer_id);
                    cancelBooking(&customerList, customer_id);
                }
                break;

            case 10:
                if (currentUser != NULL) {
                    int customer_id;
                    printf("Enter Customer ID to extend stay: ");
                    scanf("%d", &customer_id);
                    extendStay(customerList, customer_id);
                }
                break;

            case 11:
                printf("Thank you for using the system.\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }

    return 0;
}
