//Shravan Pinni
//11/6/19
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>

/*enum.cpp Lab9
 *Shravan Pinni
 *This program takes in a given input of length and
 *number of ones and prints out all possible enumerations
 *that fits those specifications.
 */

using namespace std;

//Prototype.
void do_enumeration(string &s, int index, int n_ones);

//Main.
int main(int argc, char **argv){

	//Error echking.
	if (argc !=3) return 0;

	//Declaring variables.
	string dashes;
	stringstream ss;
	int length, ones;

	//Puts in all of the variables using a string stream.
	ss << argv[1];
	ss >> length;
	ss.clear();
	ss << argv[2];
	ss >> ones;

	//Makes a string of specified length with dashes.
	for (int i  = 0; i < length; i++) dashes+= "-";

	//Enumeration function call.
	do_enumeration(dashes,0,ones);

	return 0;
}

//Enumeration function.
void do_enumeration(string &s, int index, int n_ones){


	//Base case: fill up string aka index = length
	if (index == (int)s.length()){ 
		//If the number of ones left to input is 0 prints out the string.
		if (n_ones==0)
			cout << s << endl;
		return;
	}else{

		//Adds 0s until you must add 1s
		if (n_ones + index <(int)s.length()){
			s[index] = '0';//0 or 1
			//Moves to next index.
			do_enumeration(s, index+1,n_ones);
		}

		//Adds 1s until string is full
		if(n_ones>=0){
			s[index] = '1';
			//Moves to next index and decreases one count.
			do_enumeration(s, index +1,n_ones-1);
		}
	}
}

