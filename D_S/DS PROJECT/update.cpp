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

// Function to input and format date as YYYYMMDD
int inputDateAsInt() {
    char date_str[11];  // Input date string in "YYYY-MM-DD" format
    int year, month, day;
    int formatted_date;

    printf("Enter date (YYYY-MM-DD): ");
    scanf("%s", date_str);  // Get the date input as a string

    // Parse the string using sscanf
    if (sscanf(date_str, "%4d-%2d-%2d", &year, &month, &day) != 3) {
        printf("Invalid date format! Please use YYYY-MM-DD format.\n");
        return -1;  // Return an error code
    }

    // Ensure valid date values
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        printf("Invalid date values!\n");
        return -1;
    }

    // Format the date as YYYYMMDD (integer)
    formatted_date = year * 10000 + month * 100 + day;

    return formatted_date;  // Return the formatted date as an integer
}

// Initialize rooms with sample data
void initializeRooms(Room* rooms[]) {
    // Room initialization logic...
}

// Function definitions for other features (signUp, signIn, addCustomer, etc.) ...

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

        if (choice == 1) {
            signUp(&userList);
        } else if (choice == 2) {
            currentUser = signIn(userList);
        } else if (choice == 3) {
            printf("View rooms by type:\n");
            printf("1. Non-AC\n");
            printf("2. AC\n");
            printf("3. VIP\n");
            printf("Enter room type: ");
            int roomType;
            scanf("%d", &roomType);
            displayRooms(rooms, roomType - 1); // 0: Non-AC, 1: AC, 2: VIP
        } else if (choice == 4) {
            if (currentUser == NULL) {
                printf("Please sign in first.\n");
            } else {
                int room_number, age, customer_id, days_of_stay, num_guests, num_children, check_in_date, check_out_date;
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
                    scanf("%d", &age);
                    printf("Enter Number of Guests: ");
                    scanf("%d", &num_guests);
                    printf("Enter Number of Children: ");
                    scanf("%d", &num_children);
                    printf("Enter Phone Number: ");
                    scanf("%s", phone_number);

                    // Using the inputDateAsInt function to get valid check-in and check-out dates
                    check_in_date = inputDateAsInt();
                    if (check_in_date == -1) continue;  // Skip if invalid date entered

                    check_out_date = inputDateAsInt();
                    if (check_out_date == -1) continue;  // Skip if invalid date entered

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
            }
        } else if (choice == 5) {
            viewBookingDetails(customerList);
        } else if (choice == 6) {
            int room_number;
            printf("Enter room number to add to wishlist: ");
            scanf("%d", &room_number);
            addToWishlist(&wishlist, room_number);
        } else if (choice == 7) {
            viewWishlist(wishlist);
        } else if (choice == 8) {
            printf("Exiting...\n");
            exit(0);
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
