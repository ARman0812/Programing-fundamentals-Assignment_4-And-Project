#include <iostream>

#include <fstream>
        #include <string>
                   using namespace std;



void add_patient() {
             int id, age, room;
           string name, disease;

  
      cout << "Enter Patient ID: ";
 
    cin >> id;

    cout << "Enter Patient Name: ";

    
             cin.ignore();
                                      getline(cin, name);

                   cout << "Enter Patient Age: ";
    cin >> age;

    cout << "Enter Disease: ";
    
               cin.ignore();
    getline(cin, disease);

             cout << "Enter Room Number: ";
    cin >> room;


    ofstream file("patients.txt", ios::app);
   
     file << id << " " << name << " " << age << " " << disease << " " << room << endl;
    file.close();

    cout << "Patient added successfully!\n";
}


void display_patients() {
    ifstream file("patients.txt");
    if (!file) {
        cout << "No patients found.\n";
        return;
    }

    cout << "\nList of Patients:\n";
    cout << "ID Name Age Disease Room\n";

    int id, age, room;
    string name, disease;

    while (file >> id >> name >> age >> disease >> room) {
        cout << id << " " << name << " " << age << " " << disease << " " << room << endl;
    }

    file.close();
}

// Function to search for a patient by ID
void search_patient() {
                  int search_id;
              cout << "Enter Patient ID to search: ";
    cin >> search_id;

                      ifstream file("patients.txt");
                if (!file) {
                       cout << "No patients found.\n";
    
                    
                    return;
    }

                                       int id, age, room;
                 string name, disease;
    bool found = false;

    while (file >> id >> name >> age >> disease >> room) {
                       if (id == search_id) {
            cout << "\nPatient Found:\n";
      
            
            cout << "ID: " << id << "\nName: " << name << "\nAge: " << age << "\nDisease: " << disease << "\nRoom: " << room << endl;
                                         found = true;
            break;
    
        
        }
  
    
    }

             if (!found) {

        
        cout << "Patient not found.\n";
    }

    file.close();
}

// Function to delete a patient by ID
void delete_patient() {
    int delete_id;
         cout << "Enter Patient ID to delete: ";
   
     cin >> delete_id;


    
    ifstream file("patients.txt");
    ofstream temp("temp.txt");

    if (!file) {
                           cout << "No patients found.\n";
                     return;
    }

         int id, age, room;
              string name, disease;
                  bool found = false;

    while (file >> id >> name >> age >> disease >> room) {
        if (id == delete_id) {
            found = true;
        } else {
            temp << id << " " << name << " " << age << " " << disease << " " << room << endl;
        }
    }

    file.close();
    temp.close();

    if (found) {
                                                  remove("patients.txt");
                                           rename("temp.txt", "patients.txt");
                                             cout << "Patient deleted successfully!\n";
    } else {
        cout << "Patient not found.\n";
    }
}

int main() {
    int choice;

    do {
                cout << "\nHospital Management System\n";
                                  cout << "1. Add Patient\n";
                             
        
        cout << "2. Display All Patients\n";
  
        cout << "3. Search Patient by ID\n";
                                              cout << "4. Delete Patient by ID\n";
                         cout << "5. Exit\n";
        cout << "Enter your choice: ";
 
        cin >> choice;

        if (choice == 1) {
            add_patient();
      
        } else if (choice == 2) {
            display_patients();
        } else if (choice == 3) {
              search_patient();
  
  
   
         } else if (choice == 4) {
                                   } else if (choice == 5) {
  
            cout << "Exiting program. Goodbye!\n";
        } else {
   
            cout << "Invalid choice. Please try again.\n";
               }
           
            } while (choice != 5);

    return 0;
}
