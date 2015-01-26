#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

int main()
{
	vector<int> math; // Container that holds all integers entered by the user
	string inp = ""; // Place holder string that stores user input 
	int temp; // Place holder integer that stores the last integer from vector<int> math
	int temp2; // Place holder integer that stores the last integer from vector<int> math
	int converted; // Place holder integer for the string input that will be converted to a true int
	char *end; // Dummy null pointer variable
	
	cout << "Enter your RPN equation, or type \"done\" to finish and exit." << endl;
	
	while(inp != "done") // Run this loop, reading input, until the user enters "done"
	{	
		cin >> inp; // Reads in input
		
		if(inp == "+") // User wants Addition
		{
			temp = math.back(); // Copies the last number in the stack to variable temp
			math.pop_back(); // Removes the last number from the stack
			temp = temp + math.back(); // Adds the new last number on the stack to temp variable
			math.pop_back(); // Removes the new last number from the stack
			math.push_back(temp); // Places the sum of those two previous numbers into the back of the stack
		}
		
		else if(inp == "-") // User wants Subtraction
		{
			temp2 = math.back(); // Copies the last number in the stack to variable temp2
			math.pop_back(); // Removes the last number from the stack
			temp = math.back(); // Copies the last variable in the stack to variable temp
			math.pop_back(); // Removes the last number from the stack
			temp = temp - temp2; // Subtracts the two temp variables in the proper order
			math.push_back(temp); // Places the difference of those two numbers into the back of the stack
		}
		
		else if(inp == "*") // User wants Multiplication
		{
			temp = math.back(); // Copies the last number in the stack to variable temp
			math.pop_back(); // Removes the last number from the stack
			temp = temp * math.back(); // Multiplies the new last number on the stack with the temp variable
			math.pop_back(); // Removes the last number from the stack
			math.push_back(temp); // Places the product of those two numbers into the back of the stack
		}
		
		else if(inp == "/") // User wants Division
		{
			temp2 = math.back(); // Copies the last number in the stack to variable temp2
			math.pop_back(); // Removes the last number from the stack
			temp = math.back(); // Copies the last variable in the stack to variable temp
			math.pop_back(); // Removes the last number from the stack
			temp = temp / temp2; // Divides the two temp variables in the proper order
			math.push_back(temp); // Places the division of those two numbers onto the back of the stack
		}
		
		else if(inp != "done") // Ensures that when the user wants to stop calculating things, the loop is exited cleanly
		{
			converted = strtol(inp.c_str(), &end, 10); // Converts the user's string to an int
			math.push_back(converted); // Places that converted number onto the back of the stack			
		}
	}
	
	cout << "Last number on the stack: " << math.back(); // Prints the last number on the stack (aka the answer)
	
	return 0;
}