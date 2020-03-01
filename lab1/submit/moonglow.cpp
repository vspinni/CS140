#include <iostream>
#include <string>

/* moonglow.cpp
	Venkata Shravan Pinni
	August 31, 2019

	This program sorts through information in a file and 
	helps the teacher grade by returning the student's
	name and score.
 */

using namespace std;

int main (){

/*Declaring doubles for the score, a counter for the 
  current average, a variable for the current average, 
  and a temporary number for cin */

	double score = 0;
	double count = 0;
	double average = 0;
	double tempNum = 0;

//declaring variables for a temporary string and the name
	string tempStr;
	string name;

//while loop that continues as long as the file hasn't ended
	while(!(cin.eof())){		
	
/*while loop that adds to the score as long as the 
  current input is a lone number */
		while(cin >> tempNum){
			score += tempNum;
		}
/*when the while loop is exited, it means that there is a 
  non number so I clear cin and then put it into a string */
			cin.clear();
			cin >> tempStr;

//if the cin is name I load the next input into name
			if(tempStr == "NAME"){
				cin >> name;
			}
/*if the cin is average I start up the average counter if 
  the next input is a number and then add the average to the score
  otherwise I clear the cin and move on */
			else if(tempStr == "AVERAGE"){
				while(cin >> tempNum){
					average += tempNum;
					count++;
				}	
				cin.clear();

				if(count > 0){
					average /= count;
					count = 0;
					score += average;
					average = 0;
				}	
			}
			else{}
	}
//print the student's name and score at the end
	cout << name << " " << score << endl;

	return 0;
}

