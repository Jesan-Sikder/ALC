#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>




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
    struct tm bookingDate;
    struct Room *next;
    struct tm checkInDate;
};




int choice, roomNumber, days, guests, kids;
char name[50], nid[20], phone[15];
float additionalCost;








int isPastDate(int day, int month, int year)
{
    time_t t = time(NULL);
    struct tm currentDate = *localtime(&t);

    
    int currentYear = currentDate.tm_year + 1900;
    int currentMonth = currentDate.tm_mon + 1;  
    int currentDay = currentDate.tm_mday;

   
    if (year < currentYear)
    {
        return 1;  
    }
    else if (year == currentYear)
    {
        
        if (month < currentMonth)
        {
            return 1;  
        }
        else if (month == currentMonth)
        {
            
            if (day < currentDay)
            {
                return 1;  
            }
        }
    }
    return 0;  
}
int selectDate(int month, int year)
{
    int day;
    while (1)
    {
        printf("\tEnter a day from the calendar (1-31): ");
        scanf("%d", &day);

        
        if (day < 1 || day > 31)
        {
            printf("\tInvalid day. Please select a valid day.\n");
            continue;
        }

       
        if (isPastDate(day, month, year))
        {
            printf("\tThe selected date is in the past. Please choose a valid future date.\n");
        }
        else
        {
            return day;  
        }
    }
}






void bookRoom(int number, const char *name, const char *nid, const char *phone,
              const char *passport, const char *country, int duration, int rent, int guests, int kids, struct Room *head,
              int day, int month, int year)
{
    struct Room *temp = head;
    while (temp != NULL)
    {
        if (temp->number == number)
        {
            if (temp->booked)
            {
                if (!isPastDate(temp->bookingDate.tm_mday, temp->bookingDate.tm_mon + 1, temp->bookingDate.tm_year + 1900))
                {
                    printf("\tRoom %d is booked for a future date and is available today.\n", number);
                    return;
                }
                else
                {
                    printf("\tRoom %d is already booked for today.\n", number);
                    return;
                }
            }
            else
            {
                if (guests > temp->maxCapacity)
                {
                    printf("\tRoom %d cannot accommodate %d guests. The maximum capacity is %d.\n", number, guests, temp->maxCapacity);
                    return;
                }

                temp->booked = 1;
                strncpy(temp->name, name, sizeof(temp->name) - 1);
                strncpy(temp->nid, nid, sizeof(temp->nid) - 1);

                if (passport[0] != '\0')
                {
                    strncpy(temp->nid, passport, sizeof(temp->nid) - 1);
                    strncpy(temp->phone, country, sizeof(temp->phone) - 1);
                }
                else
                {
                    strncpy(temp->phone, phone, sizeof(temp->phone) - 1);
                }

                temp->duration = duration;
                temp->guests = guests;
                temp->kids = kids;
                temp->cost = rent * duration;

                temp->bookingDate.tm_year = year - 1900;
                temp->bookingDate.tm_mon = month - 1;
                temp->bookingDate.tm_mday = day;

                printf("\tRoom %d booked for %s (NID: %s, Phone: %s) for %d days at %.2f total.\n",
                       number, name, nid, phone, duration, temp->cost);
                return;
            }
        }
        temp = temp->next;
    }
    printf("\tRoom %d not found.\n", number);
}









