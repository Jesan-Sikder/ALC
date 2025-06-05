#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h> 
struct Room
{
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
    struct Room *next;
};

int choice, roomNumber, days, guests, kids;
char name[50], nid[20], phone[15];
float additionalCost;

void bookRoom(int number, const char *name, const char *nid, const char *phone,
              int duration, int rent, int guests, int kids, struct Room *head)
{
    struct Room *temp = head;
    while (temp != NULL)
    {
        if (temp->number == number)
        {
            if (temp->booked)
            {
                printf("\t\t\t\t\t\tRoom %d is already booked.\n", number);
                return;
            }
            else
            {
                if (guests > temp->maxCapacity)
                {
                    printf("\t\t\t\t\t\tRoom %d cannot accommodate %d guests. The maximum capacity is %d.\n", number, guests, temp->maxCapacity);
                    return;
                }

                temp->booked = 1;
                strncpy(temp->name, name, sizeof(temp->name) - 1);
                strncpy(temp->nid, nid, sizeof(temp->nid) - 1);
                strncpy(temp->phone, phone, sizeof(temp->phone) - 1);
                temp->duration = duration;
                temp->guests = guests;
                temp->kids = kids;
                temp->cost = rent * duration;

                printf("\t\t\t\t\t\tRoom %d booked for %s (NID: %s) for %d days at %.2f total.\n",
                       number, name, nid, duration, temp->cost);
                return;
            }
        }
        temp = temp->next;
    }
    printf("\t\t\t\t\t\tRoom %d not found.\n", number);
}

void cancelRoom(int number, struct Room *head)
{
    struct Room *temp = head;
    while (temp != NULL)
    {
        if (temp->number == number)
        {
            if (!temp->booked)
            {
                printf("\t\t\t\t\t\tRoom %d is not booked.\n", number);
                return;
            }
            else
            {
                temp->booked = 0;
                temp->name[0] = '\0';
                temp->nid[0] = '\0';
                temp->phone[0] = '\0';
                temp->guests = 0;
                temp->kids = 0;
                temp->duration = 0;
                temp->cost = 0.0;
                printf("\t\t\t\t\t\tBooking for Room %d canceled.\n", number);
                return;
            }
        }
        temp = temp->next;
    }
    printf("\t\t\t\t\t\tRoom %d not found.\n", number);
}

void extendorreduceStay(int number, int days, float additionalCost, struct Room *head)
{
    struct Room *temp = head;
    while (temp != NULL)
    {
        if (temp->number == number)
        {
            if (!temp->booked)
            {
                printf("\t\t\t\t\t\tRoom %d is not booked, cannot extend stay.\n", number);
                return;
            }
            else
            {
                temp->duration += days;
                temp->cost = temp->rent * temp->duration;
                printf("\t\t\t\t\t\tExtended stay for Room %d by %d days. Total stay: %d days. New cost: %.2f\n",
                       number, days, temp->duration, temp->cost);
                return;
            }
        }
        temp = temp->next;
    }
    printf("\t\t\t\t\t\tRoom %d not found.\n", number);
}

void showRooms(struct Room *head)
{
    struct Room *temp = head;
    printf("\t\t\t\t\t\tRoom Number\tStatus\t\tCustomer Name\tDays\tRent\t\tAC Status\tMax Capacity\n");
    printf("\t\t\t\t\t\t--------------------------------------------------------------------------------------------------------\n");
    while (temp != NULL)
    {
        printf("\t\t\t\t\t\t%d", temp->number);
        if (temp->booked)
        {
            printf("\t\tBooked\t\t%s\t\t%d\t%d\t\t%s\t\t%d\n",
                   temp->name, temp->duration, temp->rent,
                   (temp->ac ? "AC" : "Non-AC"), temp->maxCapacity);
        }
        else
        {
            printf("\t\tAvailable\tN/A\t\t0\t%d\t\t%s\t\t%d\n",
                   temp->rent, (temp->ac ? "AC" : "Non-AC"), temp->maxCapacity);
        }
        temp = temp->next;
    }
}

void showBookings(struct Room *head)
{
    struct Room *temp = head;
    printf("\t\t\t\t\t\tBooked Rooms:\n");
    printf("\t\t\t\t\t\tRoom Number\tCustomer Name\t\tDays\tPrice\t\tGuests\t\tKids\n");
    printf("\t\t\t\t\t\t-------------------------------------------------------------------------------------------------------\n");
    while (temp != NULL)
    {
        if (temp->booked)
        {
            printf("\t\t\t\t\t\t%-12d\t%-20s\t%-4d\t%.2f\t\t%-6d\t",
                   temp->number, temp->name, temp->duration,
                   temp->cost, temp->guests);
            if (temp->kids)
            {
                printf("\t\t\t\t\t\t\tYes\n");
            }
            else
            {
                printf("\t\t\t\t\t\t\tNo\n");
            }
        }
        temp = temp->next;
    }
}

void freeRooms(struct Room *head)
{
    struct Room *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}
