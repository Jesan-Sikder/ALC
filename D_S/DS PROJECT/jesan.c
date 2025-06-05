#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define room types
#define NON_AC 0
#define AC 1
#define VIP 2

// Room structure to store room details
typedef struct Room {
    int room_number;
    int floor;
    int type;  // Non-AC, AC, VIP
    int price;
    int is_available;  // 1 for available, 0 for booked
    struct Room* next;
} Room;

// Customer structure
typedef struct Customer {
    int customer_id;
    char name[100];
    int age;
    int room_number;
    int total_amount;
    int days_of_stay;
    int num_guests;
    int num_children;
    int check_in_date;  // Format YYYYMMDD
    int check_out_date; // Format YYYYMMDD
    char phone_number[15];
    struct Customer* next;
} Customer;

// User structure for sign-up/sign-in
typedef struct User {
    int user_id;
    char username[50];
    char password[50];
    char email[100];
    struct User* next;
} User;

// Wishlist structure for rooms the user saved for later
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

// Initialize rooms with sample data
void initializeRooms(Room* rooms[]) {
    for (int i = 0; i < 2; i++) {  // Floors 1 and 2: Non-AC rooms
        for (int j = 0; j < 10; j++) {
            Room* newRoom = (Room*)malloc(sizeof(Room));
            newRoom->room_number = (i + 1) * 100 + j + 1;
            newRoom->floor = i + 1;
            newRoom->type = NON_AC;
            newRoom->price = 1000;
            newRoom->is_available = 1;
            newRoom->next = rooms[i];
            rooms[i] = newRoom;
        }
    }

    for (int i = 0; i < 10; i++) {  // Floor 3: AC rooms
        Room* newRoom = (Room*)malloc(sizeof(Room));
        newRoom->room_number = 300 + i + 1;
        newRoom->floor = 3;
        newRoom->type = AC;
        newRoom->price = 2000;
        newRoom->is_available = 1;
        newRoom->next = rooms[2];
        rooms[2] = newRoom;
    }

    for (int i = 0; i < 2; i++) {  // Floors 4 and 5: VIP rooms
        for (int j = 0; j < 10; j++) {
            Room* newRoom = (Room*)malloc(sizeof(Room));
            newRoom->room_number = (i + 4) * 100 + j + 1;
            newRoom->floor = i + 4;
            newRoom->type = VIP;
            newRoom->price = 5000;
            newRoom->is_available = 1;
            newRoom->next = rooms[i + 3];
            rooms[i + 3] = newRoom;
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

// Add a customer
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
        printf("Age: %d\n", current->age);
        printf("Room Number: %d\n", current->room_number);
        printf("Total Amount: %d\n", current->total_amount);
        printf("Stay Duration: %d days\n", current->days_of_stay);
        printf("Number of Guests: %d\n", current->num_guests);
        printf("Children: %d\n", current->num_children);
        printf("Check-in Date: %d\n", current->check_in_date);
        printf("Check-out Date: %d\n", current->check_out_date);
        printf("Phone Number: %s\n", current->phone_number);
        printf("\n");
        current = current->next;
    }
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

// Add room to wishlist
void addToWishlist(Wishlist** wishlist, int room_number) {
    Wishlist* newWishlistItem = (Wishlist*)malloc(sizeof(Wishlist));
    newWishlistItem->room_number = room_number;
    newWishlistItem->next = *wishlist;
    *wishlist = newWishlistItem;
    printf("Room %d added to wishlist.\n", room_number);
}

// View rooms in wishlist
void viewWishlist(Wishlist* wishlist) {
    printf("\nRooms in Wishlist:\n");
    Wishlist* current = wishlist;
    while (current != NULL) {
        printf("Room Number: %d\n", current->room_number);
        current = current->next;
    }
}

int main() {
    Room* rooms[5] = {NULL};  // Array to hold rooms (Non-AC, AC, VIP)
    Customer* customerList = NULL;
    User* userList = NULL;
    Wishlist* wishlist = NULL;

    // Initialize rooms
    initializeRooms(rooms);

    int choice;
    User* currentUser = NULL;

    while (1) {
        printf("\nHotel Management System\n");
        printf("1. Sign Up\n");
        printf("2. Sign In\n");
        printf("3. View Rooms\n");
        printf("4. Book Room\n");
        printf("5. View Booking Details\n");
        printf("6. Add to Wishlist\n");
        printf("7. View Wishlist\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                signUp(&userList);
                break;
            case 2:
                currentUser = signIn(userList);
                break;
            case 3:
                printf("View rooms by type:\n");
                printf("1. Non-AC\n");
                printf("2. AC\n");
                printf("3. VIP\n");
                printf("Enter room type: ");
                int roomType;
                scanf("%d", &roomType);
                displayRooms(rooms, roomType - 1); // 0: Non-AC, 1: AC, 2: VIP
                break;
            case 4: {
                if (currentUser == NULL) {
                    printf("Please sign in first.\n");
                    break;
                }
                int room_number, customer_id, days_of_stay, num_guests, num_children, check_in_date, check_out_date;
                char name[100], phone_number[15];

                printf("Enter Room Number to Book: ");
                scanf("%d", &room_number);

                // Check room availability before asking for details
                if (checkRoomAvailability(rooms, room_number) == 0) {
                    printf("Invalid request: Room is not available or does not exist.\n");
                } else {
                    // If room is available, proceed with asking for customer details
                    printf("Enter Customer ID: ");
                    scanf("%d", &customer_id);
                    printf("Enter Full Name: ");
                    scanf(" %[^\n]", name);
                    printf("Enter Age: ");
                    scanf("%d", &days_of_stay);
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
                    Room* bookedRoom = bookRoom(rooms, room_number);
                    if (bookedRoom) {
                        int total_amount = bookedRoom->price * days_of_stay;
                        addCustomer(&customerList, customer_id, name, days_of_stay, room_number, total_amount, days_of_stay, num_guests, num_children, check_in_date, check_out_date, phone_number);
                        printf("Room booked successfully! Total amount: %d\n", total_amount);
                    } else {
                        printf("Room is not available.\n");
                    }
                }
                break;
            }
            case 5:
                viewBookingDetails(customerList);
                break;
            case 6: {
                int room_number;
                printf("Enter room number to add to wishlist: ");
                scanf("%d", &room_number);
                addToWishlist(&wishlist, room_number);
                break;
            }
            case 7:
                viewWishlist(wishlist);
                break;
            case 8:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