void showRooms(struct Room *head)
{
    struct Room *temp = head;
    printf("Room Number\tStatus\t\tCustomer Name\tDays\tRent\t\tAC Status\tMax Capacity\tBooking Date\n");
    printf("--------------------------------------------------------------------------------------------------------------------------\n");

    if (temp == NULL)
    {
        printf("\tNo rooms available.\n");
        return;
    }

    
    time_t t = time(NULL);
    struct tm currentDate = *localtime(&t);
    int currentYear = currentDate.tm_year + 1900;
    int currentMonth = currentDate.tm_mon + 1;  
    int currentDay = currentDate.tm_mday;

    while (temp != NULL)
    {
        printf("%d\t\t", temp->number);
        
     
        if (temp->booked)
        {
            
            if (temp->bookingDate.tm_year + 1900 < currentYear ||
                (temp->bookingDate.tm_year + 1900 == currentYear && temp->bookingDate.tm_mon + 1 < currentMonth) ||
                (temp->bookingDate.tm_year + 1900 == currentYear && temp->bookingDate.tm_mon + 1 == currentMonth && temp->bookingDate.tm_mday <= currentDay))
            {
                
                printf("Booked\t\t%s\t\t%d\t%d\t\t%s\t\t%d\t\t%02d-%02d-%d\n",
                       temp->name, temp->duration, temp->rent,
                       (temp->ac ? "AC" : "Non-AC"), temp->maxCapacity,
                       temp->bookingDate.tm_mday, temp->bookingDate.tm_mon + 1, temp->bookingDate.tm_year + 1900);
            }
            else
            {
                
                printf("Reserved\t%s\t\t%d\t%d\t\t%s\t\t%d\t\t%02d-%02d-%d\n",
                       temp->name, temp->duration, temp->rent,
                       (temp->ac ? "AC" : "Non-AC"), temp->maxCapacity,
                       temp->bookingDate.tm_mday, temp->bookingDate.tm_mon + 1, temp->bookingDate.tm_year + 1900);
            }
        }
        else
        {
            
            printf("Available\tN/A\t\t0\t%d\t\t%s\t\t%d\t\tN/A\n", temp->rent, (temp->ac ? "AC" : "Non-AC"), temp->maxCapacity);
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







void cancelRoom(int number, struct Room *head)
{
    struct Room *temp = head;
    while (temp != NULL)
    {
        if (temp->number == number)
        {
            if (!temp->booked)
            {
                printf("\tRoom %d is not booked.\n", number);
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
                printf("\tBooking for Room %d canceled.\n", number);
                return;
            }
        }
        temp = temp->next;
    }
    printf("\tRoom %d not found.\n", number);
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
                printf("\tRoom %d is not booked, cannot extend stay.\n", number);
                return;
            }
            else
            {
                temp->duration = days;
                temp->cost = temp->rent * temp->duration;
                printf("\tExtended stay for Room %d by %d days. Total stay: %d days. New cost: %.2f\n",
                       number, days, temp->duration, temp->cost);
                return;
            }
        }
        temp = temp->next;
    }
    printf("\t\t\t\t\t\tRoom %d not found.\n", number);
}








void getValidPhoneNumber(char *phone)
{
    int valid = 0;
    while (!valid)
    {
        printf("\tEnter customer phone number (11 digits): ");
        scanf(" %[^\n]", phone);

        if (strlen(phone) == 11 && strspn(phone, "0123456789") == 11)
        {
            valid = 1;
        }
        else
        {
            printf("\tInvalid phone number. Please enter exactly 11 digits.\n");
        }
    }
}








void getValidnid(char *nid)
{
    int valid = 0;
    while (!valid)
    {
        printf("\tEnter customer NID Number(10 digits): ");
        scanf(" %[^\n]", nid);

        if (strlen(nid) == 10 && strspn(nid, "0123456789") == 10)
        {
            valid = 1;
        }
        else
        {
            printf("\tInvalid NID Number . Please enter exactly 10 digits.\n");
        }
    }
}










void showBookings(struct Room *head)
{
    struct Room *temp = head;
    printf("\tBooked Rooms:\n");
    printf("Room Number\tCustomer Name\t\tDays\tPrice\t\tGuests\t\tKids\t\tBooking Date\n");
    printf("------------------------------------------------------------------------------------------------------------\n");
    while (temp != NULL)
    {
        if (temp->booked)
        {
            printf("%-12d\t%-20s\t%-4d\t%.2f\t%-6d\t\t",
                   temp->number, temp->name, temp->duration,
                   temp->cost, temp->guests);
            if (temp->kids)
            {
                printf("Yes\t\t");
            }
            else
            {
                printf("No\t\t");
            }

            printf("%02d-%02d-%d\n",
                   temp->bookingDate.tm_mday, temp->bookingDate.tm_mon + 1, temp->bookingDate.tm_year + 1900);
        }
        temp = temp->next;
    }
}









int getValidRoomNumber()
{
    int roomNumber;
    while (1)
    {
        printf("\tEnter room number: ");
        if (scanf("%d", &roomNumber) == 1)
        {
            if ((roomNumber > 100 && roomNumber < 111) || (roomNumber > 200 && roomNumber < 211) ||
                (roomNumber > 300 && roomNumber < 311))
            {
                return roomNumber;
            }
            else
            {
                printf("\tInvalid room number.\n");
            }
        }
        else
        {

            while (getchar() != '\n')
            printf("\tInvalid room number. Please enter a valid integer.\n");
        }
    }
}










