#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Song structure to store song data
typedef struct Song {
    char title[100];
    char artist[100];
    char genre[50];
    char mood[50];      // Mood tag (e.g., happy, sad, energetic)
    int popularity;     // Popularity score (can be like number of listens or likes)
    struct Song* next;  // Pointer to next song in the playlist (linked list)
} Song;

// Mood BST Node to store moods
typedef struct MoodNode {
    char mood[50];      // Mood type (e.g., happy, sad)
    Song* songs;       // Linked list of songs for that mood
    struct MoodNode* left;
    struct MoodNode* right;
} MoodNode;

// Function to normalize mood to lowercase
void normalizeMood(char* mood) {
    for (int i = 0; mood[i]; i++) {
        mood[i] = tolower(mood[i]);  // Convert to lowercase for uniform comparison
    }
}

// Function to create a new song
Song* createSong(const char* title, const char* artist, const char* genre, const char* mood, int popularity) {
    Song* new_song = (Song*)malloc(sizeof(Song));
    strcpy(new_song->title, title);
    strcpy(new_song->artist, artist);
    strcpy(new_song->genre, genre);
    strcpy(new_song->mood, mood);
    new_song->popularity = popularity;
    new_song->next = NULL;
    return new_song;
}

// Add song to a specific mood list in the BST
void addSongToMood(MoodNode** root, Song* new_song, const char* mood) {
    if (*root == NULL) {
        *root = (MoodNode*)malloc(sizeof(MoodNode));
        strcpy((*root)->mood, mood);
        (*root)->songs = new_song;
        (*root)->left = (*root)->right = NULL;
    } else if (strcmp(mood, (*root)->mood) < 0) {
        addSongToMood(&(*root)->left, new_song, mood);
    } else if (strcmp(mood, (*root)->mood) > 0) {
        addSongToMood(&(*root)->right, new_song, mood);
    } else {
        new_song->next = (*root)->songs;  // Add song to the existing mood list
        (*root)->songs = new_song;
    }
}

// Function to display songs in a specific mood
void displayMoodSongs(MoodNode* root, const char* mood) {
    if (root == NULL) {
        printf("Mood not found.\n");
        return;
    }
    
    if (strcmp(mood, root->mood) < 0) {
        displayMoodSongs(root->left, mood);
    } else if (strcmp(mood, root->mood) > 0) {
        displayMoodSongs(root->right, mood);
    } else {
        printf("Songs for mood '%s':\n", mood);
        Song* temp = root->songs;
        while (temp != NULL) {
            printf("Title: %s | Artist: %s | Genre: %s | Popularity: %d\n", 
                   temp->title, temp->artist, temp->genre, temp->popularity);
            temp = temp->next;
        }
    }
}

// Function to clear the input buffer (flush the newline character)
void clearInputBuffer() {
    while (getchar() != '\n');  // Discard remaining characters in the buffer until newline
}

// Display the menu options for user interaction
void displayMenu() {
    printf("\nMusic Playlist Generator\n");
    printf("1. Add Song\n");
    printf("2. Display Playlist by Mood\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

// Main function
int main() {
    MoodNode* mood_tree = NULL;  // The root of the BST to store songs by mood

    while (1) {
        int choice;
        displayMenu();
        scanf("%d", &choice);

        // Clear the input buffer to prevent leftover newline from affecting subsequent input
        clearInputBuffer();

        switch (choice) {
            case 1: {
                char title[100], artist[100], genre[50], mood[50];
                int popularity;

                // Input song details
                printf("Enter song title: ");
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = 0;  // Remove the newline character

                printf("Enter artist name: ");
                fgets(artist, 100, stdin);
                artist[strcspn(artist, "\n")] = 0;  // Remove the newline character

                printf("Enter genre: ");
                fgets(genre, 50, stdin);
                genre[strcspn(genre, "\n")] = 0;  // Remove the newline character

                printf("Enter mood (e.g., happy, sad, energetic): ");
                fgets(mood, 50, stdin);
                mood[strcspn(mood, "\n")] = 0;  // Remove the newline character

                normalizeMood(mood);  // Normalize the mood to lowercase

                printf("Enter popularity score (e.g., 1-100): ");
                scanf("%d", &popularity);

                // Create a new song and add it to the BST under the appropriate mood
                Song* new_song = createSong(title, artist, genre, mood, popularity);
                addSongToMood(&mood_tree, new_song, mood);

                break;
            }
            case 2: {
                char mood[50];
                printf("Enter mood to search for (e.g., happy, sad, energetic): ");
                fgets(mood, 50, stdin);
                mood[strcspn(mood, "\n")] = 0;  // Remove the newline character

                normalizeMood(mood);  // Normalize the mood to lowercase
                displayMoodSongs(mood_tree, mood);  // Display songs for the selected mood
                break;
            }
            case 3:
                printf("Exiting the music playlist system.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
