#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Patient {
    int patient_id;
    string name;
    int age;
    string disease;
    int room_number;
};

void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool isValidID(int id) {
    return id > 0;
}

bool isValidAge(int age) {
    return age >= 0 && age <= 150;
}

bool isValidRoomNumber(int room) {
    return room > 0;
}

void addNewPatient() {
    Patient patient;
    cout << "Enter Patient ID (positive integer): ";
    cin >> patient.patient_id;
    if (!isValidID(patient.patient_id)) {
        cout << "Invalid Patient ID! It must be a positive integer.\n";
        clearInputBuffer();
        return;
    }

    cin.ignore();
    cout << "Enter Patient Name: ";
    getline(cin, patient.name);

    cout << "Enter Patient Age (0-150): ";
    cin >> patient.age;
    if (!isValidAge(patient.age)) {
        cout << "Invalid Age! Please enter an age between 0 and 150.\n";
        clearInputBuffer();
        return;
    }

    cin.ignore();
    cout << "Enter Disease: ";
    getline(cin, patient.disease);

    cout << "Enter Room Number (positive integer): ";
    cin >> patient.room_number;
    if (!isValidRoomNumber(patient.room_number)) {
        cout << "Invalid Room Number! It must be a positive integer.\n";
        clearInputBuffer();
        return;
    }

    ifstream file("patients.txt");
    string line;
    while (getline(file, line)) {
        size_t pos = line.find(',');
        int id = stoi(line.substr(0, pos));
        if (id == patient.patient_id) {
            cout << "Error: Patient ID already exists!" << endl;
            file.close();
            clearInputBuffer();
            return;
        }
    }
    file.close();

    ofstream outfile("patients.txt", ios::app);
    outfile << patient.patient_id << "," << patient.name << "," << patient.age << "," << patient.disease << "," << patient.room_number << endl;
    outfile.close();
    cout << "Patient added successfully!" << endl;
}

void displayPatients() {
    ifstream file("patients.txt");
    if (!file) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    cout << "\nAdmitted Patients:\n";
    cout << "---------------------------------------------------------------\n";
    cout << "ID\tName\t\tAge\tDisease\t\tRoom\n";
    cout << "---------------------------------------------------------------\n";

    string line;
    while (getline(file, line)) {
        size_t pos = 0;
        string id, name, age, disease, room;
        pos = line.find(',');
        id = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        name = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        age = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        disease = line.substr(0, pos);
        line.erase(0, pos + 1);

        room = line;

        cout << id << "\t" << name << "\t\t" << age << "\t" << disease << "\t\t" << room << endl;
    }
    cout << "---------------------------------------------------------------\n";

    file.close();
}

void searchPatientByID(int id) {
    ifstream file("patients.txt");
    if (!file) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        size_t pos = line.find(',');
        int patient_id = stoi(line.substr(0, pos));
        if (patient_id == id) {
            cout << "Patient Found: " << line << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Patient not found." << endl;
    }

    file.close();
}

void deletePatientByID(int id) {
    ifstream file("patients.txt");
    if (!file) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string line;
    bool found = false;
    ofstream tempFile("temp.txt");
    while (getline(file, line)) {
        size_t pos = line.find(',');
        int patient_id = stoi(line.substr(0, pos));
        if (patient_id != id) {
            tempFile << line << endl;
        } else {
            found = true;
        }
    }

    file.close();
    tempFile.close();

    if (found) {
        remove("patients.txt");
        rename("temp.txt", "patients.txt");
        cout << "Patient with ID " << id << " has been deleted.\n";
    } else {
        cout << "Patient not found.\n";
    }
}

void updatePatientDetails(int id) {
    ifstream file("patients.txt");
    if (!file) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string line;
    bool found = false;
    ofstream tempFile("temp.txt");

    while (getline(file, line)) {
        size_t pos = line.find(',');
        int patient_id = stoi(line.substr(0, pos));
        if (patient_id == id) {
            found = true;

            Patient updatedPatient;
            cout << "Patient found. Updating details...\n";
            updatedPatient.patient_id = id;

            cin.ignore();
            cout << "Enter new Name: ";
            getline(cin, updatedPatient.name);

            cout << "Enter new Age: ";
            cin >> updatedPatient.age;
            cin.ignore();

            cout << "Enter new Disease: ";
            getline(cin, updatedPatient.disease);

            cout << "Enter new Room Number: ";
            cin >> updatedPatient.room_number;

            tempFile << updatedPatient.patient_id << "," << updatedPatient.name << "," << updatedPatient.age << "," << updatedPatient.disease << "," << updatedPatient.room_number << endl;
        } else {
            tempFile << line << endl;
        }
    }

    file.close();
    tempFile.close();

    if (found) {
        remove("patients.txt");
        rename("temp.txt", "patients.txt");
        cout << "Patient details updated successfully.\n";
    } else {
        cout << "Patient not found.\n";
    }
}

void preloadPatients() {
    ofstream file("patients.txt");
    if (!file) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    file << "101,John Doe,45,Flu,101\n";
    file << "102,Jane Smith,34,Pneumonia,102\n";
    file << "103,Robert Brown,60,Heart Attack,103\n";
    file << "104,Emily Davis,28,Diabetes,104\n";
    file << "105,Michael Johnson,50,Stroke,105\n";

    file.close();
    cout << "Hospital preloaded with sample patients!" << endl;
}

int main() {
    preloadPatients();
    int choice;
    do {
        cout << "\nHospital Patient Management System";
        cout << "\n1. Add New Patient";
        cout << "\n2. Display All Patients";
        cout << "\n3. Search Patient by ID";
        cout << "\n4. Delete Patient by ID";
        cout << "\n5. Update Patient Details";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 1:
                addNewPatient();
                break;
            case 2:
                displayPatients();
                break;
            case 3: {
                int id;
                cout << "Enter Patient ID: ";
                cin >> id;
                searchPatientByID(id);
                break;
            }
            case 4: {
                int id;
                cout << "Enter Patient ID to delete: ";
                cin >> id;
                deletePatientByID(id);
                break;
            }
            case 5: {
                int id;
                cout << "Enter Patient ID to update: ";
                cin >> id;
                updatePatientDetails(id);
                break;
            }
            case 6:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 6);

    return 0;
}