void checkInRoom(struct Room *head)
{
    int searchChoice;
    char phone[15], nid[20], passport[20];
    int roomNumber;
    struct Room *temp = head;

  
    printf("\n\tSearch by:\n");
    printf("\t1. Room Number\n");
    printf("\t2. Phone Number\n");
    printf("\t3. NID Number\n");
    printf("\t4. Passport Number\n");
    printf("\tEnter your choice: ");
    scanf("%d", &searchChoice);

    switch (searchChoice)
    {
    case 1:

        printf("\tEnter room number: ");
        scanf("%d", &roomNumber);
        temp = head;
        while (temp != NULL)
        {
            if (temp->number == roomNumber)
            {
                break;
            }
            temp = temp->next;
        }
        break;
    case 2:

        printf("\tEnter phone number: ");
        scanf(" %[^\n]", phone);
        temp = head;
        while (temp != NULL)
        {
            if (strcmp(temp->phone, phone) == 0)
            {
                break;
            }
            temp = temp->next;
        }
        break;
    case 3:

        printf("\tEnter NID number: ");
        scanf(" %[^\n]", nid);
        temp = head;
        while (temp != NULL)
        {
            if (strcmp(temp->nid, nid) == 0)
            {
                break;
            }
            temp = temp->next;
        }
        break;
    case 4:

        printf("\tEnter passport number: ");
        scanf(" %[^\n]", passport);
        temp = head;
        while (temp != NULL)
        {
            if (strcmp(temp->nid, passport) == 0)
            {
                break;
            }
            temp = temp->next;
        }
        break;
    default:
        printf("\tInvalid choice. Please select a valid option.\n");
        return;
    }

    if (temp == NULL)
    {
        printf("\tNo guest found matching the criteria.\n");
        return;
    }

    if (temp->booked)
    {

        if (temp->guests > 0)
        {
            printf("\tChecking in Room %d...\n", temp->number);
            time_t t = time(NULL);
            struct tm checkInTime = *localtime(&t);

            temp->checkInDate = checkInTime;

            printf("\tCustomer %s is now checked in.\n", temp->name);
            printf("\tCheck-in Time: %02d-%02d-%d %02d:%02d:%02d\n",
                   checkInTime.tm_mday, checkInTime.tm_mon + 1, checkInTime.tm_year + 1900,
                   checkInTime.tm_hour, checkInTime.tm_min, checkInTime.tm_sec);
        }
        else
        {
            printf("\tRoom %d has no guests to check in.\n", temp->number);
        }
    }
    else
    {
        printf("\tRoom %d is not booked. Cannot check in.\n", temp->number);
    }
}










void checkout(int number, struct Room *head)
{
    struct Room *temp = head;
    while (temp != NULL)
    {
        if (temp->number == number)
        {
            if (!temp->booked)
            {
                printf("\tRoom %d is not booked.\n", number);
                return;
            }
            else
            {

                printf("\n\t--- Bill for Room %d ---\n", number);
                printf("\tCustomer Name: %s\n", temp->name);
                printf("\tStay Duration: %d days\n", temp->duration);
                printf("\tTotal Cost: %.2f\n", temp->cost);

                float discountPercentage = 0.0;
                char applyDiscount;
                printf("\tDo you want to apply a discount? (Y/N): ");
                scanf(" %c", &applyDiscount);

                if (applyDiscount == 'Y' || applyDiscount == 'y')
                {
                    printf("\tEnter discount percentage: ");
                    scanf("%f", &discountPercentage);
                    if (discountPercentage < 0 || discountPercentage > 100)
                    {
                        printf("\tInvalid discount percentage! Please enter a value between 0 and 100.\n");
                        return;
                    }

                    float discountAmount = (discountPercentage / 100) * temp->cost;
                    temp->cost -= discountAmount;
                    printf("\tDiscount Applied: %.2f%%\n", discountPercentage);
                    printf("\tNew Total After Discount: %.2f\n", temp->cost);
                }

                int paymentChoice;
                printf("\n\tChoose Payment Method:\n");
                printf("\t1. Fastest Cash\n");
                printf("\t2. Card\n");
                printf("\t3. Bank Transfer\n");
                printf("\tEnter your choice (1/2/3): ");
                scanf("%d", &paymentChoice);

                switch (paymentChoice)
                {
                case 1:
                    printf("\tPayment received via Fastest Cash.\n");
                    break;
                case 2:
                    printf("\tPayment received via Card.\n");
                    break;
                case 3:
                    printf("\tPayment received via Bank Transfer.\n");
                    break;
                default:
                    printf("\tInvalid payment method.\n");
                    return;
                }

                temp->booked = 0;
                temp->name[0] = '\0';
                temp->nid[0] = '\0';
                temp->phone[0] = '\0';
                temp->guests = 0;
                temp->kids = 0;
                temp->duration = 0;
                temp->cost = 0.0;

                printf("\tBooking for Room %d checked out successfully !!.\n", number);
                return;
            }
        }
        temp = temp->next;
    }
    printf("Room %d not found.\n", number);
}










