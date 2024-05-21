#include <unordered_map>
#include <map>
#include <iostream>
#include <string>
#include <cctype>
#include <limits>
using namespace std;

// This function is used to convert the entered names to all uppercase 
string upper(string name) {
	string upperName;
	for (char c : name) {
		upperName += toupper(c);
	}
	name = upperName;
	return name;
}

// This function prompts the user for the employee's first and last name, checks their length and then combines them and uses the upper function on it
void namePrompt(string &fName, string &lName, string &name) {	
	cout << "\nWhat is the employee's first name? (Limit of 15 characters): ";
	cin.clear();
	cin >> fName;

	if (fName.length() >= 16 || fName.length() <= 0) {
		cout << "\nInvalid first name length! Please enter a valid first name length: ";
		cin.clear();
		cin >> fName;
	}

	cout << "\nWhat is the employee's last name? (Limit of 15 characters): ";
	cin.clear();
	cin >> lName;

	if (lName.length() >= 16 || lName.length() <= 0) {
		cout << "\nInvalid last name length! Please enter a valid last name length: ";
		cin.clear();
		cin >> lName;
	}

	name = upper(fName + " " + lName);

}

// This function prompts the user for the employee's salary, checking for invalid values
void salaryPrompt(unsigned int &salary) {
	cout << "\nWhat is the employee's salary? (Enter only numbers, no letters or commas): ";
	cin.clear();
	cin >> salary;

	while (!cin.good()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nInvalid input! Please enter one of the valid inputs previously mentioned: ";
		cin >> salary;
	}
}

// This function resets important variable values back to zero after being used
void resetValues(string &fName, string &lName, string &name, unsigned int &salary) {
	fName = "";
	lName = "";
	name = "";
	salary = 0;
}

// This function checks to see if there are any employees in the ordered/unordered map
bool noEmployeesCheck(unsigned int &employeeNumber) {	
	if (employeeNumber == 0) {
		cout << "\nNo employees in the database!" << endl;
		return true;
	}else{
		return false;
	}
}

// This function continues to ask the user what aspect of the program they would like to use after performing an action
void continueTheLoop(int& loopContinuer) { 
	cout << "\nWhat would you like to do?\nEnter 1 to enter a worker, 2 to delete a worker, 3 to search for a worker's information, \n4 to search for all worker's information, or 5 to quit the program: ";
	cin >> loopContinuer;

	while (!cin.good()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nInvalid input! Please enter one of the valid inputs previously mentioned: ";
		cin >> loopContinuer;
	}
}

