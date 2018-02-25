/*
 * UniqueList.h
 *
 *  Created on: Mar 2, 2017
 *      Author: Ethan
 */

#ifndef UNIQUELIST_H_
#define UNIQUELIST_H_

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

template<typename T>
class UniqueList {
private:
	vector<T> items;
public:
	UniqueList();
	void Describe() const;
	int Size();
	T GetFirst();
	T GetLast();
	T GetMin();
	T GetMax();

	void Insert(T item);

};

template<typename T>
T Pick(T op1, T op2, T op3) {
	srand(time(NULL));
	int randNum = rand() % 3; //Generate random number
	if (randNum == 0) {//Use randnum to choose option
		return op1;
	} else if (randNum == 1) {
		return op2;
	} else {
		return op3;
	}
}
template<typename T>
T GetChoice(string s1, string s2, T other1, T other2) {
	string choice;
	T returnVal;
	do {
		cout << "Please pick " << s1 << " or " << s2 << ": \n";
		cin >> choice;
		if (choice == s1) {//Display  variable
			returnVal = other1;
		} else {
			returnVal = other2;
		}
	} while (choice != s1 and choice != s2); //Do-while loop until user chooses one of options
	return returnVal;
}
template<typename T>
UniqueList<T>::UniqueList() {

}

template<typename T>
void UniqueList<T>::Insert(T item) {
	bool add = true;
	for (unsigned int i = 0; i < items.size(); i++) {
		if (items[i] == item) {//Checks if item is in list
			cout << endl << "Your value (" << item
					<< ") is already in the vector" << endl;
			add = false;//Changes if item is already in list
		}
	}
	if (add) {
		items.push_back(item);//Appends item if not in vector
		cout << item << " has been added.\n";
	}
}

template<typename T>
void UniqueList<T>::Describe() const {
	for (unsigned int i = 0; i < items.size(); i++) {
		cout << items[i] << ' ';
	}
	cout << endl;
}

template<typename T>
int UniqueList<T>::Size() {
	return items.size();
}

template<typename T>
T UniqueList<T>::GetFirst() {
	return items.front();
}

template<typename T>
T UniqueList<T>::GetLast() {
	return items.back();
}

template<typename T>
T UniqueList<T>::GetMin() {
	T min = items[0];//Assigns min val to first item in vector
	for (unsigned int i = 0; i < items.size(); i++) {
		if (items[i] < min) {//Compares every item to first item
			min = items[i];
		}
	}
	return min;
}
template<typename T>
T UniqueList<T>::GetMax() {
	T max = items[0];
	for (unsigned int i = 0; i < items.size(); i++) {
		if (items[i] > max) {//Switches direction of equality
			max = items[i];
		}
	}

	return max;
}

#endif /* UNIQUELIST_H_ */
