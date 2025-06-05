#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <windows.h>
#define MAX 100
#define RESET_COLOR "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"
#define BOLD "\x1b[1m"

int main();
void adminMenu();
void menu_order();
typedef struct {
    char name[100];
    int price;
} MenuItem;

MenuItem menu[MAX];
int menuSize = 0;


void saveMenu(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Could not open menu file");
        exit(1);
    }
    for (int i = 0; i < menuSize; i++) {
        fprintf(file, "%s,%d\n", menu[i].name, menu[i].price);
    }
    fclose(file);
}

void loadMenu(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open menu file");
        exit(1);
    }
    menuSize = 0;
    while (fscanf(file, " %49[^,],%d", menu[menuSize].name, &menu[menuSize].price) == 2) {
        menuSize++;
    }
    fclose(file);
}

void displayMenu() {
    system("cls");
    system("color 4F");
    printf("\n\t\t\t\tFOOD MENU\n\t\t\t\t---------\n");
    for (int i = 0; i < menuSize; i++) {
        printf("\t%d. %s ...................... %d/=\n", i + 1, menu[i].name, menu[i].price);
    }
}

void logOrder(int arID[], int arqty[], int counter) {
    FILE *file = fopen("orders.txt", "a");
    if (!file) {
        printf("Could not open orders file");
        return;
    }
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(file, "%02d-%02d-%04d %02d:%02d:%02d, ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);

    for (int i = 0; i < counter; i++) {
        fprintf(file, "%s:%d,", menu[arID[i] - 1].name, arqty[i]);
    }
    fprintf(file, "\n");
    fclose(file);
}

void viewDailyIncome() {
    system("cls");
    system("color 6F");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char dateStr[11];
    snprintf(dateStr, sizeof(dateStr), "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    FILE *file = fopen("orders.txt", "r");
    if (!file) {
        perror("Could not open orders file");
        return;
    }

    char line[256];
    int dailyTotal = 0;
    printf("Daily Orders on %s:\n", dateStr);

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, dateStr, 10) == 0) {
            printf("%s", line);
            char *token = strtok(line + 20, ",");
            while (token) {
                char itemName[MAX];
                int itemQty;
                sscanf(token, "%[^:]:%d", itemName, &itemQty);
                for (int i = 0; i < menuSize; i++) {
                    if (strcmp(menu[i].name, itemName) == 0) {
                        dailyTotal += menu[i].price * itemQty;
                        break;
                    }
                }
                token = strtok(NULL, ",");
            }
        }
    }
    fclose(file);
    printf("\nTotal daily income: %d BDT\n", dailyTotal);
    printf("Press any key to continue...");
    getchar();
    getchar();
}

void viewMonthlyIncome() {
    system("cls");
    system("color 6F");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char dateStr[8];
    snprintf(dateStr, sizeof(dateStr), "%02d-%04d", tm.tm_mon + 1, tm.tm_year + 1900);

    FILE *file = fopen("orders.txt", "r");
    if (!file) {
        perror("Could not open orders file");
        return;
    }

    char line[256];
    int monthlyTotal = 0;
    printf("Monthly Orders for %s:\n", dateStr);

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line + 3, dateStr, 7) == 0) {
            printf("%s", line);
            char *token = strtok(line + 20, ",");
            while (token) {
                char itemName[MAX];
                int itemQty;
                sscanf(token, "%[^:]:%d", itemName, &itemQty);
                for (int i = 0; i < menuSize; i++) {
                    if (strcmp(menu[i].name, itemName) == 0) {
                        monthlyTotal += menu[i].price * itemQty;
                        break;
                    }
                }
                token = strtok(NULL, ",");
            }
        }
    }
    fclose(file);
    printf("\nTotal monthly income: %d BDT\n", monthlyTotal);
    printf("Press any key to continue...");
    getchar();
    getchar();
}

