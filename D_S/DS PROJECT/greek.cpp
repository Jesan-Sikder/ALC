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
    int room_number;
    int total_amount;
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

// Booking structure to store booking details including dates
typedef struct Booking {
    int room_number;
    int check_in_date;
    int check_out_date;
    struct Booking* next;
} Booking;

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
void addCustomer(Customer** customerList, int id, char* name, int room_number, int total_amount);
void viewBookingDetails(Customer* customerList);
void displayVIPFacilities();
void signUp(User** userList);
User* signIn(User* userList);
void addToWishlist(Wishlist** wishlist, int room_number);
void viewWishlist(Wishlist* wishlist);
int checkRoomAvailability(Room* rooms[], int room_number, int check_in_date, int check_out_date);
int compareDates(int date1, int date2);

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

// Check if the room is available for the given dates
int checkRoomAvailability(Room* rooms[], int room_number, int check_in_date, int check_out_date) {
    // Simulate checking availability based on dates
    return 1;  // Assume room is available for simplicity
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
void addCustomer(Customer** customerList, int id, char* name, int room_number, int total_amount) {
    Customer* newCustomer = (Customer*)malloc(sizeof(Customer));
    newCustomer->customer_id = id;
    strcpy(newCustomer->name, name);
    newCustomer->room_number = room_number;
    newCustomer->total_amount = total_amount;
    newCustomer->next = *customerList;
    *customerList = newCustomer;
}

// View booking details
void viewBookingDetails(Customer* customerList) {
    printf("\nBooking Details:\n");
    Customer* current = customerList;
    while (current != NULL) {
        printf("Customer ID: %d, Name: %s, Room Number: %d, Total Amount: %d\n",
               current->customer_id, current->name, current->room_number, current->total_amount);
        current = current->next;
    }
}

// Display VIP facilities
void displayVIPFacilities() {
    printf("\nVIP Facilities: Gym, Swimming Pool, Bar, Party Place\n");
}

// Sign-Up function to create a new user
void signUp(User** userList) {
    User* newUser = (User*)malloc(sizeof(User));
    printf("Enter Username: ");
    scanf("%s", newUser->username);
    printf("Enter Password: ");
    scanf("%s", newUser->password);
    printf("Enter Email: ");
    scanf("%s", newUser->email);
    newUser->user_id = rand() % 1000;  // Assign a random user ID for simplicity
    newUser->next = *userList;
    *userList = newUser;
    printf("User created successfully!\n");
}

// Sign-In function for users
User* signIn(User* userList) {
    char username[50], password[50];
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    User* current = userList;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0) {
            printf("Sign-in successful!\n");
            return current;
        }
        current = current->next;
    }
    printf("Invalid credentials. Please try again.\n");
    return NULL;
}

// Add a room to the wishlist
void addToWishlist(Wishlist** wishlist, int room_number) {
    Wishlist* newWishlistItem = (Wishlist*)malloc(sizeof(Wishlist));
    newWishlistItem->room_number = room_number;
    newWishlistItem->next = *wishlist;
    *wishlist = newWishlistItem;
    printf("Room %d added to wishlist.\n", room_number);
}

// View the wishlist
void viewWishlist(Wishlist* wishlist) {
    printf("\nWishlist:\n");
    Wishlist* current = wishlist;
    while (current != NULL) {
        printf("Room Number: %d\n", current->room_number);
        current = current->next;
    }
}

int main() {
    Room* rooms[5] = {NULL};
    Customer* customerList = NULL;
    User* userList = NULL;
    Wishlist* wishlist = NULL;

    // Initialize rooms data
    initializeRooms(rooms);

    int choice;
    while (1) {
        printf("\nHotel Management System\n");
        printf("1. Sign Up\n");
        printf("2. Sign In\n");
        printf("3. View Available Rooms\n");
        printf("4. Book Room\n");
        printf("5. View Booking Details\n");
        printf("6. VIP Facilities\n");
        printf("7. Add Room to Wishlist\n");
        printf("8. View Wishlist\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                signUp(&userList);
                break;
            case 2:
                signIn(userList);
                break;
            case 3:
                printf("Available Non-AC Rooms:\n");
                displayRooms(rooms, NON_AC);
                printf("Available AC Rooms:\n");
                displayRooms(rooms, AC);
                printf("Available VIP Rooms:\n");
                displayRooms(rooms, VIP);
                break;
            case 4: {
                int room_number;
                printf("Enter room number to book: ");
                scanf("%d", &room_number);
                Room* bookedRoom = bookRoom(rooms, room_number);
                if (bookedRoom) {
                    printf("Room %d booked successfully!\n", room_number);
                } else {
                    printf("Room is not available or doesn't exist.\n");
                }
                break;
            }
            case 5:
                viewBookingDetails(customerList);
                break;
            case 6:
                displayVIPFacilities();
                break;
            case 7: {
                int room_number;
                printf("Enter room number to add to wishlist: ");
                scanf("%d", &room_number);
                addToWishlist(&wishlist, room_number);
                break;
            }
            case 8:
                viewWishlist(wishlist);
                break;
            case 9:
                exit(0);
        }
    }

    return 0;
}
