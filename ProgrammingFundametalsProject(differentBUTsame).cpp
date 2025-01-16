#include <iostream> 
//A library for Input and outPut
#include <iomanip>
//A library was specifically added cause I used set.w in display attendance and displaymarks Function this was learned from my brother and then used.
#include <fstream>
//a library was added for file Handling as taught in class
#include <string>
//a library entered so that names can be hand
using namespace std;

struct Student {
    //Structure was used so that we don't have to make so many arrays and add different variables again and again .
    string name;
    bool attendance;
    int marks[3]; // 0: Maths, 1: Science, 2: English
};


const int MAX_STUDENTS = 50;
//only Max students were capital used cause they are limited the user can adjust the limits of students or can remove the limits 
Student students[MAX_STUDENTS];
int studentCount = 0;

void saveToFile() {
    // This function was added to save all the data entered by used into a file it was Complicated so the help was taken from different sources
    ofstream outFile("studentdatabase.txt");
    if (!outFile) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    outFile << studentCount << endl;
    for (int i = 0; i < studentCount; ++i) {
        outFile << students[i].name << endl;
        outFile << students[i].attendance << endl;
        outFile << students[i].marks[0] << " " << students[i].marks[1] << " " << students[i].marks[2] << endl;
    }

    outFile.close();
    cout << "Data saved to file successfully!" << endl;
}

void loadFromFile() {
    //load file function was an idea taken from chat gpt and implemented in parts after taking different ideas from chat gpt and my ideas it was a combined Function that checks and shows all the previous data so that it can be used by any user anytime
    
    ifstream inFile("studentdatabase.txt");
    if (!inFile) {
        cout << "Error opening file for reading! Starting fresh." << endl;
        return;
    }

    inFile >> studentCount;
    inFile.ignore(); // Ignore newline character after studentCount
    for (int i = 0; i < studentCount; ++i) {
        getline(inFile, students[i].name);
        inFile >> students[i].attendance;
        inFile >> students[i].marks[0] >> students[i].marks[1] >> students[i].marks[2];
        inFile.ignore(); // Ignore newline character
    }

    inFile.close();
    cout << "Data loaded from file successfully!" << endl;
}

void enterNames() {
    //a function to enter names this is very important function that is added and must be used first cause all other functions depends on this function
    cout << "Enter the number of students: ";
    cin >> studentCount;
    if (studentCount > MAX_STUDENTS) {
        cout << "Maximum number of students is " << MAX_STUDENTS << ".\n";
        studentCount = MAX_STUDENTS;
    }
//cin.ignore was specifically added so that it doesn't cause problem in some compilers
    cin.ignore(); // Clear input buffer
    for (int i = 0; i < studentCount; ++i) {
        cout << "Enter name for student " << i + 1 << ": ";
        getline(cin, students[i].name);
        students[i].attendance = false;
        for (int j = 0; j < 3; ++j) {
            students[i].marks[j] = -1; // Initialize marks to -1
        }
    }
}

void markAttendance() {
    //a function created to mark attendance of the names Entered by the user and the attendance can only be marked in two types Present (y) and Absents (n) the leave and short leave were not added for now but user can add them in the same way as the 2 are applied
    for (int i = 0; i < studentCount; ++i) {
        char status;
        cout << "Is " << students[i].name << " present? (y/n): ";
        cin >> status;
        students[i].attendance = (status == 'y' || status == 'Y');
    }
}

void inputMarks() {
    //A function created to enter marks I added 3 subjects but new user can change them accordingly and add more subjects I added three subjects to just add something
    for (int i = 0; i < studentCount; ++i) {
        cout << "Enter marks for " << students[i].name << ":\n";
        cout << "Maths: ";
        cin >> students[i].marks[0];
        cout << "Science: ";
        cin >> students[i].marks[1];
        cout << "English: ";
        cin >> students[i].marks[2];
    }
}

void displayAttendance() {
    //a function created to display the marked attendance by the user. REMEMBER: attendance can not be marked before entering names as the file is empty
    cout << left << setw(15) << "Name" 
         << setw(10) << "Attendance" << "\n";
    cout << string(25, '-') << "\n";

    for (int i = 0; i < studentCount; ++i) {
        cout << left << setw(15) << students[i].name
             << setw(10) << (students[i].attendance ? "Present" : "Absent")
             << "\n";
    }
}

void displayMarks() {
    //a function created to displaymarks present in the file or the marks entered by the user
    cout << left << setw(15) << "Name" 
         << setw(8) << "Maths" 
         << setw(8) << "Science" 
         << setw(8) << "English" << "\n";
    cout << string(40, '-') << "\n";

    for (int i = 0; i < studentCount; ++i) {
        cout << left << setw(15) << students[i].name
             << setw(8) << (students[i].marks[0] != -1 ? to_string(students[i].marks[0]) : "NA")
             << setw(8) << (students[i].marks[1] != -1 ? to_string(students[i].marks[1]) : "NA")
             << setw(8) << (students[i].marks[2] != -1 ? to_string(students[i].marks[2]) : "NA")
             << "\n";
    }
}

void displaymenu(){
	 //an extra Function created so that menu can be loaded again and again and can be adjusted by the new user 
	 cout << "\n\033[1;4;36mWelcome to The Student Data Base by Muhammad Abdullah\033[0m\n";
        cout << "1. Enter student names\n";
        cout << "2. Mark attendance\n";
        cout << "3. Input marks\n";
        cout << "4. Display attendance\n";
        cout << "5. Display marks\n";
        cout << "6. Save and Exit\n";
        
        // Only in the first line ANSI codes were used I usually use them cause I like the way they change code and make the output more beautiful but I only added them once here because not all compilers can run ANSI codes
}
int main() {
    loadFromFile(); //If you are a new user kindly create a file with studentsatabase.txt and use it it'll will help you automatically bring your data in the Program
    int choice;

//used do-while loop instead of while loop so that it runs at least once for the first time and then it stops.
    do {
        displaymenu();
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
            saveToFile();
            cout << "Exiting program. Thanks for Using \n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}