void leaveReview() {
    system("cls");
    char review[MAX];
    char comment[MAX];
    FILE *file = fopen("reviews.txt", "a");
    if (!file) {
        perror("Could not open reviews file");
        return;
    }

    printf("\n\n\t\tGive us 5[*****] *_*: ");
    getchar();
    fgets(review, MAX, stdin);
    printf("\n\t\tLeave a comment:");
    fgets(comment, MAX, stdin);
    fprintf(file, "%s ", review);
    fprintf(file, "%s\n", comment);
    fclose(file);
    printf("Thank you for your review!\n");
    //Sleep(200);
    main();
}
void Bill_Payment(int sum)
{

    int i,cash,changer,n;
    system("cls");
    system("color 3F");
    printf("\n\t\t\tYour Total Bill is = %d",sum);
    work:
            printf("\n\t\t\tPay your bill (Provide Cash): ");
            scanf("%d",&cash);
    changer = cash-sum;
    if(changer == 0)
    {
        printf("\n\t\tThanks for your payment. Have a great day!\n");
    }
    else if (changer<0)
    {
        system("cls");
        printf("\n\t\t\tAmount is not sufficient. :(\n\t\tPlease pay the fair price of your bill\n");
        goto work;
    }
    else
    {
        printf(RED"\n\n\n\t\tHere is your change : (%d - %d) = %d Tk.\n\t\t  ",cash,sum,changer);

            for(i=0;i<19;i++)
            {
                printf("_");
            }
            if(changer>=1000 )
                {printf("\n\t\t1000 Tk. note(s) = %d\n",changer/1000);
                changer=changer%1000;}
            if(changer>=500 && changer<1000)
            {printf("\n\t\t 500 Tk. note(s) = %d\n",changer/500);
            changer=changer%500;}
            if(changer>=100 && changer<500)
            {printf("\n\t\t 100 Tk. note(s) = %d\n",changer/100);
            changer= changer%100;}
            if(changer>=50 && changer<100)
            {printf("\n\t\t  50 Tk. note(s) = %d\n",changer/50);
            changer=changer%50;}
             if(changer>=10 && changer<50)
            {printf("\n\t\t  10 Tk. note(s) = %d\n",changer/10);
            changer=changer%10;}
            if(changer>=5 && changer<10)
            {printf("\n\t\t   5 Tk. note(s) = %d\n",changer/5);
            changer=changer%5;}
            if(changer>=2 && changer<5)
            {printf("\n\t\t   2 Tk. note(s) = %d\n",changer/2);
            changer=changer%2;}
            if(changer>=1 && changer<2)
            {printf("\n\t\t   1 Tk. note(s) = %d\n",changer/1);
            changer=changer%1;}

            printf("\t\t  ");
            for(i=0;i<19;i++)
            {
                printf("_");
            }

        printf(WHITE"\n\n\n\n\n\t\t\tThanks for your payment.\n\t\t\t    Have a great day!\n",changer);



    }
    printf("\n\n\t\t\t<Enter (1) to order more.>\n\t\t\t<Enter (2) to go back main menu>\n\t\t\t<Enter (3) to give review>\n\n\n\t\t\tEnter your choice: \t");
        scanf("%d",&n);
         if (n == 1) {
        menu_order();
    }
    else if (n == 2) {
        main();
    }
    else if (n == 3){
        leaveReview();
    }
}


int Bill_show(int arID[], int arqty[], int counter) {
    int a;
    system("cls");
    system("color B0");

    int i, sum = 0;
    printf("\n\nYour Bill:\n\n\n\t\tItem(s)\t\t     Quantity\t\t    Cost\n\n\n\n");

    for (i = 0; i < counter; i++) {
        printf("\t%2d. %-16s ________\t%-5d piece(s) ____ %7d\n", i + 1, menu[arID[i] - 1].name, arqty[i], arqty[i] * menu[arID[i] - 1].price);
        sum += arqty[i] * menu[arID[i] - 1].price;
    }

    printf("\n\n\n\n\t\t\t\t\t\t\t  Total = %d\n\n\n\n", sum);
    printf("\t\t\t For pay bill ENTER 1 : ");
    scanf("%d",&a);
    if(a==1){
        logOrder(arID, arqty, counter);
        return sum;
    }
    return 0;
}

