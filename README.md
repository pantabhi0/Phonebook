Phonebook Management System

Documentation for Phonebook Management System
1. Overview
The Phonebook Management System is a simple command-line application designed to manage a list of contacts. It provides functionalities to add, search, modify, delete, and display contacts. The contacts are stored in an array and persist across sessions by saving to and loading from a file.

2. Features
Add Contact: Add new contact details to the phonebook.
Search Contact: Search for a contact by phone number or name.
Show Contacts: Display all contacts in the phonebook.
Modify Contact: Update the details of an existing contact.
Delete Contact: Remove a contact from the phonebook.
Persistent Storage: Contacts are saved to and loaded from a file (phonebook.txt).

3. Components
Contact Class:

Represents an individual contact with attributes such as phone number, name, email, and address.
Provides methods to set and get these attributes and to display the contact details.

Phonebook Class:

Manages a collection of Contact objects.
Provides methods to add, search, modify, delete contacts, and handle file I/O operations.

Main Function:

Provides a text-based menu interface for user interaction.
Calls appropriate methods from the Phonebook class based on user input.

4. Code Structure
Contact Class:

Contact(): Default constructor.
Contact(string phoneNumber, string name, string email, string address): Parameterized constructor.
setPhoneNumber, setName, setEmail, setAddress: Setters for contact attributes.
getPhoneNumber, getName, getEmail, getAddress: Getters for contact attributes.
display(): Displays contact details.

Phonebook Class:

Phonebook(): Constructor initializes contact array and loads data from file.
~Phonebook(): Destructor saves data to file and cleans up resources.
addContact(): Adds a new contact to the phonebook.
searchContact(): Searches and displays a contact.
showContacts(): Displays all contacts.
modifyContact(): Modifies an existing contact.
deleteContact(): Deletes a contact.
saveToFile(): Saves contacts to a file.
loadFromFile(): Loads contacts from a file.

Main Function:

displayMenu(): Shows the main menu.
main(): Handles user input and calls appropriate methods from the Phonebook class.

5. Usage Instructions

1. Compile and Run:

Use a C++ compiler to compile the code. For example:
g++ -o phonebook phonebook.cpp

Run the compiled executable:
./phonebook

2. Menu Options:

Follow the on-screen menu to add, search, modify, delete, or display contacts.

3. File Storage:

The phonebook data is stored in phonebook.txt. Ensure this file is in the same directory as the executable for proper functionality.

6. Example
Add Contact:

Enter phone number: 1234567890
Enter name: John Doe
Enter email (optional): john.doe@example.com
Enter address (optional): 123 Elm Street

Search Contact:

Enter phone number or name to search: John Doe
Name: John Doe
Phone Number: 1234567890
Email: john.doe@example.com
Address: 123 Elm Street

Modify Contact:

Enter the phone number of the record to modify: 1234567890
Enter new name: John Smith
Enter new email (optional): john.smith@example.com
Enter new address (optional): 456 Oak Street

Delete Contact:

Enter the phone number of the record to delete: 1234567890
Record deleted!
