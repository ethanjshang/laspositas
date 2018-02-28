//============================================================================
// Name        : Recursion.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
void countDown(int);
void factorialFor(int);
void factorialRe(int);
void sumFunc(int[], int);
void sumFuncFaster(int[], int, int);
void display(int);
void normalPrint(char *);
void reversePrint(char *);
int main() {
	int arr[16] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	int num;
    char *str = "Normal or Reverse";
    normalPrint(str);  //"Normal or Reverse" is displayed
    cout << endl;
    reversePrint(str); //The same string is displayed in reverse order
    cout << endl;
    cout << "Enter a number: " << endl;
    cin >> num;
    countDown(num);
	factorialFor(num);
	factorialRe(num);
	sumFunc(arr, 16);
	//sumFuncFaster(arr,16);
	display(num);

	return 0;
}
void countDown(int num) {
	if (num == 0) // Base case
		cout << "Blastoff!";
	else	// General case
	{
		cout << num << "...\n";
		countDown(num - 1); // recursive call
	}
}

void factorialFor(int num) {
	int print = 1;
	for (int i = 1; i <= num; i++) {
		print *= i;
	}
	cout << endl << "For loop factorial: " << print << endl;
}

void factorialRe(int num) {
	static int fact = 1;
	if (num == 0) {
		cout << endl << "Recursive factorial: " << fact << endl;
	} else {
		fact *= num;
		factorialRe(num - 1);
	}
}
void sumFunc(int arr[], int num) {
	static int sum = 0;
	if (num == 0) {
		cout << endl << "Sum of array: " << sum << endl << endl;
	} else {
		sum += arr[--num];
		sumFunc(arr, num);
	}
}

void sumFuncFaster(int arr[], int low, int high){
    int medium = ((low+high)/2);
    int total= 1+high-low;
    if (total == 0){
        return 0;
    }
    else if (total == 1){
        return arr[low];
    }
    else if (total == 2){
        return arr[low]+arr[high];
    }
    else{
        return sumFuncFaster(arr, low, medium) + sumFuncFaster(arr, medium+1, high);
    }

//	sumFunc()

}

void display(int intX) {
	if (intX < 10)
		display(intX + 1);
	cout << intX << endl;
}
void normalPrint(char *s) {
	if (*s) {
		cout << *s;
		normalPrint(s + 1);
	}
}
void reversePrint(char *s){
	if (*s) {
		reversePrint(s + 1);
		cout << *s;
	}
}
