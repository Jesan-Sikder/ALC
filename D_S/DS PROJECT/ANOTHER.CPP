#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure for donor details (linked list node)
struct Donor {
    char name[100];
    char bloodGroup[5];
    int age;
    struct Donor* next; // pointer to the next donor in the linked list
};

// Structure for blood stock (BST node)
struct BloodStock {
    char bloodGroup[5];
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
    
    // Compare blood groups and insert accordingly
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

// Main program
int main() {
    struct Donor* donorList = NULL; // Head of the linked list
    struct BloodStock* bloodStockRoot = NULL; // Root of the BST
    
    int choice;
    char name[100], bloodGroup[5];
    int age, quantity;
    
    while (1) {
        printf("\nBlood Bank System\n");
        printf("1. Add Donor\n");
        printf("2. Request Blood\n");
        printf("3. Add Blood to Stock\n");
        printf("4. View Donors\n");
        printf("5. View Blood Stock\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:  // Add Donor
                printf("Enter donor name: ");
                getchar();  // consume newline left by previous input
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0'; // remove newline character
                
                printf("Enter blood group (A+, B+, AB+, O+, A-, B-, AB-, O-): ");
                scanf("%s", bloodGroup);
                
                printf("Enter donor age: ");
                scanf("%d", &age);
                
                addDonor(&donorList, name, bloodGroup, age);
                break;
            
            case 2:  // Request Blood
                printf("Enter blood group to request: ");
                scanf("%s", bloodGroup);
                requestBlood(bloodStockRoot, bloodGroup);
                break;
            
            case 3:  // Add Blood to Stock
                printf("Enter blood group to add: ");
                scanf("%s", bloodGroup);
                
                printf("Enter quantity to add: ");
                scanf("%d", &quantity);
                
                bloodStockRoot = insertBloodStock(bloodStockRoot, bloodGroup, quantity);
                break;
            
            case 4:  // View Donors
                displayDonors(donorList);
                break;
            
            case 5:  // View Blood Stock
                printf("\nCurrent Blood Stock:\n");
                displayBloodStock(bloodStockRoot);
                break;
            
            case 6:  // Exit
                printf("Exiting the system. Goodbye!\n");
                return 0;
            
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}
