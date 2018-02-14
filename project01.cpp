//============================================================================
// ProjectID/Name : PROJECT01/project01.cpp
// Author         : Ethan Shang
// Date Completed : 11/14/16
// OS Used        : Windows 10
// IDE/Compiler   : Eclipse Mars/gcc
//============================================================================

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
const int SIZE = 20;//Maximum number of clients is 20
const int YEARS = 26;//One year before interest accumulates plus 25 guaranteed years
using namespace std;
void getInfo(string[SIZE],float[YEARS][SIZE],int&);//Description of each function above each function definition
float calculate(float, float, float, int, int, int&, int, float[YEARS][SIZE]);
void resultsOut(string[SIZE],float[YEARS][SIZE],int);
void rankingOut(string[SIZE],float[YEARS][SIZE],int);
void perClient(string[SIZE],float[YEARS][SIZE],int);

int main() {
	string names[SIZE];//Create 1-D array needed to store names
	float balances[YEARS][SIZE];//Create 2-D array needed to store balances; Rows correspond to years and columns correspond to clients
	int numClients = 0;
	getInfo(names,balances,numClients);
	resultsOut(names,balances,numClients);
	rankingOut(names,balances,numClients);
	for (int count = 0; count < numClients; count++){//Use number of clients retrieved from getInfo() to determine how many files to make
		perClient(names,balances,count);
	}
	return 0;
}
/*
Function: getInfo
Task    : Retrieve and store the names of each client; retrieve the data needed for calculations
Data in : names array, balances array, integer to track the number of clients in the data file
Data out: Nothing returned, but the following variables are changed:
		  -names array has the clients' names added
		  -balances array has each year's balance after calculate() is run
		  -numClients stores the number of clients for later when the number of clients is used
		   to determine the number of individual files to create.
*/
void getInfo(string names[SIZE],float balances[YEARS][SIZE],int& numClients){
	float deposit, rate, totalBalance;//For calculating balances
	int year;						  //For calculating balances and keeping track of loops per client
	int totalYear;					  //For keeping track of loops per client
	int currentRow, currentCol=0;     //For storing balances by keeping track of loops per client and separating clients
	ifstream infile;				  //Define file stream object
	string input;				 	  //For detecting 4 dashes from input file and check for continuing input
	int i = 0;					 	  //Counter
	infile.open("client_data.txt");	  //Open then check & display whether or not file opened correctly
	if (infile) {
		cout << "Input file opened successfully.\n";
	}
	else {
		cout << "Input file not opened correctly.\n";
	}
	while (infile >> input) { //As long as data is being read in from the file loop continues
		if (input == "----") {//Checks for required set of four dashes indicating a new client
			numClients++;     //4 dashes means a new client so the number of clients is increased by 1
			if (getline(infile, names[i])) {//Checks if the next line can be retrieved
				getline(infile, names[i]);  //Retrieve name and store
				i++;             //Step to next spot in array of names
				totalYear = 0;   //Set accumulator to zero for new client
				totalBalance = 0;//Set balance equal to zero for new client
				currentRow = 1;  //currentRow is 1 because the first row (balances[0][SIZE]) will be deposits only
				while (totalYear <= (YEARS - 2) ){//Check that total years adds up to 25 and keep running until 25 total years have been added together
				infile >> deposit >> rate >> year;//Retrieve each datum from a line in a file
				totalBalance = calculate(totalBalance,deposit, rate, year,totalYear, currentRow, currentCol,balances);//returns updated balance to carry over between new interest rates
				totalYear += year;//Accumulates number of years
				}
			}
			currentCol++;//Next client
		}
	}
	infile.close();
}
/*
Function: calculate
Task    : Calculate and store a client's balance every year
Data in : totalBalance - balance from previous year, deposit - (new) deposit from file,
		  interest - next interest from file, year - amount of years from file to control loop
		  totalYear - how many years have been processed for client: check deposit is 1st year deposit
		  row - passed by reference to monitor year between calculate() function calls
		  col - store in the right column, that is to say the right client
		  balances - the array in which to store balances
Data out: totalBalance is returned to pass it to the next set of calculations for next set of data
		  balances is stored with the balances from each year and each client
*/
float calculate(float totalBalance, float deposit, float interest, int year, int totalYear, int& row,
		int col, float balances[YEARS][SIZE]) {
	if (totalYear == 0){
	balances[0][col] = deposit;//Set the first row equal to the initial deposit for each client
	}
	totalBalance = (deposit + totalBalance)*(1+interest);//Add the deposit for the first year in each new interest rate
	balances[row][col] = totalBalance;					 //Store the value in the array
	row++;												 //Step to the next year
	for (int i = 1; i < year; i++, row++) {//Increment for 1 less in the interval because 1st year was already calculated
		totalBalance *= (1+interest);      //multiply balance for years without new deposit
		balances[row][col] = totalBalance; //Store the new balance in array
	}
	return totalBalance; //totalBalance is passed for the next set of calculations for next line of data
}

