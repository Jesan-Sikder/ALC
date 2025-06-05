#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 100
#define MAX_BLOOD_GROUP_LENGTH 5
#define FILE_NAME_BLOOD "blood_stock.dat"
#define FILE_NAME_DONORS "donors.dat"

// Structure for donor details (linked list node)
struct Donor {
    char name[MAX_NAME_LENGTH];
    char bloodGroup[MAX_BLOOD_GROUP_LENGTH];
    int age;
    struct Donor* next; // pointer to the next donor in the linked list
};

// Structure for blood stock (BST node)
struct BloodStock {
    char bloodGroup[MAX_BLOOD_GROUP_LENGTH];
    int quantity;  // quantity in units
    struct BloodStock* left;   // pointer to left child
    struct BloodStock* right;  // pointer to right child
};

// Function to create a new donor
struct Donor* createDonor(char name[], char bloodGroup[], int age) {
    struct Donor* newDonor = (struct Donor*)malloc(sizeof(struct Donor));
    strcpy(newDonor->name, name);
    strcpy(newDonor->bloodGroup, bloodGroup);
    newDonor->age = age;
    newDonor->next = NULL;
    return newDonor;
}

// Function to add a donor to the linked list
void addDonor(struct Donor** head, char name[], char bloodGroup[], int age) {
    struct Donor* newDonor = createDonor(name, bloodGroup, age);
    newDonor->next = *head;
    *head = newDonor;
    printf("Donor added successfully!\n");
}

// Function to create a new blood stock node (for BST)
struct BloodStock* createBloodStockNode(char bloodGroup[], int quantity) {
    struct BloodStock* newNode = (struct BloodStock*)malloc(sizeof(struct BloodStock));
    strcpy(newNode->bloodGroup, bloodGroup);
    newNode->quantity = quantity;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a blood stock node into the BST
struct BloodStock* insertBloodStock(struct BloodStock* root, char bloodGroup[], int quantity) {
    if (root == NULL) {
        return createBloodStockNode(bloodGroup, quantity);
    }

    int cmp = strcmp(bloodGroup, root->bloodGroup);
    if (cmp < 0) {
        root->left = insertBloodStock(root->left, bloodGroup, quantity);
    } else if (cmp > 0) {
        root->right = insertBloodStock(root->right, bloodGroup, quantity);
    } else {
        root->quantity += quantity;  // If blood group already exists, update quantity
    }

    return root;
}

// Function to search for a blood stock node in the BST
struct BloodStock* searchBloodStock(struct BloodStock* root, char bloodGroup[]) {
    if (root == NULL || strcmp(root->bloodGroup, bloodGroup) == 0) {
        return root;
    }

