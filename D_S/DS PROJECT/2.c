#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Donor (Linked List Node)
typedef struct Donor {
    char name[50];
    int age;
    char blood_group[5];
    char contact[15];
    struct Donor* next;
} Donor;

// Structure for Blood Group (BST Node)
typedef struct BloodGroup {
    char blood_group[5];
    struct BloodGroup* left;
    struct BloodGroup* right;
} BloodGroup;

// Function to create a new Donor Node
Donor* createDonor(char name[], int age, char blood_group[], char contact[]) {
    Donor* new_donor = (Donor*)malloc(sizeof(Donor));
    strcpy(new_donor->name, name);
    new_donor->age = age;
    strcpy(new_donor->blood_group, blood_group);
    strcpy(new_donor->contact, contact);
    new_donor->next = NULL;
    return new_donor;
}

// Function to create a new Blood Group Node (BST)
BloodGroup* createBloodGroupNode(char blood_group[]) {
    BloodGroup* new_group = (BloodGroup*)malloc(sizeof(BloodGroup));
    strcpy(new_group->blood_group, blood_group);
    new_group->left = new_group->right = NULL;
    return new_group;
}

// Linked List: Add Donor at the end
void addDonor(Donor** head, char name[], int age, char blood_group[], char contact[]) {
    Donor* new_donor = createDonor(name, age, blood_group, contact);
    if (*head == NULL) {
        *head = new_donor;
    } else {
        Donor* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_donor;
    }
}

// Binary Search Tree (BST): Insert Blood Group
BloodGroup* insertBloodGroup(BloodGroup* root, char blood_group[]) {
    if (root == NULL) {
        return createBloodGroupNode(blood_group);
    }
    if (strcmp(blood_group, root->blood_group) < 0) {
        root->left = insertBloodGroup(root->left, blood_group);
    } else if (strcmp(blood_group, root->blood_group) > 0) {
        root->right = insertBloodGroup(root->right, blood_group);
    }
    return root;
}

// Linked List: Display All Donors
void displayDonors(Donor* head) {
    if (head == NULL) {
        printf("No donors available.\n");
        return;
    }
    Donor* temp = head;
    while (temp != NULL) {
        printf("Name: %s\nAge: %d\nBlood Group: %s\nContact: %s\n\n", temp->name, temp->age, temp->blood_group, temp->contact);
        temp = temp->next;
    }
}

// Binary Search Tree (BST): Search for a Blood Group
int searchBloodGroup(BloodGroup* root, char blood_group[]) {
    if (root == NULL) {
        return 0; // Blood group not found
    }
    if (strcmp(blood_group, root->blood_group) == 0) {
        return 1; // Blood group found
    } else if (strcmp(blood_group, root->blood_group) < 0) {
        return searchBloodGroup(root->left, blood_group);
    } else {
        return searchBloodGroup(root->right, blood_group);
    }
}

// Main Function
int main() {
    Donor* donor_list = NULL;  // Linked List head for Donors
    BloodGroup* blood_tree = NULL;  // BST root for Blood Groups

    // Adding blood groups to BST
    blood_tree = insertBloodGroup(blood_tree, "O+");
    blood_tree = insertBloodGroup(blood_tree, "O-");
    blood_tree = insertBloodGroup(blood_tree, "A+");
    blood_tree = insertBloodGroup(blood_tree, "A-");
    blood_tree = insertBloodGroup(blood_tree, "B+");
    blood_tree = insertBloodGroup(blood_tree, "B-");
    blood_tree = insertBloodGroup(blood_tree, "AB+");
    blood_tree = insertBloodGroup(blood_tree, "AB-");

    // Adding some donors to the Linked List
    addDonor(&donor_list, "Alice", 25, "O+", "1234567890");
    addDonor(&donor_list, "Bob", 30, "A+", "9876543210");
    addDonor(&donor_list, "Charlie", 22, "B-", "1029384756");

    int choice;
    char blood_group[5];

    while (1) {
        printf("Blood Bank System Menu:\n");
        printf("1. Add Donor\n");
        printf("2. Display Donors\n");
        printf("3. Search for Available Blood Group\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                {
                    char name[50], contact[15];
                    int age;
                    printf("Enter Donor Name: ");
                    scanf("%s", name);
                    printf("Enter Donor Age: ");
                    scanf("%d", &age);
                    printf("Enter Donor Blood Group: ");
                    scanf("%s", blood_group);
                    printf("Enter Donor Contact: ");
                    scanf("%s", contact);
                    addDonor(&donor_list, name, age, blood_group, contact);
                    blood_tree = insertBloodGroup(blood_tree, blood_group);  // Insert blood group into BST
                    break;
                }
            case 2:
                displayDonors(donor_list);
                break;
            case 3:
                printf("Enter Blood Group to Search (e.g., O+, A-, B+): ");
                scanf("%s", blood_group);
                if (searchBloodGroup(blood_tree, blood_group)) {
                    printf("Blood group %s is available in the Blood Bank.\n", blood_group);
                } else {
                    printf("Blood group %s is not available in the Blood Bank.\n", blood_group);
                }
                break;
            case 4:
                printf("Exiting Blood Bank System.\n");
                return 0;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
