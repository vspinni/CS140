#include <iostream>
#include <string>
#include <cstdio>
#include <vector>

/*	 vflip.cpp
	Venkata Shravan Pinni
	September 9, 2019

	This program takes a pgm file through standard input
	and returns it flipped vertically as a pgm file.
	
*/

using namespace std;

int main (){

	//Declaring and inputting variables.
	string type;
	int rows=0, columns=0,temp=0, number = 0;
	cin >> type >> columns >> rows;
	
	//Error checking for the P2 at the start of the file.
	if(type != "P2"){
		cerr << "Bad PGM file -- first word is not P2"<< endl;
		return -1;
	}

	//Error checking for valid rows and columns.
	if(rows <= 0){
		cerr << "Bad PGM file -- No row specification" << endl;
		return -1;
	}
	if(columns <=0){
		cerr << "Bad PGM file -- No column specification" << endl;
		return -1;
	}

	//Finding total number of pixels and creating an array for them.
	int pixels = rows * columns;
	int array [pixels];

	//Error checking for the 255 after the rows and columns.
	cin >> temp;
	if(temp != 255){
		cerr << "Bad PGM file -- No 255 following the rows and columns" << endl;
		return -1;
	}

	//For loop to check and store every pixel.
	for (int i=0;i<pixels;i++){	
			cin >> temp;
			
			//Error checking for the validity of each pixel.
			if(temp >255 || temp < 0||cin.fail()){
				cerr << "Bad PGM file -- pixel " << number << " is not a number between 0 and 255" << endl;
				return -1;
			}

			array[i] = temp;			
			number++;
	} 

	//Error checking for stuff after the pixels in the input.
	if(cin >> type){
		cerr << "Bad PGM file -- Extra stuff after the pixels"<<endl;
		return -1;
	}

	//Printing the output pgm file in proper format.
	cout << "P2\n";
	cout << columns << " "<< rows<<endl;
	cout<< "255\n";

	//For loop that prints the input pgm file vertically flipped.
	for(int i =rows;i>0;i--){
		for (int j = columns-1;j>=0;j--){
			
			/*For the output expression I drew a sample output on paper
			 and figured out what I would need to do to have the 
			 pixels swapped properly for a vertical flip. */
			cout << array[columns*i-j-1]<<endl;
		}
	}

	return 0;
}


