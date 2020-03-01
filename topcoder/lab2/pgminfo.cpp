#include <iostream>
#include <string>
#include <cstdio>
#include <vector>

/*	 pgminfo.cpp
	Venkata Shravan Pinni
	September 9, 2019

	This program takes in an input of a pgm file and returns
	the number of rows, columns, pixels, and the average pixel
	value.
 */

using namespace std;

int main (){

	//Declaring variables and putting values into them.
	string type;
	int rows=0, columns=0,temp=0, number = 0;
	double avgpix=0;
	cin >> type >> columns >> rows;
	
	//Error checking for not having P2 at the start of file.
	if(type != "P2"){
		cerr << "Bad PGM file -- first word is not P2"<< endl;
		return -1;
	}

	//Error checking for having invalid rows or columns.
	if(rows <= 0){
		cerr << "Bad PGM file -- No row specification" << endl;
		return -1;
	}
	if(columns <= 0){
		cerr << "Bad PGM file -- No column specification" << endl;
		return -1;
	}

	//Calculating total number of pixels.
	int pixels = rows * columns;
	
	//Inputting and error checking the 255 following the columns and rows.
	cin >> temp;
	if(temp != 255){
		cerr << "Bad PGM file -- No 255 following the rows and columns" << endl;
		return -1;
	}

	//going through and checking the validity of every pixel and setting up avgpix.
	for (int i=0;i < pixels;i++){	
		cin >> temp;

		//Error checking for a pixel value that is out of the value range.
		if(temp >255 || temp < 0||cin.fail()){
			cerr << "Bad PGM file -- pixel " << number << " is not a number between 0 and 255" << endl;
			return -1;
		}
		number++;
		avgpix += temp;
	}

	//Error checking for extra input after pixels.
	if(cin >> type){
		cerr << "Bad PGM file -- Extra stuff after the pixels"<<endl;
		return -1;
	}

	//Calculating average pixel value.
	avgpix /=pixels;

	//Printing the Rows, Columns, Pixels, and Average Pixel Value.
	printf("# Rows: %11d\n",rows);
	printf("# Columns: %8d\n",columns);
	printf("# Pixels: %9d\n",pixels);
	printf("Avg Pixel: %8.3f\n", avgpix);
	
	return 0;
}
