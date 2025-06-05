// #include <bits/stdc++.h>
// using namespace std;
// #define ass return 0
// #define ll long long
// #define dd double
// int main(){
//     int t;
//     cin>>t;
//     int
//     for (int  i = 0; i < t; i++)
//     {
//         /* code */
//     }
    
// ass;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

int menuSize = 0;

typedef struct {
    char name[100];
    int price;
} MenuItem;

MenuItem menu[MAX];

void saveMenu(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Could not open menu file\n");
        return;
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
        return;
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
        printf("Could not open orders file\n");
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

void Bill_Payment(int sum) {
    int cash, changer, n;
    system("cls");
    system("color 3F");
    printf("\n\t\t\tYour Total Bill is = %d", sum);
    
    do {
        printf("\n\t\t\tPay your bill (Provide Cash): ");
        scanf("%d", &cash);
        changer = cash - sum;
        if (changer == 0) {
            printf("\n\t\tThanks for your payment. Have a great day!\n");
        } else if (changer < 0) {
            printf("\n\t\t\tAmount is not sufficient. Please pay the fair price of your bill\n");
        } else {
            printf(RED"\n\n\n\t\tHere is your change: (%d - %d) = %d Tk.\n", cash, sum, changer);
            printf(WHITE"\n\n\n\t\t\tThanks for your payment.\n\t\t\t    Have a great day!\n");
        }

        printf("\n\n\t\t\t<Enter (1) to order more.>\n\t\t\t<Enter (2) to go back main menu>\n\t\t\t<Enter (3) to give review>\n\n\n\t\t\tEnter your choice: ");
        scanf("%d", &n);
        
        if (n == 1) {
            menu_order();
        } else if (n == 2) {
            return; // Return to main menu
        } else if (n == 3) {
            leaveReview();
        }
    } while (changer < 0);
}

int Bill_show(int arID[], int arqty[], int counter) {
    int sum = 0;
    system("cls");
    system("color B0");

    printf("\n\nYour Bill:\n\n\n\t\tItem(s)\t\t     Quantity\t\t    Cost\n\n\n\n");
    for (int i = 0; i < counter; i++) {
        printf("\t%2d. %-16s ________\t%-5d piece(s) ____ %7d\n", i + 1, menu[arID[i] - 1].name, arqty[i], arqty[i] * menu[arID[i] - 1].price);
        sum += arqty[i] * menu[arID[i] - 1].price;
    }
    printf("\n\n\n\n\t\t\t\t\t\t\t  Total = %d\n\n\n\n", sum);
    printf("\t\t\t For pay bill ENTER 1 : ");
    return sum;
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
                return; // Go back to main menu
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

int main() {
    loadMenu("menu.txt");
    int choice;
    
    do {
        choice = mainPage();
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
    } while (choice != 1 && choice != 2);

    return 0;
}
