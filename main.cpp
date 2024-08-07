#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Contact class definition
class Contact {
private:
    string phoneNumber;
    string name;
    string email;
    string address;

public:
    Contact() {}
    Contact(string phoneNumber, string name, string email = "", string address = "")
        : phoneNumber(phoneNumber), name(name), email(email), address(address) {}

    void setPhoneNumber(const string& phoneNumber) { this->phoneNumber = phoneNumber; }
    void setName(const string& name) { this->name = name; }
    void setEmail(const string& email) { this->email = email; }
    void setAddress(const string& address) { this->address = address; }

    string getPhoneNumber() const { return phoneNumber; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getAddress() const { return address; }

    void display() const {
        cout << "Name: " << name << "\n";
        cout << "Phone Number: " << phoneNumber << "\n";
        if (!email.empty()) {
            cout << "Email: " << email << "\n";
        }
        if (!address.empty()) {
            cout << "Address: " << address << "\n";
        }
        cout << endl;
    }
};

// Phonebook class definition
class Phonebook {
private:
    static const int MAX_CONTACTS = 100; // Maximum number of contacts
    Contact contacts[MAX_CONTACTS];
    int contactCount;

    int findContactIndex(const string& phoneNumber) const;

public:
    Phonebook() : contactCount(0) {
        loadFromFile();
    }
    ~Phonebook() {
        saveToFile();
    }

    void addContact();
    void searchContact() const;
    void showContacts() const;
    void modifyContact();
    void deleteContact();
    void saveToFile() const;
    void loadFromFile();
};

// Phonebook member function implementations
int Phonebook::findContactIndex(const string& phoneNumber) const {
    for (int i = 0; i < contactCount; ++i) {
        if (contacts[i].getPhoneNumber() == phoneNumber) {
            return i;
        }
    }
    return -1;
}

void Phonebook::addContact() {
    if (contactCount >= MAX_CONTACTS) {
        cout << "Phonebook is full. Cannot add more contacts.\n";
        return;
    }

    string phoneNumber, name, email, address;

    cout << "Enter phone number: ";
    cin >> phoneNumber;
    if (findContactIndex(phoneNumber) != -1) {
        cout << "Phone number already exists! Try again...\n";
        return;
    }

    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter email (optional): ";
    getline(cin, email);

    cout << "Enter address (optional): ";
    getline(cin, address);

    contacts[contactCount++] = Contact(phoneNumber, name, email, address);
    cout << "Phone details successfully stored.\n";
}

void Phonebook::searchContact() const {
    string query;
    cout << "Enter phone number or name to search: ";
    cin.ignore();
    getline(cin, query);

    for (int i = 0; i < contactCount; ++i) {
        if (contacts[i].getPhoneNumber() == query || contacts[i].getName() == query) {
            contacts[i].display();
            return;
        }
    }
    cout << "Record not found.\n";
}

void Phonebook::showContacts() const {
    for (int i = 0; i < contactCount; ++i) {
        contacts[i].display();
    }
}

void Phonebook::modifyContact() {
    string phoneNumber;
    cout << "Enter the phone number of the record to modify: ";
    cin >> phoneNumber;

    int index = findContactIndex(phoneNumber);
    if (index == -1) {
        cout << "Record doesn't exist! Try again...\n";
        return;
    }

    string newName, newEmail, newAddress;

    cout << "Enter new name: ";
    cin.ignore();
    getline(cin, newName);

    cout << "Enter new email (optional): ";
    getline(cin, newEmail);

    cout << "Enter new address (optional): ";
    getline(cin, newAddress);

    contacts[index].setName(newName);
    contacts[index].setEmail(newEmail);
    contacts[index].setAddress(newAddress);

    cout << "Record modified successfully!\n";
}

void Phonebook::deleteContact() {
    string phoneNumber;
    cout << "Enter the phone number of the record to delete: ";
    cin >> phoneNumber;

    int index = findContactIndex(phoneNumber);
    if (index == -1) {
        cout << "Record doesn't exist! Try again...\n";
        return;
    }

    for (int i = index; i < contactCount - 1; ++i) {
        contacts[i] = contacts[i + 1];
    }
    --contactCount;

    cout << "Record deleted!\n";
}

void Phonebook::saveToFile() const {
    ofstream file("phonebook.txt", ios::trunc);
    for (int i = 0; i < contactCount; ++i) {
        file << contacts[i].getPhoneNumber() << "\n"
             << contacts[i].getName() << "\n"
             << contacts[i].getEmail() << "\n"
             << contacts[i].getAddress() << "\n";
    }
    file.close();
}

void Phonebook::loadFromFile() {
    ifstream file("phonebook.txt");
    if (!file.is_open()) return;

    string phoneNumber, name, email, address;
    while (getline(file, phoneNumber)) {
        getline(file, name);
        getline(file, email);
        getline(file, address);
        if (contactCount < MAX_CONTACTS) {
            contacts[contactCount++] = Contact(phoneNumber, name, email, address);
        }
    }
    file.close();
}

// Main function
void displayMenu() {
    cout << "Phonebook Management System\n";
    cout << "1. Add Phone Record\n";
    cout << "2. Search Phone Record\n";
    cout << "3. Show All Phone Records\n";
    cout << "4. Modify Phone Record\n";
    cout << "5. Delete Phone Record\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Phonebook phonebook;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                phonebook.addContact();
                break;
            case 2:
                phonebook.searchContact();
                break;
            case 3:
                phonebook.showContacts();
                break;
            case 4:
                phonebook.modifyContact();
                break;
            case 5:
                phonebook.deleteContact();
                break;
            case 6:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    } while (choice != 6);

    return 0;
}
