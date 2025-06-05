#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Room {
    int number;
    int booked;
    char name[50];
    char nid[20];
    char phone[15];
    int guests;
    int kids;
    int rent;
    int ac;
    int duration;
    float cost;
    int maxCapacity;
    struct Room* next;
};

int choice, roomNumber, days, guests, kids;
char name[50], nid[20], phone[15];
float additionalCost;

void bookRoom(int number, const char* name, const char* nid, const char* phone,
              const char* passport, const char* country, int duration, int rent, int guests, int kids, struct Room* head) {
    struct Room* temp = head;
    while (temp != NULL) {
        if (temp->number == number) {
            if (temp->booked) {
                printf("Room %d is already booked.\n", number);
                return;
            } else {
                if (guests > temp->maxCapacity) {
                    printf("Room %d cannot accommodate %d guests. The maximum capacity is %d.\n", number, guests, temp->maxCapacity);
                    return;
                }

                temp->booked = 1;
                strncpy(temp->name, name, sizeof(temp->name) - 1);
                strncpy(temp->nid, nid, sizeof(temp->nid) - 1);

                // If foreign, store passport number and country
                if (passport[0] != '\0') {
                    strncpy(temp->nid, passport, sizeof(temp->nid) - 1);  // Use the passport as the NID
                    strncpy(temp->phone, country, sizeof(temp->phone) - 1); // Use country as phone
                } else {
                    strncpy(temp->phone, phone, sizeof(temp->phone) - 1);
                }

                temp->duration = duration;
                temp->guests = guests;
                temp->kids = kids;
                temp->cost = rent * duration;

                printf("Room %d booked for %s (NID: %s, Phone: %s) for %d days at %.2f total.\n",
                       number, name, nid, phone, duration, temp->cost);
                return;
            }
        }
        temp = temp->next;
    }
    printf("Room %d not found.\n", number);
}

void cancelRoom(int number, struct Room* head) {
    struct Room* temp = head;
    while (temp != NULL) {
        if (temp->number == number) {
            if (!temp->booked) {
                printf("Room %d is not booked.\n", number);
                return;
            } else {
                // Display the bill before canceling
                printf("\n--- Bill for Room %d ---\n", number);
                printf("Customer Name: %s\n", temp->name);
                printf("Stay Duration: %d days\n", temp->duration);
                printf("Total Cost: %.2f\n", temp->cost);

                // Ask if the customer has a discount
                float discountPercentage = 0.0;
                char applyDiscount;
                printf("Do you want to apply a discount? (Y/N): ");
                scanf(" %c", &applyDiscount);

                if (applyDiscount == 'Y' || applyDiscount == 'y') {
                    printf("Enter discount percentage: ");
                    scanf("%f", &discountPercentage);
                    if (discountPercentage < 0 || discountPercentage > 100) {
                        printf("Invalid discount percentage! Please enter a value between 0 and 100.\n");
                        return;
                    }
                    // Apply the discount
                    float discountAmount = (discountPercentage / 100) * temp->cost;
                    temp->cost -= discountAmount;
                    printf("Discount Applied: %.2f%%\n", discountPercentage);
                    printf("New Total After Discount: %.2f\n", temp->cost);
                }

                // Ask for payment method
                int paymentChoice;
                printf("\nChoose Payment Method:\n");
                printf("1. Fastest Cash\n");
                printf("2. Card\n");
                printf("3. Bank Transfer\n");
                printf("Enter your choice (1/2/3): ");
                scanf("%d", &paymentChoice);

                switch(paymentChoice) {
                    case 1:
                        printf("Payment received via Fastest Cash.\n");
                        break;
                    case 2:
                        printf("Payment received via Card.\n");
                        break;
                    case 3:
                        printf("Payment received via Bank Transfer.\n");
                        break;
                    default:
                        printf("Invalid payment method.\n");
                        return;
                }

                // Proceed with the cancellation
                temp->booked = 0;
                temp->name[0] = '\0';
                temp->nid[0] = '\0';
                temp->phone[0] = '\0';
                temp->guests = 0;
                temp->kids = 0;
                temp->duration = 0;
                temp->cost = 0.0;

                printf("Booking for Room %d canceled.\n", number);
                return;
            }
        }
        temp = temp->next;
    }
    printf("Room %d not found.\n", number);
}



void extendorreduceStay(int number, int days, float additionalCost, struct Room* head) {
    struct Room* temp = head;
    while (temp != NULL) {
        if (temp->number == number) {
            if (!temp->booked) {
                printf("Room %d is not booked, cannot extend stay.\n", number);
                return;
            } else {
                temp->duration = days;
                temp->cost = temp->rent * temp->duration;
                printf("Extended stay for Room %d by %d days. Total stay: %d days. New cost: %.2f\n",
                       number, days, temp->duration, temp->cost);
                return;
            }
        }
        temp = temp->next;
    }
    printf("Room %d not found.\n", number);
}

void showRooms(struct Room* head) {
    struct Room* temp = head;
    printf("Room Number\tStatus\t\tCustomer Name\tDays\tRent\t\tAC Status\tMax Capacity\n");
    printf("--------------------------------------------------------------------------------------------------------\n");
    while (temp != NULL) {
        printf("%d\t\t", temp->number);
        if (temp->booked) {
            printf("Booked\t\t%s\t\t%d\t%d\t\t%s\t\t%d\n",
                   temp->name, temp->duration, temp->rent,
                   (temp->ac ? "AC" : "Non-AC"), temp->maxCapacity);
        } else {
            printf("Available\tN/A\t\t0\t%d\t\t%s\t\t%d\n",
                   temp->rent, (temp->ac ? "AC" : "Non-AC"), temp->maxCapacity);
        }
        temp = temp->next;
    }
}

