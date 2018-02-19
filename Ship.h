/*
 * Ship.h
 *
 *  Created on: Feb 27, 2017
 *      Author: Ethan
 */

#ifndef SHIP_H_
#define SHIP_H_
#include <string>
#include <iostream>
using namespace std;
class Ship{
private:
	string type;
	string name;
	string year;
public:
	Ship(string t, string n, string y){//Each ship will either have passengers or cargo
		type = t;
		name = n;
		year = y;
	}
	virtual ~Ship(){
	}
	void setType(string t)
	{type = t;}
	string getType()
	{return type;}

	void setName(string n)
	{name = n;}
	string getName()
	{return name;}

	void setYear(string y)
	{year = y;}
	string getYear()
	{return year;}


	virtual void display() = 0;
};



#endif /* SHIP_H_ */
