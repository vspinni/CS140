//Shravan Pinni
//8-28-19
//CS 140 Dr. Planck
//Lab 0

#include <iostream>

using namespace std;

int main() {

	int ounces = 0;
	char c;
	int n;

	while (cin >> c){
	
		if(c >='A'){
			ounces=ounces + c - 'A' +1;
		}
	}
	cout << ounces << endl;
}
