#include <stdio.h>

#define MAX_SUBJECTS 6

const char* SUBJECT_NAMES[MAX_SUBJECTS] = {"DSA", "OS", "TBVP", "COA", "DTM", "APP"};

int main() {
    char name[100], class[10], section[10];
    int numSubjects;

    printf("Enter student name: ");
    scanf("%s", name);
    printf("Enter class: ");
    scanf("%s", class);
    printf("Enter section: ");
    scanf("%s", section);
    printf("Enter number of subjects (max %d): ", MAX_SUBJECTS);
    scanf("%d", &numSubjects);

    if (numSubjects <= 0 || numSubjects > MAX_SUBJECTS) {
        printf("Invalid number of subjects. Please enter a number between 1 and %d.\n", MAX_SUBJECTS);
        return 1;
    }

    int marks[MAX_SUBJECTS], credits[MAX_SUBJECTS], absent[MAX_SUBJECTS], totalMarks[MAX_SUBJECTS];

    for (int i = 0; i < numSubjects; i++) {
        printf("Is the student absent for %s? (1 for absent, 0 for present): ", SUBJECT_NAMES[i]);
        scanf("%d", &absent[i]);

        if (absent[i] != 1 && absent[i] != 0) {
            printf("Invalid input for absence. Please re-enter.\n");
            i--;
            continue;
        }

        if (!absent[i]) {
            printf("Enter total marks for %s: ", SUBJECT_NAMES[i]);
            scanf("%d", &totalMarks[i]);

            if (totalMarks[i] <= 0 || totalMarks[i] > 100) {
                printf("Invalid total marks. Please enter a number between 1 and 100.\n");
                i--;
                continue;
            }

            printf("Enter marks obtained for %s: ", SUBJECT_NAMES[i]);
            scanf("%d", &marks[i]);

            if (marks[i] < 0 || marks[i] > totalMarks[i]) {
                printf("Invalid marks. Please enter a number between 0 and %d.\n", totalMarks[i]);
                continue;
                i--;
            }

            printf("Enter credits for %s: ", SUBJECT_NAMES[i]);
            scanf("%d", &credits[i]);

            if (credits[i] < 0) {
                printf("Invalid credits. Please enter a positive number.\n");
                i--;
                continue;
            }
        } else {
            credits[i] = 0;
        }
    }

    float totalCredits = 0, totalGradePoints = 0;

    for (int i = 0; i < numSubjects; i++) {
        totalCredits += credits[i];
        totalGradePoints += ((float)marks[i] / totalMarks[i]) * credits[i];
    }

    float cgpa = (totalCredits != 0) ? totalGradePoints / totalCredits*10 : 0;

    char file_name[150];
    sprintf(file_name, "%s_%s_%s.txt", name, class, section);

    FILE *file = fopen(file_name, "w");
    if (file != NULL) {
        fprintf(file, "Name: %s\nClass: %s\nSection: %s\n", name, class, section);
        fprintf(file, "Number of subjects: %d\n", numSubjects);
        fprintf(file, "Subjects, Total Marks, Marks Obtained, Credits, Absent\n");
        for (int i = 0; i < numSubjects; i++) {
            fprintf(file, "%s, %d, %d, %d, %s\n", SUBJECT_NAMES[i], totalMarks[i], marks[i], credits[i], (absent[i] == 1) ? "Yes" : "No");
        }
        fprintf(file, "CGPA: %.2f\n", cgpa);
        fclose(file);
        printf("Student information saved to %s\n", file_name);
    } else {
        printf("Error saving file.\n");
    }

    return 0;
}
