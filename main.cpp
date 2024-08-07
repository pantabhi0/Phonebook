#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Contact
{
private:
    string phoneNumber;
    string name;
    string email;
    string address;

public:
    Contact();
    Contact(string phoneNumber, string name, string email = "", string address = "");

    void setPhoneNumber(const string &phoneNumber);
    void setName(const string &name);
    void setEmail(const string &email);
    void setAddress(const string &address);

    string getPhoneNumber() const;
    string getName() const;
    string getEmail() const;
    string getAddress() const;

    void display() const;
};

Contact::Contact() {}

Contact::Contact(string phoneNumber, string name, string email, string address)
    : phoneNumber(phoneNumber), name(name), email(email), address(address) {}

void Contact::setPhoneNumber(const string &phoneNumber)
{
    this->phoneNumber = phoneNumber;
}

void Contact::setName(const string &name)
{
    this->name = name;
}

void Contact::setEmail(const string &email)
{
    this->email = email;
}

void Contact::setAddress(const string &address)
{
    this->address = address;
}

string Contact::getPhoneNumber() const
{
    return phoneNumber;
}

string Contact::getName() const
{
    return name;
}

string Contact::getEmail() const
{
    return email;
}

string Contact::getAddress() const
{
    return address;
}

void Contact::display() const
{
    cout << "Name: " << name << "\n";
    cout << "Phone Number: " << phoneNumber << "\n";
    if (!email.empty())
    {
        cout << "Email: " << email << "\n";
    }
    if (!address.empty())
    {
        cout << "Address: " << address << "\n";
    }
    cout << endl;
}

class Node
{
public:
    Contact contact;
    Node *next;
    Node(Contact contact) : contact(contact), next(nullptr) {}
};

class Phonebook
{
private:
    Node *head;

    Node *findContact(const string &phoneNumber);
    void saveToFile();
    void loadFromFile();

public:
    Phonebook();
    ~Phonebook();

    void addContact();
    void searchContact();
    void showContacts();
    void modifyContact();
    void deleteContact();
};

Phonebook::Phonebook() : head(nullptr)
{
    loadFromFile();
}

Phonebook::~Phonebook()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

Node *Phonebook::findContact(const string &phoneNumber)
{
    Node *current = head;
    while (current != nullptr)
    {
        if (current->contact.getPhoneNumber() == phoneNumber)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void Phonebook::addContact()
{
    string phoneNumber, name, email, address;

    cout << "Enter phone number: ";
    cin >> phoneNumber;
    if (findContact(phoneNumber))
    {
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

    Contact newContact(phoneNumber, name, email, address);
    Node *newNode = new Node(newContact);
    newNode->next = head;
    head = newNode;

    saveToFile();
    cout << "Phone details successfully stored.\n";
}

void Phonebook::searchContact()
{
    string query;
    cout << "Enter phone number or name to search: ";
    cin.ignore();
    getline(cin, query);

    Node *current = head;
    while (current != nullptr)
    {
        if (current->contact.getPhoneNumber() == query || current->contact.getName() == query)
        {
            current->contact.display();
            return;
        }
        current = current->next;
    }
    cout << "Record not found.\n";
}

void Phonebook::showContacts()
{
    Node *current = head;
    while (current != nullptr)
    {
        current->contact.display();
        current = current->next;
    }
}

void Phonebook::modifyContact()
{
    string phoneNumber;
    cout << "Enter the phone number of the record to modify: ";
    cin >> phoneNumber;

    Node *contactNode = findContact(phoneNumber);
    if (!contactNode)
    {
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

    contactNode->contact.setName(newName);
    contactNode->contact.setEmail(newEmail);
    contactNode->contact.setAddress(newAddress);

    saveToFile();
    cout << "Record modified successfully!\n";
}

void Phonebook::deleteContact()
{
    string phoneNumber;
    cout << "Enter the phone number of the record to delete: ";
    cin >> phoneNumber;

    Node *current = head;
    Node *previous = nullptr;

    while (current != nullptr && current->contact.getPhoneNumber() != phoneNumber)
    {
        previous = current;
        current = current->next;
    }

    if (!current)
    {
        cout << "Record doesn't exist! Try again...\n";
        return;
    }

    if (previous == nullptr)
    {
        head = current->next;
    }
    else
    {
        previous->next = current->next;
    }

    delete current;
    saveToFile();
    cout << "Record deleted!\n";
}

void Phonebook::saveToFile()
{
    ofstream file("phonebook.txt", ios::trunc);
    Node *current = head;
    while (current != nullptr)
    {
        file << current->contact.getPhoneNumber() << "\n"
             << current->contact.getName() << "\n"
             << current->contact.getEmail() << "\n"
             << current->contact.getAddress() << "\n";
        current = current->next;
    }
    file.close();
}

void Phonebook::loadFromFile()
{
    ifstream file("phonebook.txt");
    if (!file.is_open())
        return;

    string phoneNumber, name, email, address;
    while (getline(file, phoneNumber))
    {
        getline(file, name);
        getline(file, email);
        getline(file, address);
        Contact contact(phoneNumber, name, email, address);
        Node *newNode = new Node(contact);
        newNode->next = head;
        head = newNode;
    }
    file.close();
}

void displayMenu()
{
    cout << "Phonebook Management System\n";
    cout << "1. Add Phone Record\n";
    cout << "2. Search Phone Record\n";
    cout << "3. Show All Phone Records\n";
    cout << "4. Modify Phone Record\n";
    cout << "5. Delete Phone Record\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    Phonebook phonebook;
    int choice;

    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
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
