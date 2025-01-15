#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct patient {
    int patient_id;
    string name;
    int age;
    string disease;
    int room_number;
};

void clr_input() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool id(int id) {
    return id > 0;
}

bool age(int age) {
    return age >= 0 && age <= 150;
}

bool room_no(int room) {
    return room > 0;
}

void add_patient() {
    patient pat;
    cout << "Enter Patient ID (positive integer): ";
    cin >> pat.patient_id;
    if (!id(pat.patient_id)) {
        cout << "Invalid Patient ID! It must be a positive integer.\n";
        clr_input();
        return;
    }

    cin.ignore();
    cout << "Enter Patient Name: ";
    getline(cin, pat.name);

    cout << "Enter Patient Age (0-150): ";
    cin >> pat.age;
    if (!age(pat.age)) {
        cout << "Invalid Age! Please enter an age between 0 and 150.\n";
        clr_input();
        return;
    }

    cin.ignore();
    cout << "Enter Disease: ";
    getline(cin, pat.disease);

    cout << "Enter Room Number (positive integer): ";
    cin >> pat.room_number;
    if (!room_no(pat.room_number)) {
        cout << "Invalid Room Number! It must be a positive integer.\n";
        clr_input();
        return;
    }

    ifstream file("patients.txt");
    string line;
    while (getline(file, line)) {
        size_t pos = line.find(',');
        int id = stoi(line.substr(0, pos));
        if (id == pat.patient_id) {
            cout << "Error: Patient ID already exists!" << endl;
            file.close();
            clr_input();
            return;
        }
    }
    file.close();

    ofstream outfile("patients.txt", ios::app);
    outfile << pat.patient_id << "," << pat.name << "," << pat.age << "," << pat.disease << "," << pat.room_number << endl;
    outfile.close();
    cout << "Patient added successfully!" << endl;
}

void display_patients() {
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

void search_patient_by_id(int id) {
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

void delete_patient_by_id(int id) {
    ifstream file("patients.txt");
    if (!file) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string line;
    bool found = false;
    ofstream temp_file("temp.txt");
    while (getline(file, line)) {
        size_t pos = line.find(',');
        int patient_id = stoi(line.substr(0, pos));
        if (patient_id != id) {
            temp_file << line << endl;
        } else {
            found = true;
        }
    }

    file.close();
    temp_file.close();

    if (found) {
        remove("patients.txt");
        rename("temp.txt", "patients.txt");
        cout << "Patient with ID " << id << " has been deleted.\n";
    } else {
        cout << "Patient not found.\n";
    }
}

void update_patient_details(int id) {
    ifstream file("patients.txt");
    if (!file) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string line;
    bool found = false;
    ofstream temp_file("temp.txt");

    while (getline(file, line)) {
        size_t pos = line.find(',');
        int patient_id = stoi(line.substr(0, pos));
        if (patient_id == id) {
            found = true;

            patient updated_pat;
            cout << "Patient found. Updating details...\n";
            updated_pat.patient_id = id;

            cin.ignore();
            cout << "Enter new Name: ";
            getline(cin, updated_pat.name);

            cout << "Enter new Age: ";
            cin >> updated_pat.age;
            cin.ignore();

            cout << "Enter new Disease: ";
            getline(cin, updated_pat.disease);

            cout << "Enter new Room Number: ";
            cin >> updated_pat.room_number;

            temp_file << updated_pat.patient_id << "," << updated_pat.name << "," << updated_pat.age << "," << updated_pat.disease << "," << updated_pat.room_number << endl;
        } else {
            temp_file << line << endl;
        }
    }

    file.close();
    temp_file.close();

    if (found) {
        remove("patients.txt");
        rename("temp.txt", "patients.txt");
        cout << "Patient details updated successfully.\n";
    } else {
        cout << "Patient not found.\n";
    }
}

void preload_patients() {
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
    preload_patients();
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
        clr_input();

        switch (choice) {
            case 1:
                add_patient();
                break;
            case 2:
                display_patients();
                break;
            case 3: {
                int id;
                cout << "Enter Patient ID: ";
                cin >> id;
                search_patient_by_id(id);
                break;
            }
            case 4: {
                int id;
                cout << "Enter Patient ID to delete: ";
                cin >> id;
                delete_patient_by_id(id);
                break;
            }
            case 5: {
                int id;
                cout << "Enter Patient ID to update: ";
                cin >> id;
                update_patient_details(id);
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