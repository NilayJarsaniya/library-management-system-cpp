#include <iostream>
#include <fstream>
using namespace std;

class Book {
public:
    int id;
    char title[50];
    char author[50];
    int issued; // 0 = available, 1 = issued

    void input() {
        cout << "Enter Book ID: ";
        cin >> id;
        cout << "Enter Title: ";
        cin >> title;
        cout << "Enter Author: ";
        cin >> author;
        issued = 0;
    }

    void display() {
        cout << "ID: " << id 
             << " | Title: " << title 
             << " | Author: " << author 
             << " | Status: " << (issued ? "Issued" : "Available") 
             << endl;
    }
};

// Add Book
void addBook() {
    Book b;
    ofstream file("books.dat", ios::binary | ios::app);

    b.input();
    file.write((char*)&b, sizeof(b));

    file.close();
    cout << "Book Added!\n";
}

// Display Books
void displayBooks() {
    Book b;
    ifstream file("books.dat", ios::binary);

    while(file.read((char*)&b, sizeof(b))) {
        b.display();
    }

    file.close();
}

// Search Book
void searchBook() {
    Book b;
    int id, found = 0;

    cout << "Enter Book ID to search: ";
    cin >> id;

    ifstream file("books.dat", ios::binary);

    while(file.read((char*)&b, sizeof(b))) {
        if(b.id == id) {
            b.display();
            found = 1;
        }
    }

    if(!found) cout << "Book not found\n";

    file.close();
}

// Issue Book
void issueBook() {
    Book b;
    int id;

    cout << "Enter Book ID to issue: ";
    cin >> id;

    fstream file("books.dat", ios::binary | ios::in | ios::out);

    while(file.read((char*)&b, sizeof(b))) {
        if(b.id == id && b.issued == 0) {
            b.issued = 1;

            file.seekp(-sizeof(b), ios::cur);
            file.write((char*)&b, sizeof(b));

            cout << "Book Issued!\n";
            return;
        }
    }

    cout << "Book not available\n";
    file.close();
}

// Return Book
void returnBook() {
    Book b;
    int id;

    cout << "Enter Book ID to return: ";
    cin >> id;

    fstream file("books.dat", ios::binary | ios::in | ios::out);

    while(file.read((char*)&b, sizeof(b))) {
        if(b.id == id && b.issued == 1) {
            b.issued = 0;

            file.seekp(-sizeof(b), ios::cur);
            file.write((char*)&b, sizeof(b));

            cout << "Book Returned!\n";
            return;
        }
    }

    cout << "Invalid operation\n";
    file.close();
}

// Main
int main() {
    int choice;

    do {
        cout << "\n1. Add Book";
        cout << "\n2. Display Books";
        cout << "\n3. Search Book";
        cout << "\n4. Issue Book";
        cout << "\n5. Return Book";
        cout << "\n6. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
        }

    } while(choice != 6);

    return 0;
}
