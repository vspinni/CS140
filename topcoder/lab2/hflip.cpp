#include <iostream>
#include <string>
#include <cstdio>
#include <vector>

/*	 hflip.cpp
	Venkata Shravan Pinni
	September 9, 2019

	This program takes an input of a pgm file from standard
	input and returns a pgm file of it flipped horizontally.
 */

using namespace std;

int main (){

	//Declaring and inputting variables.
	string type;
	int rows=0, columns=0,temp=0, number = 0;
	cin >> type >> columns >> rows;

	//Error checking for the P2 at the start of the pgm file.
	if(type != "P2"){
		cerr << "Bad PGM file -- first word is not P2"<< endl;
		return -1;
	}

	//Error checking for valid row and column inputs.
	if(rows <= 0){
		cerr << "Bad PGM file -- No row specification" << endl;
		return -1;
	}
	if(columns <= 0){
		cerr << "Bad PGM file -- No column specification" << endl;
		return -1;
	}

	//Calculating the total number of pixels and creating an array to store them.
	int pixels = rows * columns;
	int array [rows][columns];
	
	//Error checking for the 255 that follows the columns and rows.
	cin >> temp;
	if(temp != 255){
		cerr << "Bad PGM file -- No 255 following the rows and columns" << endl;
		return -1;
	}

	//Checking every pixel and inputting it into the array.
	for (int i=0;i<rows;i++){	
		for(int j=0;j<columns;j++){

			cin >> temp;

			//Error checking for invalid pixels.
			if(temp >255 || temp < 0||cin.fail()){
				cerr << "Bad PGM file -- pixel " << number << " is not a number between 0 and 255" << endl;
				return -1;
			}
			array[i][j] = temp;			
			number++;
		}
	} 

	//Error checking for stuff after the end of the pixels.
	if(cin >> type){
		cerr << "Bad PGM file -- Extra stuff after the pixels"<<endl;
		return -1;
	}

	//Returning the flipped picture as a proper pgm file.
	cout << "P2\n";
	cout << columns << " "<< rows<<endl;
	cout<< "255\n";

	//Outputting the pgm file flipped horizontally.
	for(int i =0;i<rows;i++){
		for (int j=columns-1;j>=0;j--){

			cout << array[i][j] << endl;
		}
	}

	return 0;
}