void addMenuItem() {
    if (menuSize >= MAX) {
        printf("Menu is full! Cannot add more items.\n");
        return;
    }
    printf("Enter the name of the new item: ");
    getchar();
    fgets(menu[menuSize].name, MAX, stdin);
    menu[menuSize].name[strcspn(menu[menuSize].name, "\n")] = 0;
    printf("Enter the price of the new item: ");
    scanf("%d", &menu[menuSize].price);
    menuSize++;
    saveMenu("menu.txt");
    printf("Item added successfully!\n");
}

void deleteMenuItem() {
    int id;
    displayMenu();
    printf("Enter the ID of the item to delete: ");
    scanf("%d", &id);
    if (id < 1 || id > menuSize) {
        printf("Invalid item ID!\n");
        return;
    }
    for (int i = id - 1; i < menuSize - 1; i++) {
        menu[i] = menu[i + 1];
    }
    menuSize--;
    saveMenu("menu.txt");
    printf("Item deleted successfully!\n");
}

void modifyMenuItem() {
    int id;
    displayMenu();
    printf("Enter the ID of the item to modify: ");
    scanf("%d", &id);
    if (id < 1 || id > menuSize) {
        printf("Invalid item ID!\n");
        return;
    }
    printf("Enter the new name of the item: ");
    getchar();
    fgets(menu[id - 1].name, MAX, stdin);
    menu[id - 1].name[strcspn(menu[id - 1].name, "\n")] = 0;
    printf("Enter the new price of the item: ");
    scanf("%d", &menu[id - 1].price);
    saveMenu("menu.txt");
    printf("Item modified successfully!\n");
}
int adminLogin() {
    char username[MAX];
    char password[MAX];
    char fileUsername[MAX];
    char filePassword[MAX];
    system("cls");
    system("color 6F");
    FILE *file = fopen("users.txt", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
                printf ("Now you can update menu.");
                fclose(file);
               // Sleep(1000);
                adminMenu();
        }
        else {
            printf("Invalid username or password.\n");
            break;
        }
    }
    fclose(file);
    return 1;
}
void viewReview() {
    system("cls");
    FILE *file = fopen("reviews.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("All Reviews:\n");
    printf("-------------------\n");

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
        printf("-------------------\n");
    }

    fclose(file);
     printf("Press any key to continue...");
    getchar();
    getchar();
}

