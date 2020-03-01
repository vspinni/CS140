//Shravan Pinni
//October 22, 2019

#include "fraction.hpp"
#include <cstdio>
#include <iostream>
#include <set>

using namespace std;

/*fraction.cpp Lab 6
 *  *Venkata Shravan Pinni
 *  This file defines the functions provided in 
 *  fraction.hpp.
 *        */

//Sets the fraction to 1 by clearing the 2 multisets and putting 1 into the numerator.
void Fraction::Clear(){
	numerator.clear();
	denominator.clear();
	numerator.insert(1);
}

//Puts n into numerator.
bool Fraction::Multiply_Number (int n){

	//Error checking.
	if (n <=0) return false;
	if (n==1) return true;

	multiset <int> ::iterator itr;

	//Checks if n is in the denominator.If so, deletes it and if not adds n to numerator.
	itr = denominator.find(n);

	if(itr == denominator.end())
		numerator.insert(n);
	else
		denominator.erase(itr);
	
	return true;
}

//Puts n into denominator.
bool Fraction::Divide_Number(int n){
	
	//Error Checking.
	if (n <=0) return false;
	if (n==1) return true;

	multiset <int> ::iterator itr;
	
	//Checks if n is in the numerator. If so, deletes it and if not adds it to the denominator.
	itr = numerator.find(n);

	if(itr == numerator.end())
		denominator.insert(n);
	else
		numerator.erase(itr);
	
	return true;
}

//Puts factorial of n into numerator.
bool Fraction::Multiply_Factorial (int n){

	//Error Checking.
	if (n <=0) return false;

	//Adds into numerator starting from 2 because 0 and 1 don't go in factorial.
	for (int i = 2; i <= n;i++){
		Multiply_Number(i);
	}
	
	return true;
}

//Puts factorial of n into denominator.
bool Fraction::Divide_Factorial (int n){

	//Error Checking.
	if (n <=0) return false;

	//Adds into denominator starting from 2 because 0 and 2 don't go into factorial.
	for (int i = 2; i <= n;i++){
		Divide_Number(i);
		
	}
	return true;
}

//Puts binomial into fraction.
bool Fraction::Multiply_Binom (int n, int k){
	if (n<=0 || k>n || k<0) return false;
	
	//Puts numerator of binomial into numerator.
	Multiply_Factorial(n);
	
	//Puts denominator of binomial into denominator.
	Divide_Factorial(k);
	Divide_Factorial(n-k);
	
	return true;
}

//Puts reciprocal binomial into fraction.
bool Fraction::Divide_Binom (int n, int k){
	if (n<=0 || k>n || k<0) return false;

	//Puts numerator of binomial into denominator.
	Divide_Factorial(n);

	//Puts denominator of binomial into numerator.
	Multiply_Factorial(k);
	Multiply_Factorial(n-k);

	return true;
}

//Switches numerator and denominator.
void Fraction::Invert(){
	numerator.swap(denominator);
}

//Prints the fraction in proper format.
void Fraction::Print() const{
	
	multiset <int> ::iterator itr;

	//Checks for nothing in the numerator.
	if (numerator.size() ==0){
		cout << "1";
	}
	//Otherwise
	else{
		//Goes through numerator and puts in proper * and spaces.	
		for (itr = numerator.begin(); itr != numerator.end();itr++){
			cout << *itr;
			
			//Checking for the end of numerator so space and * not wanted.
			itr++;
			if (itr != numerator.end())
				cout << " * ";	
			itr--;
		}		
	}

	//Checks denominator for nothing and does nothing.
	if (denominator.size() == 0)
	{}
	//Otherwise
	else{
		cout << " / ";	
		//Goes through denominator and puts in proper / and spaces.
		for (itr = denominator.begin(); itr != denominator.end();itr++){
			cout << *itr;
			
			//Checking for the end of the denominator so space and / not wanted.
			itr++;
			if (itr != denominator.end())
				cout << " / ";
			itr--;
			}
	}
	//End line after printing.
	cout << endl;
}

//Calculates product by multipying numerator and dividing denominator.
double Fraction::Calculate_Product() const{
	double product = 1;		
	multiset <int> ::iterator itr;
	
	for (itr = numerator.begin();itr != numerator.end();itr++)
		product *= *itr;

	for (itr = denominator.begin();itr != denominator.end();itr++)
		product /= *itr;

	return product;		
}




