//Shravan Pinni
//October 22, 2019

#include <fraction.hpp>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

/*keno.cpp Lab 6
 *Venkata Shravan Pinni
  This file uses the functions in the fraction class
 declared in the header fraction.hpp and defined in the
 fraction.cpp file to calculate protential returns for the 
 betting game keno. 
  */

int main (){
	
	double bet, tempd, expected,normal;
	int temp, balls;
	vector <int> cat;
	vector <double> payout;
	vector <double> prob;
	vector <double> ret;
	Fraction chance;	

	//Inputting variables.
	cin >> bet >> balls;
	expected = 0-bet;
	
	while(cin >> temp){
		
		//Pushes the catches and payouts into vectors.
		cat.push_back(temp);
		cin.clear();

		cin >> tempd;
		payout.push_back(tempd);
		cin.clear();
	}
	
	//Printing Bet and Balls.
	printf("Bet: %0.2f\n", bet);
	cout << "Balls Picked: " << balls << endl;


	for (unsigned int i = 0; i < cat.size();i++){
		
		//Calculates the probability. 
		chance.Multiply_Binom(80-balls,20-cat[i]);
		chance.Multiply_Binom(balls,cat[i]);
		chance.Divide_Binom(80,20);
		
		//Pushes back probability and returns into vectors.
		prob.push_back(chance.Calculate_Product());
		ret.push_back(prob[i] * payout[i]);
		
		//Output.
		cout << "  Probability of catching " << cat[i] << " of " << balls << ": " << prob[i] << 
		" -- Expected return: " << ret[i] << endl;
		expected += ret[i];
		
		//Clears fraction for reuse. 
		chance.Clear();
	}	
	
	//Calculating the normalized.
	normal = expected / bet;	
	
	//Outputting return per bet and normalized.
	printf("Your return per bet: %0.2f\n", expected);
	printf("Normalized: %0.2f\n", normal); 
	
	return 0;
}


