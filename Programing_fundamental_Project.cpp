#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_STUDENTS = 50;
string names[MAX_STUDENTS];
bool attendance[MAX_STUDENTS];
int marks[MAX_STUDENTS][3]; // 0: Maths, 1: Science, 2: English
int studentCount = 0;

void enterNames() {
    cout << "Enter the number of students: ";
    cin >> studentCount;
    if (studentCount > MAX_STUDENTS) {
        cout << "Maximum number of students is " << MAX_STUDENTS << ".\n";
        studentCount = MAX_STUDENTS;
    }

    cin.ignore(); // Clear input buffer
    for (int i = 0; i < studentCount; ++i) {
        cout << "Enter name for student " << i + 1 << ": ";
        getline(cin, names[i]);
    }
}

void markAttendance() {
    for (int i = 0; i < studentCount; ++i) {
        char status;
        cout << "Is " << names[i] << " present? (y/n): ";
        cin >> status;
        attendance[i] = (status == 'y' || status == 'Y');
    }
}

void inputMarks() {
    for (int i = 0; i < studentCount; ++i) {
        cout << "Enter marks for " << names[i] << ":\n";
        cout << "Maths: ";
        cin >> marks[i][0];
        cout << "Science: ";
        cin >> marks[i][1];
        cout << "English: ";
        cin >> marks[i][2];
    }
}

void displayAttendance() {
    cout << left << setw(15) << "Name" 
         << setw(10) << "Attendance" << "\n";
    cout << string(25, '-') << "\n";

    for (int i = 0; i < studentCount; ++i) {
        cout << left << setw(15) << names[i]
             << setw(10) << (attendance[i] ? "Present" : "Absent")
             << "\n";
    }
}

void displayMarks() {
    cout << left << setw(15) << "Name" 
         << setw(8) << "Maths" 
         << setw(8) << "Science" 
         << setw(8) << "English" << "\n";
    cout << string(40, '-') << "\n";

    for (int i = 0; i < studentCount; ++i) {
        cout << left << setw(15) << names[i]
             << setw(8) << (marks[i][0] != -1 ? to_string(marks[i][0]) : "NA")
             << setw(8) << (marks[i][1] != -1 ? to_string(marks[i][1]) : "NA")
             << setw(8) << (marks[i][2] != -1 ? to_string(marks[i][2]) : "NA")
             << "\n";
    }
}

int main() {
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        attendance[i] = false;
        for (int j = 0; j < 3; ++j) {
            marks[i][j] = -1; // -1 indicates marks not entered yet
        }
    }

    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Enter student names\n";
        cout << "2. Mark attendance\n";
        cout << "3. Input marks\n";
        cout << "4. Display attendance\n";
        cout << "5. Display marks\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            enterNames();
            break;
        case 2:
            markAttendance();
            break;
        case 3:
            inputMarks();
            break;
        case 4:
            displayAttendance();
            break;
        case 5:
            displayMarks();
            break;
        case 6:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
	
    return 0;
}
