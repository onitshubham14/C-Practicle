#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 50
#define NUM_SUBJECTS 5

const char *SUBJECT_NAMES[NUM_SUBJECTS] = {
    "Mathematics",
    "Physics",
    "Chemistry",
    "English",
    "Computer Science"
};

typedef struct {
    int rollNumber;
    char name[50];
    float marks[NUM_SUBJECTS];
    float total;
    float percentage;
    char grade;
} Student;

char calculateGrade(float percentage);
int inputStudentData(Student *s);
void displayScorecard(const Student *s);
void displayAllScorecards(const Student students[], int count);
void displayClassStatistics(const Student students[], int count);

static void clearInputLine(void) {
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

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
            if (feof(stdin)) {
                return 0;
            }

            printf("Invalid input! Please enter a number.\n");
            clearInputLine();
            continue;
        }

        switch (choice) {
            case 1:
                if (count >= MAX_STUDENTS) {
                    printf("Limit reached! Cannot add more students.\n");
                    break;
                }

                printf("\n--- Enter Details for Student %d ---\n", count + 1);

                Student student;
                if (!inputStudentData(&student)) {
                    if (feof(stdin)) {
                        return 0;
                    }

                    printf("Student record was not added.\n");
                    break;
                }

                students[count++] = student;
                printf("Student record added successfully!\n");
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
}

char calculateGrade(float percentage) {
    if (percentage >= 90.0) return 'A';
    if (percentage >= 80.0) return 'B';
    if (percentage >= 70.0) return 'C';
    if (percentage >= 60.0) return 'D';
    return 'F';
}

int inputStudentData(Student *s) {
    int i;

    s->total = 0.0;

    printf("Enter Roll Number: ");
    if (scanf("%d", &s->rollNumber) != 1) {
        if (!feof(stdin)) {
            printf("Invalid roll number.\n");
            clearInputLine();
        }
        return 0;
    }
    clearInputLine();

    printf("Enter Student Name: ");
    if (fgets(s->name, sizeof(s->name), stdin) == NULL) {
        return 0;
    }

    if (strchr(s->name, '\n') == NULL) {
        clearInputLine();
    } else {
        s->name[strcspn(s->name, "\n")] = '\0';
    }

    printf("\nEnter marks obtained out of 100 for each subject:\n");
    for (i = 0; i < NUM_SUBJECTS; i++) {
        do {
            printf("  %-18s: ", SUBJECT_NAMES[i]);

            if (scanf("%f", &s->marks[i]) != 1) {
                if (feof(stdin)) {
                    return 0;
                }

                printf("  [Error] Please enter a numeric mark.\n");
                clearInputLine();
                continue;
            }

            if (s->marks[i] < 0 || s->marks[i] > 100) {
                printf("  [Error] Please enter valid marks between 0 and 100.\n");
                clearInputLine();
                continue;
            }

            clearInputLine();
            break;
        } while (1);

        s->total += s->marks[i];
    }

    s->percentage = s->total / (float)NUM_SUBJECTS;
    s->grade = calculateGrade(s->percentage);
    return 1;
}

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

void displayAllScorecards(const Student students[], int count) {
    int i;

    printf("\n===================================================\n");
    printf("               ALL STUDENT RECORDS                 \n");
    printf("===================================================\n");

    for (i = 0; i < count; i++) {
        displayScorecard(&students[i]);
    }
}

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
    printf(" Top Performer             : %s (Roll No: %d)\n",
           students[topStudentIndex].name,
           students[topStudentIndex].rollNumber);
    printf(" Highest Percentage        : %.2f%% (Grade %c)\n",
           students[topStudentIndex].percentage,
           students[topStudentIndex].grade);
    printf("===================================================\n");
}
