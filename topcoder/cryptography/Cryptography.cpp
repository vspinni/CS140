#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class Cryptography {
  public:
    long long encrypt(vector <int> numbers);
};

long long Cryptography::encrypt(vector <int> numbers)
{
	int smallest = numbers.at(0);
	long long product = 1;
	int index = 0;
	for(int i=0;i<numbers.size();i++){
		if(numbers.at(i)<smallest){
			smallest = numbers.at(i);
			index = i;
		}
	}
	numbers.at(index)= numbers.at(index) + 1;
	for(int j= 0;j<numbers.size();j++){
	
		product *=numbers.at(j); 
	}

	return product;

}