void engine()
{
    static struct Room *head = NULL;
    struct Room *last = NULL;

    if (head == NULL)
    {

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
    }

    char admin[20];
    char admin_1[20] = "0";
    char admin_2[15] = "faisal2775";
    char admin_3[10] = "raha545";
    char password_1[10] = "0";
    char password_2[15] = "01882740912";
    char password_3[10] = "islam";
    char pass[20];
    int i = 0;

    printf("\t======Welcome to Living Eco======\n");

    printf("\n");

    printf("\tEnter Staff or Admin User ID : ");

    scanf("%s", admin);

    printf("\tEnter Staff or Admin Login Password : ");

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
            printf("*");
        }
    }

    if (strcmp(admin, admin_1) == 0 && strcmp(pass, password_1) == 0 ||
        strcmp(admin, admin_2) == 0 && strcmp(pass, password_2) == 0 ||
        strcmp(admin, admin_3) == 0 && strcmp(pass, password_3) == 0)
    {
        while (1)
        {
            printf("\n\tHotel Management System\n");
            printf("\t1. Show All Rooms\n");
            printf("\t2. Book Room\n");
            printf("\t3. Check In\n");
            printf("\t4. Check Out\n");
            printf("\t5. View Bookings\n");
            printf("\t6. Extend or Reduce Stay\n");
            printf("\t7. Cancel Booking\n");
            printf("\t8. Log Out\n");
            printf("\t9. Exit\n");
            printf("\tEnter your choice: ");
            scanf("%d", &choice);

            if (choice == 1)
            {
                showRooms(head);
            }
            else if (choice == 2)
            {

                roomNumber = getValidRoomNumber();
                struct Room *temp = head;
                while (temp != NULL)
                {
                    if (temp->number == roomNumber)
                    {
                        if (temp->booked)
                        {

                            if (!isPastDate(temp->bookingDate.tm_mday, temp->bookingDate.tm_mon + 1, temp->bookingDate.tm_year + 1900))
                            {
                                printf("\tRoom %d is booked for a future date and is available today.\n", roomNumber);
                                break;
                            }
                            printf("\tRoom %d is already booked for today.\n", roomNumber);
                        }
                        break;
                    }
                    temp = temp->next;
                }

                if (temp != NULL && !temp->booked)
                {
                    printf("\tEnter customer name: ");
                    scanf(" %[^\n]", name);

                    char guestType;
                    printf("\tIs the customer local or foreign? (L/F): ");
                    scanf(" %c", &guestType);
                    char phone[15] = {0};
                    char passport[20] = {0};
                    char country[50] = {0};

                    if (guestType == 'F' || guestType == 'f')
                    {
                        printf("\tEnter passport number: ");
                        scanf(" %[^\n]", passport);

                        getchar();

                        printf("\tEnter country name: ");
                        scanf(" %[^\n]", country);
                    }

                    else
                    {

                        getValidPhoneNumber(phone);
                        getValidnid(nid);
                    }

                    int day, month, year;
                    printf("\tEnter booking month (1-12): ");
                    scanf("%d", &month);
                    printf("\tEnter booking year: ");
                    scanf("%d", &year);

                    day = selectDate(month, year);

                    printf("\tEnter stay duration (days): ");
                    scanf("%d", &days);

                    printf("\tEnter number of guests: ");
                    scanf("%d", &guests);

                    printf("\tEnter number of kids: ");
                    scanf("%d", &kids);

                    bookRoom(roomNumber, name, nid, phone, passport, country, days, temp->rent, guests, kids, head, day, month, year);
                }
            }

            else if (choice == 4)
            {
                printf("\tEnter room number to check out: ");
                scanf("%d", &roomNumber);
                checkout(roomNumber, head);
            }

            else if (choice == 7)
            {
                printf("\tEnter room number to cancel: ");
                scanf("%d", &roomNumber);
                cancelRoom(roomNumber, head);
            }
            else if (choice == 3)
            {
                checkInRoom(head);
            }
            else if (choice == 5)
            {
                showBookings(head);
            }
            else if (choice == 6)
            {
                printf("\tEnter room number to extend/reduce stay: ");
                scanf("%d", &roomNumber);
                printf("\tEnter days to extend (positive) or reduce (negative): ");
                scanf("%d", &days);
                extendorreduceStay(roomNumber, days, additionalCost, head);
            }
            else if (choice == 8)
            {
                printf("\n\tLogging you out %s !!!\n\n", admin);

                return engine();
            }
            else if (choice == 9)
            {
                printf("\tExiting !!!......\n");
                break;
            }
        }
    }
    else
    {
        printf("\n\tInvalid Admin ID or Password.\n\n");
        return engine();
        printf("\n");
    }
}








int main()
{
    engine();
}
