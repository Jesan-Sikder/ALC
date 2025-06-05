#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BOOKS_CAPACITY 10
#define INITIAL_USERS_CAPACITY 10

// Structures
typedef struct {
    int bookID;
    char title[50];
    char author[50];
    int available;  // 1 for available, 0 for issued
} Book;

typedef struct {
    int userID;
    char name[50];
    char borrowedBookTitle[50];  // Empty string means no book borrowed
} User;

// Global Variables
Book *books = NULL;
User *users = NULL;
int totalBooks = 0, totalUsers = 0;
int booksCapacity = 0, usersCapacity = 0;
int nextUserID = 1;  // Start userID from 1

// Function Prototypes
void startMenu();
void issueBook();
void returnBook();
void addBook();
void addUser();
void displayBooks();
void displayUsers();
void deleteBook();
void deleteUser();
void expandBooks();
void expandUsers();
int findBookByTitle(const char *title);
int findUserByID(int userID);
void loadSampleData();
void freeLibrary();

int main() {
    loadSampleData();
    startMenu();
    freeLibrary();
    return 0;
}

void startMenu() {
    int choice;
    while (1) {
        printf("\n==== Library Management System ====\n");
        printf("1. Add Book\n");
        printf("2. Add User\n");
        printf("3. Display Books\n");
        printf("4. Display Users\n");
        printf("5. Issue Book\n");
        printf("6. Return Book\n");
        printf("7. Delete Book\n");
        printf("8. Delete User\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: addUser(); break;
            case 3: displayBooks(); break;
            case 4: displayUsers(); break;
            case 5: issueBook(); break;
            case 6: returnBook(); break;
            case 7: deleteBook(); break;
            case 8: deleteUser(); break;
            case 9:
                printf("Exiting program. Goodbye!\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void issueBook() {
    int userID;
    char bookTitle[50];

    printf("Enter User ID: ");
    scanf("%d", &userID);
    getchar(); // Consume newline

    // Validate User ID
    int userIndex = findUserByID(userID);
    if (userIndex == -1) {
        printf("Invalid User ID. Please try again.\n");
        return;
    }

    // Check if the user already borrowed a book
    if (strlen(users[userIndex].borrowedBookTitle) > 0) {
        printf("User already has a borrowed book. Please return it first.\n");
        return;
    }

    // Enter the book title to issue
    printf("Enter the title of the book to issue: ");
    fgets(bookTitle, sizeof(bookTitle), stdin);
    bookTitle[strcspn(bookTitle, "\n")] = '\0';  // Remove trailing newline

    // Validate Book Title
    int bookIndex = findBookByTitle(bookTitle);
    if (bookIndex == -1 || books[bookIndex].available == 0) {
        printf("Invalid or unavailable book title. Please check again.\n");
        return;
    }

    // Issue the book
    books[bookIndex].available = 0;
    strcpy(users[userIndex].borrowedBookTitle, bookTitle);
    printf("Book '%s' issued successfully to User ID %d.\n", bookTitle, userID);
}

void returnBook() {
    int userID;
    printf("Enter User ID: ");
    scanf("%d", &userID);

    // Validate User ID
    int userIndex = findUserByID(userID);
    if (userIndex == -1) {
        printf("Invalid User ID. Please try again.\n");
        return;
    }

    // Check if the user has borrowed a book
    if (strlen(users[userIndex].borrowedBookTitle) == 0) {
        printf("This user has not borrowed any book.\n");
        return;
    }

    // Return the book
    int bookIndex = findBookByTitle(users[userIndex].borrowedBookTitle);
    books[bookIndex].available = 1;
    strcpy(users[userIndex].borrowedBookTitle, "");
    printf("Book returned successfully.\n");
}

void addBook() {
    if (totalBooks == booksCapacity) {
        expandBooks();
    }
    Book newBook;
    printf("Enter Book ID: ");
    scanf("%d", &newBook.bookID);
    getchar();  // Consume newline
    printf("Enter Book Title: ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0';  // Remove trailing newline
    printf("Enter Book Author: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';  // Remove trailing newline
    newBook.available = 1;

    books[totalBooks++] = newBook;
    printf("Book added successfully.\n");
}

void addUser() {
    if (totalUsers == usersCapacity) {
        expandUsers();
    }
    User newUser;
    newUser.userID = nextUserID++;  // Automatically assign and increment userID
    getchar();  // Consume newline
    printf("Enter User Name: ");
    fgets(newUser.name, sizeof(newUser.name), stdin);
    newUser.name[strcspn(newUser.name, "\n")] = '\0';  // Remove trailing newline
    strcpy(newUser.borrowedBookTitle, "");

    users[totalUsers++] = newUser;
    printf("User added successfully with ID %d.\n", newUser.userID);
}

void deleteBook() {
    char bookTitle[50];
    printf("Enter the title of the book to delete: ");
    getchar();  // Consume newline
    fgets(bookTitle, sizeof(bookTitle), stdin);
    bookTitle[strcspn(bookTitle, "\n")] = '\0';  // Remove trailing newline

    int bookIndex = findBookByTitle(bookTitle);
    if (bookIndex == -1) {
        printf("Book not found.\n");
        return;
    }

    for (int i = bookIndex; i < totalBooks - 1; i++) {
        books[i] = books[i + 1];
    }
    totalBooks--;
    printf("Book deleted successfully.\n");
}

void deleteUser() {
    int userID;
    printf("Enter User ID to delete: ");
    scanf("%d", &userID);

    int userIndex = findUserByID(userID);
    if (userIndex == -1) {
        printf("User not found.\n");
        return;
    }

    if (strlen(users[userIndex].borrowedBookTitle) > 0) {
        printf("User cannot be deleted because they have a borrowed book.\n");
        return;
    }

    for (int i = userIndex; i < totalUsers - 1; i++) {
        users[i] = users[i + 1];
    }
    totalUsers--;
    printf("User deleted successfully.\n");
}

void displayBooks() {
    printf("\nList of Books:\n");
    for (int i = 0; i < totalBooks; i++) {
        printf("ID: %d | Title: %s | Author: %s | %s\n", books[i].bookID,
               books[i].title, books[i].author,
               books[i].available ? "Available" : "Issued");
    }
}

void displayUsers() {
    printf("\nList of Users:\n");
    for (int i = 0; i < totalUsers; i++) {
        printf("ID: %d | Name: %s | Borrowed Book: %s\n", users[i].userID,
               users[i].name, strlen(users[i].borrowedBookTitle) > 0 ? users[i].borrowedBookTitle : "None");
    }
}

int findBookByTitle(const char *title) {
    for (int i = 0; i < totalBooks; i++) {
        if (strcmp(books[i].title, title) == 0) {
            return i;
        }
    }
    return -1;
}

int findUserByID(int userID) {
    for (int i = 0; i < totalUsers; i++) {
        if (users[i].userID == userID) {
            return i;
        }
    }
    return -1;
}

void expandBooks() {
    booksCapacity += INITIAL_BOOKS_CAPACITY;
    books = realloc(books, booksCapacity * sizeof(Book));
}

void expandUsers() {
    usersCapacity += INITIAL_USERS_CAPACITY;
    users = realloc(users, usersCapacity * sizeof(User));
}

void loadSampleData() {
    booksCapacity = INITIAL_BOOKS_CAPACITY;
    usersCapacity = INITIAL_USERS_CAPACITY;

    books = malloc(booksCapacity * sizeof(Book));
    users = malloc(usersCapacity * sizeof(User));
}

void freeLibrary() {
    free(books);
    free(users);
}