void engine()
{
    struct Room *head = NULL;
    struct Room *last = NULL;

    for (int block = 0; block < 3; block++)
    {
        for (int i = 0; i < 10; i++)
        {
            struct Room *newRoom = (struct Room *)malloc(sizeof(struct Room));
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

            if (head == NULL)
            {
                head = newRoom;
                last = head;
            }
            else
            {
                last->next = newRoom;
                last = newRoom;
            }
        }
    }

    char admin[20];
    char admin_1[20] = "jesan_sikder";
    char admin_2[15] = "faisal2775";
    char admin_3[10] = "raha545";
    char password_1[10] = "0";
    char password_2[15] = "01882740912";
    char password_3[10] = "islam";
    char pass[20];
    int i = 0;

    printf("\t\t\t\t\t\t=================================== Welcome to Majestic Suite ======================================\n");

    printf("\t\t\t\t\t\t\n\n");
    printf("\t\t\t\t\t\t====================================================================================================\n");

    printf("\t\t\t\t\t\tEnter Staff or Admin User ID: \n");
    printf("\t\t\t\t\t\t=");
    scanf("%s", admin);
    // printf("\t\t\t\t\t\t");

    printf("\t\t\t\t\t\tEnter Staff or Admin Login Password: \n");
    printf("\t\t\t\t\t\t=");

    while (1)
    {
        char ch = _getch();

        if (ch == 13)
        {
            pass[i] = '\0';
            break;
        }
        else if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            pass[i] = ch;
            i++;
            printf("  ");
        }
    }
    // printf("\t\t\t\t\t\t\n");

    if (strcmp(admin, admin_1) == 0 && strcmp(pass, password_1) == 0 ||
        strcmp(admin, admin_2) == 0 && strcmp(pass, password_2) == 0 ||
        strcmp(admin, admin_3) == 0 && strcmp(pass, password_3) == 0)
    {

        while (1)
        {
            printf("\n\t\t\t\t\t\t====================================================================================================\n");

            printf("\t\t\t\t\t\t\n");
            printf("\t\t\t\t\t\t\n");

            printf("\t\t\t\t\t\t=================================== A Hotel Management System =======================================\n");
            printf("\t\t\t\t\t\t\n");

            printf("\t\t\t\t\t\t1. Show All Rooms\n");
            printf("\t\t\t\t\t\t2. Book Room\n");
            printf("\t\t\t\t\t\t3. Check Out\n");
            printf("\t\t\t\t\t\t4. View Bookings\n");
            printf("\t\t\t\t\t\t5. Extend or Reduce Stay\n");
            printf("\t\t\t\t\t\t6. Logout\n");
            printf("\t\t\t\t\t\t7. Exit\n");

            printf("\t\t\t\t\t\t\n");

            printf("\t\t\t\t\t\t====================================================================================================\n");
            printf("\t\t\t\t\t\t\n");

            printf("\t\t\t\t\t\tEnter your choice: ");
            scanf("%d", &choice);

            if (choice == 1)
            {
                showRooms(head);
            }
            else if (choice == 2)
            {
                printf("\t\t\t\t\t\tEnter room number: ");
                scanf("%d", &roomNumber);

                struct Room *temp = head;
                while (temp != NULL)
                {
                    if (temp->number == roomNumber)
                    {
                        if (temp->booked)
                        {
                            printf("\t\t\t\t\t\tRoom %d is already booked.\n", roomNumber);
                            break;
                        }
                        break;
                    }
                    temp = temp->next;
                }

                if (temp != NULL && !temp->booked)
                {
                    printf("\t\t\t\t\t\tEnter customer name: ");
                    scanf(" %[^\n]", name);
                    printf("\t\t\t\t\t\tEnter customer NID: ");
                    scanf(" %[^\n]", nid);
                    printf("\t\t\t\t\t\tEnter customer phone: ");
                    scanf(" %[^\n]", phone);
                    printf("\t\t\t\t\t\tEnter stay duration (days): ");
                    scanf("%d", &days);

                    printf("\t\t\t\t\t\tEnter number of guests: ");
                    scanf("%d", &guests);

                    printf("\t\t\t\t\t\tEnter number of kids: ");
                    scanf("%d", &kids);

                    bookRoom(roomNumber, name, nid, phone, days, temp->rent, guests, kids, head);
                }
            }
            else if (choice == 3)
            {
                printf("\t\t\t\t\t\tEnter room number to cancel: ");
                scanf("%d", &roomNumber);
                cancelRoom(roomNumber, head);
            }
            else if (choice == 4)
            {
                showBookings(head);
            }
            else if (choice == 5)
            {
                printf("\t\t\t\t\t\tEnter room number to extend/reduce stay: ");
                scanf("%d", &roomNumber);
                printf("\t\t\t\t\t\tEnter days to extend (positive) or reduce (negative): ");
                scanf("%d", &days);
                extendorreduceStay(roomNumber, days, additionalCost, head);
            }
            else if (choice == 6)
            {
                printf("\n\t\t\t\t\t\tLogging you out %s !!!\n\n",admin);

                return engine();
            }
             else if (choice == 7)
            {
                freeRooms(head); 
                break; 
                
            }
        }
    }
    else
    {
        printf("\n\t\t\t\t\t\tInvalid Admin ID or Password.\n\n");
        return engine();
        printf("\t\t\t\t\t\t\n");
    }
}
void loadingAnimation() {
    char* dots[] = {".......", "...................", "........................", ".............................", "............................................."};
    int i = 0;

    for (int j = 0; j < 3; j++) {
        printf("\n\t\t\t\t\t\tLoading Hotel Management System");
        
        
        printf("%s", dots[i]);
        fflush(stdout);  

        Sleep(500);  

        
        system("cls");
        
      
        i = (i + 1) % 5;
    }

    
    printf("\n\n\t\t\t\t\t\tLoading Complete!\n");
}

/************************************************************************* */

int main()
{
    loadingAnimation();

    engine();

    return 0;
}


/***************************************************************************** */

