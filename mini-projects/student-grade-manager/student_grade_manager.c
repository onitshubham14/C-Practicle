#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 50
#define NUM_SUBJECTS 5

// Structure to store subject names
const char *SUBJECT_NAMES[NUM_SUBJECTS] = {
    "Mathematics",
    "Physics",
    "Chemistry",
    "English",
    "Computer Science"
};

// Structure to hold student details
typedef struct {
    int rollNumber;
    char name[50];
    float marks[NUM_SUBJECTS];
    float total;
    float percentage;
    char grade;
} Student;

// Function declarations
char calculateGrade(float percentage);
void inputStudentData(Student *s);
void displayScorecard(const Student *s);
void displayAllScorecards(const Student students[], int count);
void displayClassStatistics(const Student students[], int count);

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    printf("===================================================\n");
    printf("   WELCOME TO STUDENT GRADE MANAGEMENT SYSTEM     \n");
    printf("===================================================\n");

    while (1) {
        printf("\n--- MAIN MENU ---\n");
        printf("1. Add Student Record\n");
        printf("2. Display All Student Scorecards\n");
        printf("3. View Class Summary & Statistics\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear buffer
            continue;
        }

        switch (choice) {
            case 1:
                if (count >= MAX_STUDENTS) {
                    printf("Limit reached! Cannot add more students.\n");
                } else {
                    printf("\n--- Enter Details for Student %d ---\n", count + 1);
                    inputStudentData(&students[count]);
                    count++;
                    printf("Student record added successfully!\n");
                }
                break;

            case 2:
                if (count == 0) {
                    printf("\nNo student records available to display.\n");
                } else {
                    displayAllScorecards(students, count);
                }
                break;

            case 3:
                if (count == 0) {
                    printf("\nNo student records available for statistics.\n");
                } else {
                    displayClassStatistics(students, count);
                }
                break;

            case 4:
                printf("\nExiting Student Grade Management System. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice! Please choose an option between 1 and 4.\n");
        }
    }

    return 0;
}

// Function to calculate letter grade based on percentage
char calculateGrade(float percentage) {
    if (percentage >= 90.0) return 'A';
    if (percentage >= 80.0) return 'B';
    if (percentage >= 70.0) return 'C';
    if (percentage >= 60.0) return 'D';
    return 'F';
}

// Function to input data for a single student
void inputStudentData(Student *s) {
    int i;
    s->total = 0.0;

    printf("Enter Roll Number: ");
    scanf("%d", &s->rollNumber);
    
    // Clear newline character left in input buffer
    getchar();

    printf("Enter Student Name: ");
    fgets(s->name, sizeof(s->name), stdin);
    s->name[strcspn(s->name, "\n")] = '\0'; // Remove trailing newline

    printf("\nEnter marks obtained out of 100 for each subject:\n");
    for (i = 0; i < NUM_SUBJECTS; i++) {
        do {
            printf("  %-18s: ", SUBJECT_NAMES[i]);
            if (scanf("%f", &s->marks[i]) != 1 || s->marks[i] < 0 || s->marks[i] > 100) {
                printf("  [Error] Please enter valid marks between 0 and 100.\n");
                while (getchar() != '\n'); // Clear buffer
            } else {
                break;
            }
        } while (1);
        
        s->total += s->marks[i];
    }

    s->percentage = s->total / (float)NUM_SUBJECTS;
    s->grade = calculateGrade(s->percentage);
}

// Function to display scorecard for one student
void displayScorecard(const Student *s) {
    int i;
    printf("\n---------------------------------------------------\n");
    printf("              STUDENT SCORECARD                    \n");
    printf("---------------------------------------------------\n");
    printf(" Roll Number : %d\n", s->rollNumber);
    printf(" Name        : %s\n", s->name);
    printf("---------------------------------------------------\n");
    printf(" Subject               Marks (Out of 100)\n");
    printf("---------------------------------------------------\n");
    for (i = 0; i < NUM_SUBJECTS; i++) {
        printf(" %-20s : %6.2f\n", SUBJECT_NAMES[i], s->marks[i]);
    }
    printf("---------------------------------------------------\n");
    printf(" Total Marks           : %6.2f / 500.00\n", s->total);
    printf(" Percentage            : %6.2f%%\n", s->percentage);
    printf(" Final Grade           : %c\n", s->grade);
    printf("---------------------------------------------------\n");
}

// Function to display all student scorecards
void displayAllScorecards(const Student students[], int count) {
    int i;
    printf("\n===================================================\n");
    printf("               ALL STUDENT RECORDS                 \n");
    printf("===================================================\n");
    for (i = 0; i < count; i++) {
        displayScorecard(&students[i]);
    }
}

// Function to display class statistics
void displayClassStatistics(const Student students[], int count) {
    int i;
    float totalClassPercentage = 0.0;
    float highestPercentage = students[0].percentage;
    int topStudentIndex = 0;

    for (i = 0; i < count; i++) {
        totalClassPercentage += students[i].percentage;
        if (students[i].percentage > highestPercentage) {
            highestPercentage = students[i].percentage;
            topStudentIndex = i;
        }
    }

    printf("\n===================================================\n");
    printf("               CLASS SUMMARY & STATS               \n");
    printf("===================================================\n");
    printf(" Total Students Recorded  : %d\n", count);
    printf(" Class Average Percentage  : %.2f%%\n", totalClassPercentage / count);
    printf(" Top Performer             : %s (Roll No: %d)\n", students[topStudentIndex].name, students[topStudentIndex].rollNumber);
    printf(" Highest Percentage        : %.2f%% (Grade %c)\n", students[topStudentIndex].percentage, students[topStudentIndex].grade);
    printf("===================================================\n");
}
