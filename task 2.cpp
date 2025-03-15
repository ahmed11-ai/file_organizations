#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct ClientData {
	int acctNum; 
	char lastName[15]; 
	char firstName[10];
	double balance; 
}; 

void main() {
	ClientData client; 
	
	fstream file("d:/credit.dat", ios::in | ios::out | ios::binary);
	
	if (!file) {
		cerr << "File could not be opened." << endl;
		return;
	}
	else {
		
		char action = 'a';
		while (action != 'q')
		{
			cout << "Enter 'r' to read, 'w' to write, q to exit (r/w/q): ";
			cin >> action;
			if (action == 'w') { 
				
				cout << "Enter account number (1 to 100): ";
				cin >> client.acctNum;
				
				cout << "Enter lastname, firstname, balance: ";
				cin >> client.lastName >> client.firstName
					>> client.balance;
				
				file.seekp((client.acctNum - 1) * sizeof(ClientData),
					ios::beg);
				
				file.write(reinterpret_cast<const char*>(&client),
					sizeof(ClientData));
			}
			else if (action == 'r') { 
				
				cout << "Enter account number to read (1 to 100): ";
				int accountToRead;
				cin >> accountToRead;

					
					file.seekg((accountToRead - 1) * sizeof(ClientData),
						ios::beg);
				
				file.read(reinterpret_cast<char*>(&client),
					sizeof(ClientData));
				
				cout << "Account Number: " << client.acctNum << endl;
				cout << "Last Name: " << client.lastName << endl;
				cout << "First Name: " << client.firstName << endl;
				cout << "Balance: " << client.balance << endl;
			}
			else if (action == 'q') {
				exit(0);
			}
			else
				cout << "invalid" << endl;
		}
		file.close(); 
	}
	system("pause");
}