// Every one of the cin values could use more error checking if the code is enhanced in the future
// Not adhering to the prompted acceptable input values will in most cases cause the program to break
int main()
{
	int mapChoice;
	int loopContinuer;
	string fName;
	string lName;
	string name;
	string department;
	unsigned int salary;
	unsigned int employeeNumber = 0;

	cout << "Welcome to the Herman Inc. Employee Database builder.\n\nWould you like to use an ordered map or an unordered map?\nSelect 1 for an ordered map, 2 for an unordered map, or 3 to quit the program: ";
	cin >> mapChoice;

	while (!cin.good()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nInvalid input! Please enter one of the valid inputs previously mentioned: ";
		cin >> mapChoice;
	}

	while (mapChoice != 3) {

		if (mapChoice == 1) {
			cout << "\nYou've chosen an ordered map.\nConstructing the map..." << endl;
			map<string, pair<int, int>> employees; // name, employeeNumber, salary
			cout << "Done! The map is ready for your use." << endl;

			continueTheLoop(loopContinuer);

			while (loopContinuer != 5) {

				switch (loopContinuer) {
				case 1:

					namePrompt(fName, lName, name);
					employeeNumber++;
					salaryPrompt(salary); 

					employees.emplace(name,  make_pair(employeeNumber, salary));
					cout << "\nName: " << name << "\nEmployee Number: " << employeeNumber << "\nSalary: " << salary << endl;
					resetValues(fName, lName, name, salary);
					break;

				case 2:
					if (noEmployeesCheck(employeeNumber) == true) {
						break;
					}
					namePrompt(fName, lName, name);

					if (employees.find(name) != employees.end()) {
						cout << "\nFound item! Now deleting..." << endl;
						employees.erase(name);
						employeeNumber--;
						cout << "Item is now deleted!" << endl;
					}else {
						cout << "\nItem not found! Please select delete again and enter a valid first and last name." << endl;
					}

					break;

				case 3:
					if (noEmployeesCheck(employeeNumber) == true) {
						break;
					}
					namePrompt(fName, lName, name);

					if (employees.find(name) != employees.end()) {
						cout << "\nInformation found about " << name << "\nEmployeeNumber: " << employees[name].first << "\nSalary: $" << employees[name].second << endl;
					}else{
						cout << "\nNo information about " << name << " found." << endl;
					}

					resetValues(fName, lName, name, salary);
					break;

				case 4:
					if (noEmployeesCheck(employeeNumber) == true) {
						break;
					}

					namePrompt(fName, lName, name);
					cout << "\nSearching for all worker's information...." << endl;
					cout << "\nName\t\t Employee Number\tSalary\n" << endl;
					
					for (const auto& print : employees) {
						cout << print.first << "\t\t" << print.second.first << "\t\t" << print.second.second << endl;
					}

					cout << "\nDone!" << endl;
					resetValues(fName, lName, name, salary);
					break;
				}

				continueTheLoop(loopContinuer);

				if (loopContinuer == 5) {
					mapChoice = 3;
				}

			}

		  // The unordered_map section is the same code as the ordered map section
		}else if(mapChoice == 2){
			cout << "\nYou've chosen an unordered map.\nConstructing the map..." << endl;
			unordered_map<string, pair<int, int>> employees; 
			cout << "\nDone! The map is ready for your use." << endl;
			
			continueTheLoop(loopContinuer);

			while (loopContinuer != 5) {

				switch (loopContinuer) {
				case 1: 

					namePrompt(fName, lName, name);
					employeeNumber++;
					salaryPrompt(salary);

					employees.emplace(name, make_pair(employeeNumber, salary));
					cout << "\nName: " << name << "\nEmployee Number: " << employeeNumber << "\nSalary: " << salary << endl;
					resetValues(fName, lName, name, salary);
					break;

				case 2:
					if (noEmployeesCheck(employeeNumber) == true) {
						break;
					}
					namePrompt(fName, lName, name);

					if (employees.find(name) != employees.end()) {
						cout << "\nFound item! Now deleting..." << endl;
						employees.erase(name);
						employeeNumber--;
						cout << "Item is now deleted!" << endl;
					}
					else {
						cout << "\nItem not found! Please select delete again and enter a valid first and last name." << endl;
					}

					break;

				case 3:
					if (noEmployeesCheck(employeeNumber) == true) {
						break;
					}
					namePrompt(fName, lName, name);

					if (employees.find(name) != employees.end()) {
						cout << "\nInformation found about " << name << "\nEmployeeNumber: " << employees[name].first << "\nSalary: $" << employees[name].second << endl;
					}
					else {
						cout << "\nNo information about " << name << " found." << endl;
					}

					resetValues(fName, lName, name, salary);
					break;

				case 4:
					if (noEmployeesCheck(employeeNumber) == true) {
						break;
					}

					namePrompt(fName, lName, name);
					cout << "\nSearching for all worker's information...." << endl;
					cout << "\nName\t\t Employee Number\tSalary\n" << endl;

					for (const auto& print : employees) {
						cout << print.first << "\t\t" << print.second.first << "\t\t" << print.second.second << endl;
					}

					cout << "\nDone!" << endl;
					resetValues(fName, lName, name, salary);
					break;
				}

				continueTheLoop(loopContinuer);

				if (loopContinuer == 5) {
					mapChoice = 3;
				}

			}
		}
		else {
			cout << "\nInvalid input! Please enter one of the valid inputs previously mentioned: ";
			cin >> loopContinuer;
		}
		
		if (loopContinuer == 5) {
			mapChoice = 3;
		}
	}
	cout << "\nYou've chosen to end the program. Thank you for using the Herman Inc. Employee Database builder." << endl;
}


