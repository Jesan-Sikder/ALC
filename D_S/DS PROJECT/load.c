#include <stdio.h>
#include <stdlib.h>
#include <windows.h>  // For Sleep() and system("cls")

void loadingAnimation() {
    char* dots[] = {".", "..", "...", "....", "....."};
    int i = 0;

    // Loop for a certain number of iterations to simulate loading
    for (int j = 0; j < 5; j++) {
        printf("Loading Hotel Management System");
        
        // Print one of the dot animations
        printf("%s", dots[i]);
        fflush(stdout);  // Ensure the output is displayed immediately

        Sleep(500);  // Sleep for half a second (500 milliseconds)

        // Clear the screen on Windows
        system("cls");
        
        // Update dot sequence
        i = (i + 1) % 5;
    }

    // Finish the loading
    printf("\nLoading Complete!\n");
}

int main() {
    // Print a welcome message
    printf("Welcome to the Hotel Management System\n");

    // Call the loading animation function
    loadingAnimation();

    // You can now proceed with the rest of the system's functionality
    printf("System Ready!\n");

    return 0;
}