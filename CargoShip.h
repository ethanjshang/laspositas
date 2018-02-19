/*
 * CargoShip.h
 *
 *  Created on: Feb 23, 2017
 *      Author: Ethan
 */
#include "Ship.h"
#ifndef CARGOSHIP_H_
#define CARGOSHIP_H_
using namespace std;
class CargoShip : public Ship{//Inherits from Ship
private:
	static int CargoShipCount;
	static int totalCapacity;
	int capacity;
public:
	CargoShip(string t, string n, string y, int c):Ship(t, n, y)//Takes four arguments and sends three to Ship's constructor
    {
		capacity = c;
		CargoShipCount++;//Every CargoShip class constructed increments static variable
	}
	~CargoShip(){
	}
	void setCargoShipCount(int s)
	{CargoShipCount = s;}
	static int getCargoShipCount() //Getter to retrieve static variable
	{return CargoShipCount;}
	static int getCapacity(){
		return totalCapacity;
	}
	void display()
	{
			totalCapacity += capacity;
			cout << setw(20) << left << getName() << setw(15) << right
					<< getYear() << setw(20) << capacity
					<< endl;
	}
};


int CargoShip::CargoShipCount = 0;
int CargoShip::totalCapacity = 0;
#endif /* CARGOSHIP_H_ */
