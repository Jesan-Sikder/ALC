#include <stdio.h>
#include <string.h>


#define MARA 19.5
#define CREDITS 3.00
#define LAB_CREDITS 1.5


struct Subject {
    char name[50];
    float marks;
    float grade_point;
    float credits;
};


float calculate_grade_point(float marks) {
    if (marks > 79.00) {
        return 4.00;
    } else if (marks >= 75 && marks <= 79) {
        return 3.75;
    } else if (marks >= 70 && marks < 75) {
        return 3.50;
    } else if (marks >= 65 && marks < 70) {
        return 3.25;
    } else if (marks >= 60 && marks < 65) {
        return 3.00;
    } else if (marks >= 55 && marks < 60) {
        return 2.75;
    } else if (marks >= 50 && marks < 55) {
        return 2.50;
    } else if (marks >= 45 && marks < 50) {
        return 2.25;
    } else if (marks >= 40 && marks < 45) {
        return 2.00;
    } else {
        return 0.00;
    }
}


void input_subject_data(struct Subject *subject) {
    printf("Enter marks for '%s': ", subject->name);
    scanf("%f", &subject->marks);
    subject->grade_point = calculate_grade_point(subject->marks);
}


void display_subject_info(struct Subject subject) {
    printf("Subject: %-25s Marks: %-5.2f Grade Points: %-5.2f Credits: %-5.2f\n",
           subject.name, subject.marks, subject.grade_point, subject.credits);
}


float calculate_sgpa(struct Subject subjects[], int num_subjects) {
    float total_points = 0.0;
    float total_credits = 0.0;

    for (int i = 0; i < num_subjects; i++) {
        total_points += subjects[i].grade_point * subjects[i].credits;
        total_credits += subjects[i].credits;
    }

    return total_points / total_credits;
}

int main() {
    
    struct Subject subjects[8];  

    
    strcpy(subjects[0].name, "English");
    subjects[0].credits = CREDITS;

    strcpy(subjects[1].name, "Data Structure");
    subjects[1].credits = CREDITS;

    strcpy(subjects[2].name, "Data Structure Lab");
    subjects[2].credits = LAB_CREDITS;

    strcpy(subjects[3].name, "EC");
    subjects[3].credits = CREDITS;

    strcpy(subjects[4].name, "EC Lab");
    subjects[4].credits = LAB_CREDITS;

    strcpy(subjects[5].name, "Physics");
    subjects[5].credits = CREDITS;

    strcpy(subjects[6].name, "Physics Lab");
    subjects[6].credits = LAB_CREDITS;

    strcpy(subjects[7].name, "Mathematics-II");
    subjects[7].credits = CREDITS;

    
    printf("\n******************************* SGPA Calculator ****************************\n\n");
    printf("Please enter your marks as the program asks for...\n\n");

    
    for (int i = 0; i < 8; i++) {  
        input_subject_data(&subjects[i]);
    }

    
    printf("\n***************************** Subject Information ****************************\n");
    for (int i = 0; i < 8; i++) {  
        display_subject_info(subjects[i]);
    }

    
    float sgpa = calculate_sgpa(subjects, 8);  
    printf("\n********************************** SGPA: %.2f **********************************\n\n", sgpa);

    return 0;
}
//code ok ase