void showBookings(struct Room* head) {
    struct Room* temp = head;
    printf("Booked Rooms:\n");
    printf("Room Number\tCustomer Name\t\tDays\tPrice\t\tGuests\t\tKids\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    while (temp != NULL) {
        if (temp->booked) {
            printf("%-12d\t%-20s\t%-4d\t%.2f\t\t%-6d\t",
                   temp->number, temp->name, temp->duration,
                   temp->cost, temp->guests);
            if (temp->kids) {
                printf("\tYes\n");
            } else {
                printf("\tNo\n");
            }
        }
        temp = temp->next;
    }
}

void freeRooms(struct Room* head) {
    struct Room* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Room* head = NULL;
    struct Room* last = NULL;

    for (int block = 0; block < 3; block++) {
        for (int i = 0; i < 10; i++) {
            struct Room* newRoom = (struct Room*)malloc(sizeof(struct Room));
            int roomNumber = (block + 1) * 100 + (i + 1);
            newRoom->number = roomNumber;
            newRoom->booked = 0;
            newRoom->name[0] = '\0';
            newRoom->nid[0] = '\0';
            newRoom->phone[0] = '\0';
            newRoom->guests = 0;
            newRoom->kids = 0;
            newRoom->rent = 2000 + (i % 3) * 1000;
            newRoom->duration = 0;
            newRoom->cost = 0.0;
            newRoom->ac = (i % 2 == 0) ? 1 : 0;
            newRoom->maxCapacity = 2 + rand() % 5;
            newRoom->next = NULL;

            if (head == NULL) {
                head = newRoom;
                last = head;
            } else {
                last->next = newRoom;
                last = newRoom;
            }
        }
    }

    char admin[20];
    char admin_1[10] = "jesan545";
    char admin_2[15] = "faisal2775";
    char admin_3[10] = "raha545";
    char password_1[10] = "admin69";
    char password_2[15] = "324725";
    char password_3[10] = "islam";
    char pass[20];

    printf("Enter Staff or Admin User ID: ");
    scanf("%s", admin);
    printf("Enter Staff or Admin Login Password: ");
    scanf("%s", pass);

    if (strcmp(admin, admin_1) == 0 && strcmp(pass, password_1) == 0 ||
        strcmp(admin, admin_2) == 0 && strcmp(pass, password_2) == 0 ||
        strcmp(admin, admin_3) == 0 && strcmp(pass, password_3) == 0) {

        while (1) {
            printf("\nHotel Management System\n");
            printf("1. Show All Rooms\n");
            printf("2. Book Room\n");
            printf("3. Check Out\n");
            printf("4. View Bookings\n");
            printf("5. Extend or Reduce Stay\n");
            printf("6. Log Out\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            if (choice == 1) {
                showRooms(head);
            } else if (choice == 2) {
                printf("Enter room number: ");
                scanf("%d", &roomNumber);

                struct Room* temp = head;
                while (temp != NULL) {
                    if (temp->number == roomNumber) {
                        if (temp->booked) {
                            printf("Room %d is already booked.\n", roomNumber);
                            break;
                        }
                        break;
                    }
                    temp = temp->next;
                }

                if (temp != NULL && !temp->booked) {
                    printf("Enter customer name: ");
                    scanf(" %[^\n]", name);

                    // Ask if the guest is local or foreign
                    char guestType;
                    printf("Is the customer local or foreign? (L/F): ");
                    scanf(" %c", &guestType);

                    char phone[15] = {0};
                    char passport[20] = {0};
                    char country[50] = {0};

                    if (guestType == 'F' || guestType == 'f') {
                        printf("Enter passport number (9 digits): ");
                        scanf("%s", passport);
                        printf("Enter country name: ");
                        scanf(" %[^\n]", country);
                    } else {
                        printf("Enter customer NID: ");
                        scanf(" %[^\n]", nid);
                        printf("Enter customer phone: ");
                        scanf(" %[^\n]", phone);
                    }

                    printf("Enter stay duration (days): ");
                    scanf("%d", &days);

                    printf("Enter number of guests: ");
                    scanf("%d", &guests);

                    printf("Enter number of kids: ");
                    scanf("%d", &kids);

                    bookRoom(roomNumber, name, nid, phone, passport, country, days, temp->rent, guests, kids, head);
                }
            } else if (choice == 3) {
                printf("Enter room number to check out: ");
                scanf("%d", &roomNumber);
                cancelRoom(roomNumber, head);
            } else if (choice == 4) {
                showBookings(head);
            } else if (choice == 5) {
                printf("Enter room number to extend/reduce stay: ");
                scanf("%d", &roomNumber);
                printf("Enter number of extend/reduce days: ");
                scanf("%d", &days);
                extendorreduceStay(roomNumber, days, additionalCost, head);
            } else if (choice == 6) {
                printf("Logged out successfully.\n");
                break;
            } else {
                printf("Invalid choice, please try again.\n");
            }
        }
    } else {
        printf("Incorrect User ID or Password.\n");
    }

    freeRooms(head);
    return 0;
}

