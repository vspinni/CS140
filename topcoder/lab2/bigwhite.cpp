#include <iostream>
#include <string>
#include <cstdio>
#include <stdlib.h>
#include <vector>

/*	 bigwhite.cpp
	Venkata Shravan Pinni
	September 9, 2019

	This program takes command line inputs of rows and 
	columns and outputs a full white pgm file that fits
	the inputs.
 */

using namespace std;

int main (int argc, char* argv[]){

	//Error checking for improper number of arguments given.
	if(argc !=3){
		cerr << "usage: bigwhite rows cols"<< endl;
		return -1;
	}

	//Declaring rows and columns and inputting values into them.
	int rows=0, columns = 0;
	rows = atoi(argv[1]);
	columns = atoi(argv[2]);

	//Error checking for valid row and column inputs.
	if(rows <1 || columns <1){
		cerr << "usage: bigwhite rows cols"<< endl;
		return -1;
	}

	//Outputs the resulting pgm file in the proper format.
	cout << "P2\n";
	cout << columns << " "<< rows<<endl;
	cout<< "255\n";
	for(int i =0; i<rows;i++){
		for(int j =0; j<columns;j++){
			cout << "255" << endl;
		}
	}

	return 0;
}