void adminMenu() {
    int choice;
    while (1) {
        system("cls");
        printf("Admin Menu\n");
        printf("1. Add Menu Item\n");
        printf("2. Delete Menu Item\n");
        printf("3. Modify Menu Item\n");
        printf("4. View Daily Income\n");
        printf("5. View Monthly Income\n");
        printf("6. View Reviews\n");
        printf("7. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addMenuItem();
                break;
            case 2:
                deleteMenuItem();
                break;
            case 3:
                modifyMenuItem();
                break;
            case 4:
                viewDailyIncome();
                break;
            case 5:
                viewMonthlyIncome();
                break;
            case 6:
                viewReview();
                break;
            case 7:
                main();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

int isUsernameExists(const char *username) {
    char fileUsername[MAX];
    char filePassword[MAX];
    FILE *file = fopen("users.txt", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        if (strcmp(username, fileUsername) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void registerMember() {
    char username[MAX];
    char password[MAX];
    char confirmPassword[MAX];
    ok:
    system("cls");
    system("color 6F");

    printf(MAGENTA"\n\n\tEnter a new username: ");
    scanf("%s", username);

    if (isUsernameExists(username)) {
        printf("Username already exists. Please choose another username.\n");
      //  Sleep(400);
        goto ok;
    }

    printf("\n\tEnter a password: ");
    scanf("%s", password);

    printf("\tConfirm password: ");
    scanf("%s", confirmPassword);

    if (strcmp(password, confirmPassword) != 0) {
        printf("Passwords do not match. Registration failed.\n");
      //  Sleep(400);
        goto ok;
    }

    FILE *file = fopen("users.txt", "a");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%s %s\n", username, password);
    fclose(file);
    printf("Registration successful.\n");
   // Sleep(500);
    main();
}

int login() {
    char username[MAX];
    char password[MAX];
    char fileUsername[MAX];
    char filePassword[MAX];
    system("cls");
    system("color 6F");
    FILE *file = fopen("users.txt", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    printf(MAGENTA"\n\n\t\tEnter username: ");
    scanf("%s", username);
    printf("\t\tEnter password: ");
    scanf("%s", password);

    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
            printf("Login successful.\n");
            fclose(file);
           // Sleep(500);
            menu_order();
        }
    }
    printf("Invalid username or password.\n");
    //sleep(1);
    fclose(file);
    main();
}

int mainPage() {
    int a;
    system("cls");
    system("color 2F");
    printf("\n\n\n\n\n");
    printf("    ##                  ## ######### #         .****     .****.     ##*     *## #########  \n");
  //  Sleep(400);
    printf("     ##       ##       ##  #         #        **        **     **   ## *   * ## #           \n");
  //  Sleep(400);
    printf("      ##     #  #     ##   #         #       **        **       **  ##  * *  ## #            \n");
  //  Sleep(400);
    printf("       ##   #    #   ##    # ###     #       **        **       **  ##   *   ## # ###          \n");
   // Sleep(400);
    printf("        ## #      # ##     #         #        **        **     **   ##       ## #               \n");
   // Sleep(400);
    printf("         ##        ##      ######### ########   ****      ****      ##       ## #########         \n");
  //  Sleep(400);
    printf("         \n\n TO               \n");
    printf(RED"                PRO CODER RESTAURANT         \n");
    printf(WHITE"  Owners:                       \n");
    printf("           RISHAT   <_>          \n");
    printf("           EVA       -_-      \n");
    printf("           RISHA      '.'      \n");
    printf("           ANIK        +_+          \n");
    printf(CYAN " +-----------------------------------------------+  \n");
    printf(WHITE" |    1. CUSTOMER PANEL                          |   \n");
    printf(     " |                                               |  \n ");
    printf(     "|    2. ADMIN PANEL                             |  \n ");
    printf(     "|                                               |  \n ");
    printf(CYAN "+-----------------------------------------------+  ");
    printf(BLUE"              \n\n \t\t\n Enter 1 or 2 : ");
    scanf("%d",&a);
    return a;
}

void menu_order() {
    int arID[10], decision, arqty[10], counter = 0,sum;
    char check;
    while (1) {
        displayMenu();
        printf("\n\n\tOrder your dish\n");
        while (1) {
            printf("\t Enter Food ID: ");
            scanf("%d", &arID[counter]);
            printf("\t Enter Quantity: ");
            scanf("%d", &arqty[counter]);
            printf("\t If you want to order more ENTER (y) for yes or (n) for NO : ");
            scanf(" %c", &check);
            counter++;
            if (check == 'n') {
                break;
            }
        }

        system("cls");
        printf("\n\n\n\n\n\n\n\n\n\n\t\tThanks for your order. We are getting ready the dishes.\n\t\tUntil then, have some selfies with friends. Enjoy!\n\n\n\n\n\t\t\t  <Enter 1 to check your bill>\n\t\t\tEnter your choice: ");
        scanf("%d", &decision);

        if (decision == 1) {
            sum = Bill_show(arID, arqty, counter);
            Bill_Payment(sum);
            break;
        } else {
            break;
        }
    }
}
void customerPanel(){
    system("cls");
    system("color 6B");
    printf("\n\n \t1. REGESTRATION \n \t2. LOGIN\n\n");
    printf(RED"\t\t\tENTER 1 OR 2 -> ");
    int c;
    scanf("%d",&c);
    if(c==1)
        registerMember();
    else if(c==2)
        login();
    else{
        printf("Enter a valid number");
        //sleep(1);
        customerPanel();}
}
int main() {
    loadMenu("menu.txt");
    int choice = mainPage();
    switch (choice) {
        case 1:
            customerPanel();
            break;
        case 2:
            adminLogin();
            break;
        default:
            printf("Invalid choice.\n");
    }
    return 0;
}