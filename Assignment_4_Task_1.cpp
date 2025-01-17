#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Library {

           int book_id;
    string title;

        string author;

    int quantity;


};

void addNewBook() {
    Library book;
    cout << "Enter Book ID: ";
    cin >> book.book_id;
    cin.ignore();


    cout << "Enter Book Title: ";
    getline(cin, book.title);
    cout << "Enter Author: ";
    cin >> book.author;



    cout << "Enter Quantity: ";
    cin >> book.quantity;


    ifstream file("library.txt");
    string line;
    while (getline(file, line)) {

int pos;
        int id = stoi(line.substr(0, pos));
        if (id == book.book_id) {

            cout << "Error: Book ID already exists!" << endl;
            file.close();
            return;


        }


    }
    file.close();


    ofstream outfile("library.txt", ios::app);

    outfile << book.book_id << "," << book.title << "," << book.author << "," << book.quantity << endl;
    outfile.close();


    cout << "Book added successfully!" << endl;
}

void displayBooks() {
    ifstream file("library.txt");
    if 
    (!file) {

        cout << "Error: Could not open file." << endl;
        return;
    }

    cout << "\nAvailable Books:\n";
    cout << "---------------------------------------------------------------\n";
          cout << "ID\tTitle\t\tAuthor\t\tQty\n";
               cout << "-------------------------------------------------------------  --\n";

    string line;
    while
    (getline(file, line)) {
        size_t pos = 0;
        string id, title, author, quantity;
        pos = line.find(',');
        id = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        title = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        author = line.substr(0, pos);
        line.erase(0, pos + 1);

        quantity = line;

        cout << id << "\t" << title << "\t\t" << author << "\t\t" << quantity << endl;
    }
    cout << "---------------------------------------------------------------\n";

    file.close();
}

void searchBookByID(int id) {

          ifstream file("library.txt");
    if (!file) 
    {

               cout << "Error: Could not open file." << endl;
        return;
    }

    string line;
                bool found = false;
    while (getline(file, line)) {
        size_t pos = line.find(',');
                 int book_id = stoi(line.substr(0, pos));
        if (book_id == id) {
            cout << "Book Found: " << line << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Book not found." << endl;
    }

    file.close();
}

       void searchBooksByTitle(const string& keyword) {
            ifstream file("library.txt");
    if (!file) {
        cout << "Error: Could not open file." << endl;
        return;
    }

               string line;
    bool found = false;
          while (getline(file, line)) {
               if (line.find(keyword) != string::npos) {
            cout << "Book Found: " << line << endl;
            found = true;

        }

    }


    if (!found) {
        cout << "Book not found." << endl;
    }

            file.close();
}

                void preloadBooks() {
    ofstream file("library.txt");
               if (!file) {
        cout << "Error: Could not open file." << endl;
                  return;
                }



    file << "101,The Great Gatsby,F. Scott Fitzgerald,5\n";

    file << "102,1984,George Orwell,8\n";
    file << "103,To Kill a Mockingbird,Harper Lee,10\n";

    file << "104,The Catcher in the Rye,J.D. Salinger,7\n";
    file << "105,Pride and Prejudice,Jane Austen,4\n";

    file.close();
    cout << "Library preloaded with sample books!" << endl;
}
void displaymenu (){
            cout << "\nLibrary Management System";

        cout << "\n1. Add New Book";

        cout << "\n2. Display All Books";

        cout << "\n3. Search Book by ID";

        cout << "\n4. Search Book by Title";

        cout << "\n5. Exit";

}

int main() {
    preloadBooks();
    int choice;
    do {
        displaymenu ();
        cout << "\nEnter your choice: ";

        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addNewBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3: {
                int id;
                cout << "Enter Book ID: ";
                cin >> id;
                searchBookByID(id);
                break;
            }
            case 4: {
                string keyword;


                cout << "Enter Title or Keyword: ";
                cin.ignore();
                getline(cin, keyword);

                searchBooksByTitle(keyword);
                break;
            }
            case 5:

                cout << "Exiting the program.\n";
                break;
            default:

                cout << "Invalid choice, please try again.\n";
            }

                 }


    while (choice != 5);

    return 0;
}