    int cmp = strcmp(bloodGroup, root->bloodGroup);
    if (cmp < 0) {
        return searchBloodStock(root->left, bloodGroup);
    } else {
        return searchBloodStock(root->right, bloodGroup);
    }
}

// Function to request blood (decrease quantity in BST)
void requestBlood(struct BloodStock* root, char bloodGroup[]) {
    struct BloodStock* stock = searchBloodStock(root, bloodGroup);
    if (stock != NULL) {
        if (stock->quantity > 0) {
            stock->quantity--;
            printf("Blood requested successfully! Remaining stock: %d\n", stock->quantity);
        } else {
            printf("Sorry, blood group %s is out of stock.\n", bloodGroup);
        }
    } else {
        printf("Blood group %s not found in stock.\n", bloodGroup);
    }
}

// Function to display blood stock in order (BST traversal)
void displayBloodStock(struct BloodStock* root) {
    if (root != NULL) {
        displayBloodStock(root->left);
        printf("%s: %d units\n", root->bloodGroup, root->quantity);
        displayBloodStock(root->right);
    }
}

// Function to display donor list (linked list traversal)
void displayDonors(struct Donor* head) {
    printf("\nDonor List:\n");
    while (head != NULL) {
        printf("Name: %s, Blood Group: %s, Age: %d\n", head->name, head->bloodGroup, head->age);
        head = head->next;
    }
}

// Function to load blood stock from file
void loadBloodStockFromFile(struct BloodStock** root) {
    FILE* file = fopen(FILE_NAME_BLOOD, "r");
    if (!file) {
        printf("No existing blood stock file found. Starting fresh.\n");
        return;
    }

    char bloodGroup[MAX_BLOOD_GROUP_LENGTH];
    int quantity;

    while (fscanf(file, "%s %d", bloodGroup, &quantity) != EOF) {
        *root = insertBloodStock(*root, bloodGroup, quantity);
    }

    fclose(file);
}

// Function to save blood stock to file
void saveBloodStockToFile(struct BloodStock* root) {
    FILE* file = fopen(FILE_NAME_BLOOD, "w");
    if (!file) {
        printf("Error opening blood stock file for saving.\n");
        return;
    }

    // Traverse BST in order to save blood stock
    if (root != NULL) {
        fprintf(file, "%s %d\n", root->bloodGroup, root->quantity);
        saveBloodStockToFile(root->left);
        saveBloodStockToFile(root->right);
    }

    fclose(file);
}

// Function to load donor data from file
void loadDonorsFromFile(struct Donor** head) {
    FILE* file = fopen(FILE_NAME_DONORS, "r");
    if (!file) {
        printf("No existing donor file found. Starting fresh.\n");
        return;
    }

    char name[MAX_NAME_LENGTH], bloodGroup[MAX_BLOOD_GROUP_LENGTH];
    int age;

    while (fscanf(file, "%s %s %d", name, bloodGroup, &age) != EOF) {
        addDonor(head, name, bloodGroup, age);
    }

    fclose(file);
}

// Function to save donor data to file
void saveDonorsToFile(struct Donor* head) {
    FILE* file = fopen(FILE_NAME_DONORS, "w");
    if (!file) {
        printf("Error opening donor file for saving.\n");
        return;
    }

    // Traverse the linked list to save donor data
    while (head != NULL) {
        fprintf(file, "%s %s %d\n", head->name, head->bloodGroup, head->age);
        head = head->next;
    }

    fclose(file);
}

// Main program with direct function calls and no switch-case
int main() {
    struct Donor* donorList = NULL; // Head of the linked list
    struct BloodStock* bloodStockRoot = NULL; // Root of the BST

    // Load data from files (if any)
    loadDonorsFromFile(&donorList);
    loadBloodStockFromFile(&bloodStockRoot);

    // Menu-driven approach without switch-case
    while (1) {
        int choice;
        printf("\nBlood Bank System\n");
        printf("1. Add Donor\n");
        printf("2. Request Blood\n");
        printf("3. Add Blood to Stock\n");
        printf("4. View Donors\n");
        printf("5. View Blood Stock\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            char name[MAX_NAME_LENGTH], bloodGroup[MAX_BLOOD_GROUP_LENGTH];
            int age;
            printf("Enter donor name: ");
            getchar();  // consume newline left by previous input
            fgets(name, MAX_NAME_LENGTH, stdin);
            name[strcspn(name, "\n")] = '\0'; // remove newline character

            printf("Enter blood group (A+, B+, AB+, O+, A-, B-, AB-, O-): ");
            scanf("%s", bloodGroup);

            printf("Enter donor age: ");
            scanf("%d", &age);

            addDonor(&donorList, name, bloodGroup, age);
            saveDonorsToFile(donorList); // Save updated donor list to file
        }
        else if (choice == 2) {
            char bloodGroup[MAX_BLOOD_GROUP_LENGTH];
            printf("Enter blood group to request: ");
            scanf("%s", bloodGroup);
            requestBlood(bloodStockRoot, bloodGroup);
            saveBloodStockToFile(bloodStockRoot); // Save updated blood stock
        }
        else if (choice == 3) {
            char bloodGroup[MAX_BLOOD_GROUP_LENGTH];
            int quantity;
            printf("Enter blood group to add: ");
            scanf("%s", bloodGroup);
            printf("Enter quantity to add: ");
            scanf("%d", &quantity);
            bloodStockRoot = insertBloodStock(bloodStockRoot, bloodGroup, quantity);
            saveBloodStockToFile(bloodStockRoot); // Save updated blood stock
        }
        else if (choice == 4) {
            displayDonors(donorList);
        }
        else if (choice == 5) {
            displayBloodStock(bloodStockRoot);
        }
        else if (choice == 6) {
            printf("Exiting the system. Goodbye!\n");
            break; // Exit the program
        }
        else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
