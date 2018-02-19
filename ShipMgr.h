#ifndef SHIPMGR_H
#define SHIPMGR_H
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include "Ship.h"
#include "CargoShip.h"
#include "CruiseShip.h"
using namespace std;
const int SIZE = 999;
class ShipMgr {
private:
	Ship *shipArr[SIZE];
	int shipNum = 0;
public:
	ShipMgr() {
		ifstream infile;
		string buffer;
		for (int i = 0; i < SIZE; i++) { //Initialize array to NULL
			shipArr[i] = NULL;
		}
		infile.open("shipRecords-1.txt");
		string type;
		string name;
		string year;
		int capacity;
		int i = 0;
		while (!infile.eof()) {
			getline(infile, type, char(32)); //Get first number and delete space
			getline(infile, buffer, char(34)); //Read and store first quotation into empty "buffer"
			getline(infile, name, char(34)); //Read and store until next set of quotation marks
			infile >> year; //Use infile to ignore whitespace
			infile >> capacity;
			infile.ignore(); //Clear return from infile
			if (type == "1") { //Create new CargoShip class
				shipArr[i] = new CargoShip(type, name, year, capacity);
			} else {//Create new CruiseShip class
				shipArr[i] = new CruiseShip(type, name, year, capacity);
			}
			i++; //Move to next spot in array
			shipNum++;
		}
	}

	~ShipMgr() {
		for (int i = 0; i < SIZE; i++)
			if (shipArr[i] != NULL)
				delete shipArr[i];
	}
	void DisplayCargoShips() {
		cout << "Cargo Ship\n";
		cout << "=============\n";
		cout << setw(20) << " " << setw(15) << right << "Year" << setw(20)
				<< right //Display headings
				<< "Cargo Capacity" << endl;
		for (int i = 0; i < shipNum; i++) {
			if (shipArr[i]->getType()=="1"){//Call on Ship class to get the type
					shipArr[i]->display();
			}
		}
		cout << setw(54) << right << "Number of Cargo Ships: " << CargoShip::getCargoShipCount()  << endl;//Retrieve static variables
		cout << setw(52) << right << "Total Cargo Capacity: " << CargoShip::getCapacity() << endl;
	}

	void DisplayCruiseShips() {
		cout << "Cruise Ship\n"; //Essentially the same for cruise ships but different variables are called
		cout << "=============\n";
		cout << setw(20) << " " << setw(15) << right << "Year" << setw(20)
				<< right << "# of Passengers" << endl;
		for (int i = 0; i < shipNum; i++) {
			if (shipArr[i]->getType()=="2"){
					shipArr[i]->display();
			}
		}
		cout << setw(54) << right << "Number of Cruise Ships: " << CruiseShip::getCruiseShipCount()  << endl;
		cout << setw(51) << right << "Total Passengers: " << CruiseShip::getPassengers() << endl;
	}
};

#endif // SHIPMGR_H
