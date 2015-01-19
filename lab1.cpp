// Ryan Roberge
// Joseph Lawrance
// 1-16-2015
// COMP201-2015

// Problem Statement:
// Write a program that gets file name from the command line (argv[1]) 
// and then creates a three-column table (each column separated by a tab (\t)), 
// populated based upon the integers found in the file. For each integer in the file, 
// the first column will be the integer, the second will be the integer squared, 
// and the third column is to show a running sum of the integers in the file.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// When running program from terminal, pass main the input file path (to be stored in argv[1])
int main(int argc, char* argv[])
{
	ofstream fout; // Declares the output file stream
	ifstream fin; // Declares the input file stream
	
	fin.open(argv[1]); // Opens the passed input file
	
	string outpath; // Declares a place holder string for the user's preferred output file path
	
	cout << "Enter the the desired output location: ";
	cin >> outpath; // Reads in the user's preferred output file path
	outpath += "/output.txt"; // Only asked for the output location, this ensures data gets dumped in a txt file
	
	fout.open(outpath.c_str()); // Converts the user entered string to a c-string so it can be used with the open function
	
	fout << "X\tX^2\tSum" << endl; // Prints table headers to the output file
	fout << "--------------------------------------" << endl;
	
	int sum = 0; // Sum is the place holder for the total sum of all occurring numbers in the input file
	while (!fin.eof()) // Runs this loop until there is nothing left to read in
    {
    	int x; // Place holder variable for reading in integers from the input file
    	fin >> x; // Reads this integer in from the input file
		sum += x; // Adds this number to the total sum of occurring numbers
    	fout << x << "\t" << x*x << "\t" << sum << endl; // Prints the information for one row to the output file
    }
	
	fin.close(); // Closes the input file
	fout.close(); // Closes the output file
	cout << endl;

	cout << "Execution complete." << endl;
	
	return 0;
}