/*
Function: resultsOut
Task    : Output the clients' data to a data file with data from all clients
Data In : array of the clients' names, array of clients' balances, numClients - number of clients used to control loops and avoid if-statements in loops
Data Out: One file of all of the clients' data
*/
void resultsOut(string names[SIZE], float balances[YEARS][SIZE], int numClients){
	ofstream outfile; 				   //Define file stream object
	outfile.open("client_results.csv");//Open then check & display whether or not file opened correctly
	if (outfile) {
		cout << "Client data output file opened successfully.\n";
	}
	else{
		cout << "Client data output file not opened correctly.\n";
	}
	outfile << "Year" <<",";	   //Create label for years column
	for (int i = 0; i < numClients; i++){//Store valid names in file
		outfile << names[i] << ",";
	}
	outfile << endl; //New line to start storing balances
		for (int j = 0; j < YEARS; j++){
			outfile << j << ",";           //Use a counter to store the years
			for (int k = 0; k < numClients; k++){//Stores values horizontally
				outfile << setprecision(2) << fixed << showpoint; //Make sure two places after decimal is stored
				outfile << balances[j][k]<< ",";
			}
			outfile << endl; //Next year
		}
	outfile << "\n";//Trailing newline character that .csv files need
	outfile.close();
}

/*
Function: rankingOut
Task    : Sort balances array by client in descending order then sort client array accordingly
		  Create file with ranking of client with 1 being the most money after 25 years
Data In : Names array, balances array, numClients - number of clients used to control loops and avoid if-statements in loops
Data Out: File that ranks clients
*/
void rankingOut(string names[SIZE], float balances[YEARS][SIZE], int numClients){
	ofstream outfile;      //Defines file stream object
	float ranking[numClients];   //Creates new array of balances so original is not changed during sort
	string newNames[numClients]; //Creates new array of names so original is not changed during sort
	bool change;		   //For checking if sort is finished
	float temp;			   //For switching balance array elements while sorting
	string temp2;		   //For switching names array elements while sorting
	for (int count =0; count < numClients;count++){//Creates 1-D array of balances so original is not changed
		ranking[count] = balances[YEARS-1][count];
	}
	for (int i = 0; i < numClients; i++){//Creates new array of names so original is not changed
		newNames[i]=names[i];
	}
	do {//Start the bubble sort
		change = false;
		for (int i = 0; i < (numClients-1); i++){//Bubble sort method used because it is a small array
			if (ranking[i] < ranking[i+1])//Ascending order
			{
				temp = ranking[i];//temp switches the balances
				ranking[i] = ranking[i + 1];
				ranking[i + 1] = temp;
				temp2 = newNames[i];//temp2 switches the names
				newNames[i] = newNames[i + 1];
				newNames[i + 1] = temp2;
				change = true;
			}
		}
	}while (change);
	outfile.open("ranking.csv");//Open then check & display whether or not file opened correctly
	if (outfile) {
		cout << "Ranking output file opened successfully.\n";
	}
	else{
		cout << "Ranking output file not opened correctly.\n";
	}
	outfile << "Ranking" << "," << "Name" << "," << "Ending Balance"<<endl; // Create heading for each column

	for (int j = 0; j < numClients; j++){
			outfile << setprecision(2) << fixed << showpoint; //Make sure two places after decimal is stored
			outfile << j+1 << "," << newNames[j] << "," << ranking[j]<<endl;
	}

	outfile << "\n";//Trailing newline character that .csv files need
	outfile.close();
}

/*
Function: perClient
Task    : Create a specific number of client-specific files that show balances in every year
Data In : Names array, balances array, count - number of clients
Data Out: Client-specific files whose quantity corresponds to the value stored in count
*/
void perClient(string names[SIZE], float balances[YEARS][SIZE],int count){
	ofstream outfile;    //Define file stream object
	string filename;	 //For overall filename
	stringstream ending; //For number that goes into filename
	ending << count + 1; //count + 1 because count is sent from a loops that is initialized at 0
	filename = "Client" + ending.str() + ".csv"; //Concatenate strings together to form filename
	outfile.open(filename.c_str());				 //Convert filename to cstring then open/create file
	if (outfile) {								 //Check if file was opened correctly
		cout << "Individual output file for client " << count+1 << " opened successfully.\n";
	}
	else{
		cout << "Individual output file for client " << count+1 << " opened successfully.\n";
	}
	outfile << "Year" << "," << names[count] << endl;//Creates headings for each column
	for (int i = 0; i < YEARS; i++){				 /*No checks needed because the loop will only run through altered values
													   due to number of clients being recorded and perClient() only being run
													   that many times */
		outfile << setprecision(2) << fixed << showpoint; //Make sure two places after decimal is stored
		outfile << i << "," << balances[i][count] << endl;/*Stores values in file; count is unchanged for each function call
															because data must be stored by column (client)*/
	}
	outfile << "\n";
	outfile.close();//Trailing newline character that .csv files need
}
