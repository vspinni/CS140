#include <iostream>

/* moonglow.cpp
	Venkata Shravan Pinni
	August 31,2019

	This program returns a checkerboard that is made from
	inputs of rows, columns, width, a starting character, 
	and cycle lengths. */

using namespace std;

int main (){

/*Variables for the inputs as well as the current character,
  the row offset, and the column count are declared here. 
  The current variable is for finding where the character is
  in the current cycle. The offset is for the cycle offset 
  going from row to row. The count is for deciding where in the 
  current cycle it is from column to column*/ 
	int rows, columns, cycle, width=0;
	char sc, current;
	int offset,count =  0;

//error checking for not enough inputs
	if(!(cin >> rows >> columns >> sc >> cycle >> width)){	
		cerr << "usage: checkerboard  - stdin should contain R, C, SC, CS and W"<<endl;
		return 0;
	}

//error checking for variables being inputted to 0
	if(rows==0 || columns==0|| sc==0||cycle==0||width==0)
		return 0;

//error checking for a starting character + cycle that goes over 127
	if(sc+cycle > 127)
		return 0;
		
/*the first for loop is for the rows and this is where the current
  character is set up */	
	for (int i=0; i<rows; i++){

		current = sc;
//the second for loop is for the repeating rows due to the width
		for (int k=0; k<width; k++){

/*the third for loop is for the columns and this is where the count
  is changed from character to character*/
			for(int j=0; j<columns; j++){

/*the fourth for loop is for the repeating columns due to the width
  and is where the actual printing occurs*/
				for (int l=0;l<width;l++){
					cout << (char)(current + count);
				}
/*the count is incremented and modded with the cycle here to switch
  characters*/
				count++;
				count = count % cycle;
			}	
/*the cout here creates the rows and the count is set to the offset
 for the new row*/
			cout << endl;
			count = offset;

		}
/*the offset is incremented here so that the row starts properly
  and the count is reset to the new offset*/
		offset++;
		offset= offset % cycle;
		count = offset;

	}		
	return 0;
		
}
