#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure for Donor (Linked List Node)
typedef struct Donor {
    char name[50];
    int age;
    char blood_group[5];
    char gender[10];  // Add gender information
    char contact[15];
    char medical_history[100];  // Add medical history information
    struct tm last_donated;  // Track the date of last donation
    struct Donor* next;
} Donor;

// Structure for Blood Group (BST Node)
typedef struct BloodGroup {
    const char* blood_group;  // Use `const char*` for blood group to avoid modifying string literals
    struct BloodGroup* left;
    struct BloodGroup* right;
} BloodGroup;

// Normalize Blood Group Input (AB+, AB-, O+, O-...)
void normalizeBloodGroup(char* blood_group) {
    for (int i = 0; blood_group[i]; i++) {
        blood_group[i] = toupper(blood_group[i]);  // Convert input to uppercase
    }
}

// Function to create a new Donor Node
Donor* createDonor(const char* name, int age, const char* blood_group, const char* gender, const char* contact, const char* medical_history, struct tm last_donated) {
    Donor* new_donor = (Donor*)malloc(sizeof(Donor));
    strcpy(new_donor->name, name);
    new_donor->age = age;
    strcpy(new_donor->blood_group, blood_group);
    strcpy(new_donor->gender, gender);
    strcpy(new_donor->contact, contact);
    strcpy(new_donor->medical_history, medical_history);
    new_donor->last_donated = last_donated;
    new_donor->next = NULL;
    return new_donor;
}

// Function to create a new Blood Group Node (BST)
BloodGroup* createBloodGroupNode(const char* blood_group) {
    BloodGroup* new_group = (BloodGroup*)malloc(sizeof(BloodGroup));
    new_group->blood_group = blood_group;  // Store string literal directly
    new_group->left = new_group->right = NULL;
    return new_group;
}

// Linked List: Add Donor at the end
void addDonor(Donor** head, const char* name, int age, const char* blood_group, const char* gender, const char* contact, const char* medical_history, struct tm last_donated) {
    Donor* new_donor = createDonor(name, age, blood_group, gender, contact, medical_history, last_donated);
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
BloodGroup* insertBloodGroup(BloodGroup* root, const char* blood_group) {
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
        printf("Name: %s\nAge: %d\nBlood Group: %s\nGender: %s\nContact: %s\nMedical History: %s\nLast Donated: %02d-%02d-%d\n\n", 
                temp->name, temp->age, temp->blood_group, temp->gender, temp->contact, temp->medical_history, 
                temp->last_donated.tm_mday, temp->last_donated.tm_mon + 1, temp->last_donated.tm_year + 1900);
        temp = temp->next;
    }
}

// Binary Search Tree (BST): Search for a Blood Group
int searchBloodGroup(BloodGroup* root, const char* blood_group) {
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

// Check if the donor is eligible to donate again (56 days rule)
int canDonateAgain(struct tm last_donated) {
    time_t now;
    time(&now);
    struct tm* current_time = localtime(&now);
    
    // Calculate the difference in days between the current time and the last donation date
    int diff = (current_time->tm_year - last_donated.tm_year) * 365 +
               (current_time->tm_mon - last_donated.tm_mon) * 30 +
               (current_time->tm_mday - last_donated.tm_mday);

    if (diff >= 56) {
        return 1;  // Eligible to donate
    }
    return 0;  // Not eligible to donate
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

    int choice;
    char blood_group[5], gender[10], contact[15], medical_history[100];
    struct tm last_donated;
    last_donated.tm_year = 120;  // Default value for tm_year (year since 1900)
    last_donated.tm_mon = 0;     // Default January month

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
                    char name[50];
                    int age;
                    printf("Enter Donor Name: ");
                    scanf("%s", name);
                    printf("Enter Donor Age: ");
                    scanf("%d", &age);
                    printf("Enter Donor Gender (Male/Female/Other): ");
                    scanf("%s", gender);
                    printf("Enter Donor Blood Group: ");
                    scanf("%s", blood_group);
                    normalizeBloodGroup(blood_group);  // Normalize blood group (e.g., "AB+" or "ab+")
                    printf("Enter Donor Contact: ");
                    scanf("%s", contact);
                    printf("Enter Medical History (any issues or leave blank): ");
                    getchar(); // Clear newline character
                    fgets(medical_history, 100, stdin);
                    printf("Enter Last Donation Date (DD MM YYYY): ");
                    scanf("%d %d %d", &last_donated.tm_mday, &last_donated.tm_mon, &last_donated.tm_year);
                    last_donated.tm_mon -= 1;  // Adjust month (0-11 range)
                    last_donated.tm_year -= 1900; // Adjust year (since 1900)

                    addDonor(&donor_list, name, age, blood_group, gender, contact, medical_history, last_donated);
                    blood_tree = insertBloodGroup(blood_tree, blood_group);  // Insert blood group into BST
                    break;
                }
            case 2:
                displayDonors(donor_list);
                break;
            case 3:
                printf("Enter Blood Group to Search (e.g., O+, A-, B+): ");
                scanf("%s", blood_group);
                normalizeBloodGroup(blood_group);
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
