#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct ClientData {
    int acctNum;
    char lastName[15];
    char firstName[10];
    double age;
};

void insertClient(fstream& file) {
    ClientData client;
    cout << "Enter account number (1 to 100): ";
    cin >> client.acctNum;
    cout << "Enter firstname, lastname, age: ";
    cin >> client.lastName >> client.firstName >> client.age;

    file.seekp((client.acctNum - 1) * sizeof(ClientData), ios::beg);
    file.write(reinterpret_cast<const char*>(&client), sizeof(ClientData));
    cout << "Client data inserted successfully!" << endl;
}

void readClient(fstream& file) {
    ClientData client;
    int accountToRead;
    cout << "Enter account number to read (1 to 100): ";
    cin >> accountToRead;

    file.seekg((accountToRead - 1) * sizeof(ClientData), ios::beg);
    file.read(reinterpret_cast<char*>(&client), sizeof(ClientData));

    if (client.acctNum == 0) {
        cout << "No record found for account number " << accountToRead << endl;
    } else {
        cout << "Account Number: " << client.acctNum << endl;
        cout << "Last Name: " << client.lastName << endl;
        cout << "First Name: " << client.firstName << endl;
        cout << "Age: " << client.age << endl;
    }
}

void deleteClient(fstream& file) {
    ClientData blankClient = {0, "", "", 0.0};
    int accountToDelete;
    cout << "Enter account number to delete (1 to 100): ";
    cin >> accountToDelete;

    file.seekp((accountToDelete - 1) * sizeof(ClientData), ios::beg);
    file.write(reinterpret_cast<const char*>(&blankClient), sizeof(ClientData));
    cout << "Client data deleted successfully!" << endl;
}

void searchClient(fstream& file) {
    ClientData client;
    int accountToSearch;
    cout << "Enter account number to search (1 to 100): ";
    cin >> accountToSearch;

    file.seekg((accountToSearch - 1) * sizeof(ClientData), ios::beg);
    file.read(reinterpret_cast<char*>(&client), sizeof(ClientData));

    if (client.acctNum == 0) {
        cout << "No record found for account number " << accountToSearch << endl;
    } else {
        cout << "Client found!" << endl;
        cout << "Account Number: " << client.acctNum << endl;
        cout << "Last Name: " << client.lastName << endl;
        cout << "First Name: " << client.firstName << endl;
        cout << "Age: " << client.age << endl;
    }
}

int main() {
    string filename;
    cout << "Enter the file path and name (e.g., d:/credit.dat): ";
    cin >> filename;

    fstream file(filename, ios::in | ios::out | ios::binary);

    if (!file) {
        cout << "File does not exist. Creating a new file..." << endl;
        file.open(filename, ios::out | ios::binary);
        file.close();
        file.open(filename, ios::in | ios::out | ios::binary);
        if (!file) {
            cerr << "File could not be created." << endl;
            return 1;
        }
    }

    char action;
    while (true) {
        cout << "Enter 'r' to read, 'w' to write, 's' to search, 'd' to delete, 'q' to exit (r/w/s/d/q): ";
        cin >> action;

        switch (action) {
            case 'w': insertClient(file); break;
            case 'r': readClient(file); break;
            case 's': searchClient(file); break;
            case 'd': deleteClient(file); break;
            case 'q': file.close(); return 0;
            default: cout << "Invalid option!" << endl;
        }
    }
}

