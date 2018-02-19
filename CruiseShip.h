/*
 * CruiseShip.h
 *
 *  Created on: Feb 23, 2017
 *      Author: Ethan
 */

#ifndef CRUISESHIP_H_
#define CRUISESHIP_H_
#include <iostream>
#include "Ship.h"
using namespace std;

class CruiseShip : public Ship{//Essentially the same as CargoShip but with passengers instead of cargo
private:
	static int CruiseShipCount;
	static int totalPassengers;
	int passengers;
public:
	CruiseShip(string t, string n, string y, int p):Ship(t, n, y)
    {
		passengers = p;
		CruiseShipCount++;
	}
	void setCruiseShipCount(int s)
	{CruiseShipCount = s;}

	static int getCruiseShipCount()
	{return CruiseShipCount;}

	static int getPassengers(){
		return totalPassengers;
	}
	void display()
	{
			totalPassengers+=passengers;
			cout << setw(20) << left << getName() << setw(15) << right
					<< getYear() << setw(20) << passengers
					<< endl;
		}
};


int CruiseShip::CruiseShipCount = 0;
int CruiseShip::totalPassengers = 0;
#endif /* CRUISESHIP_H_ */
