//============================================================================
// Name        : StringProcessing.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
const int SIZE = 6;
struct ship {
	string type;
	string name;
	string year;
	int capacity;
};
void Display(ship[SIZE]);

int main() {
	ship shipArr[SIZE];
	ifstream infile;
	string buffer;
	int i = 0;
	infile.open("shipRecords-1.txt");
	while (!infile.eof()) {
		getline(infile, shipArr[i].type, char(32));//Get first number and delete space
		getline(infile, buffer, char(34));//Read and store first quotation into empty "buffer"
		getline(infile, shipArr[i].name, char(34));//Read and store until next set of quotation marks
		infile >> shipArr[i].year; //Use infile to ignore whitespace
		infile >> shipArr[i].capacity;
		infile.ignore();//Clear return from infile
		i++;//Move to next spot in array
	}
	infile.close();
	Display(shipArr);
	return 0;
}

void Display(ship shipArr[SIZE]) { //Pass array of structs by reference
	int cargoCount = 0, cruiseCount = 0; //Number of each type of ship
	int cargoTotal = 0, cruiseTotal = 0; //Total capacity of each type of ship
	cout << "Cargo Ship\n";
	cout << "=============\n";
	cout << setw(20) << " " << setw(15) << right << "Year" << setw(20) << right //Display headings
			<< "Cargo Capacity" << endl;
	for (int i = 0; i < SIZE; i++) {
		if (shipArr[i].type == "1") {//Use first number to choose to display or not
			cout << setw(20) << left << shipArr[i].name << setw(15) << right //Display all info by ship
					<< shipArr[i].year << setw(20) << shipArr[i].capacity
					<< endl;
			cargoCount++;//Increment number of cargo ships
			cargoTotal += shipArr[i].capacity; //Add capacity of ship to total
		}
	}
	cout << setw(40) << right << cargoCount << " Cargo Ships" << endl;
	cout << setw(50) << right << "Total Cargo Capability: " << cargoTotal;

	cout << endl << endl;

	cout << "Cruise Ship\n"; //Essentially the same for cruise ships but different variables are called
	cout << "=============\n";
	cout << setw(20) << " " << setw(15) << right << "Year" << setw(20) << right
			<< "# of Passengers" << endl;
	for (int i = 0; i < SIZE; i++) {
		if (shipArr[i].type == "2") {
			cout << setw(20) << left << shipArr[i].name << setw(15) << right
					<< shipArr[i].year << setw(20) << shipArr[i].capacity
					<< endl;
			cruiseCount++;
			cruiseTotal += shipArr[i].capacity;
		}
	}
	cout << setw(40) << right << cruiseCount << " Cruise Ships" << endl;
	cout << setw(50) << right << "Total # of Passengers: " << cruiseTotal;
}
