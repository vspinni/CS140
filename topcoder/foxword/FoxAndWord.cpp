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

class FoxAndWord {
  public:
    int howManyPairs(vector <string> words);
};

int FoxAndWord::howManyPairs(vector <string> words)
{
	int count = 0;
	string a, b;

	for(int i = 0;i<words.size()-1;i++){
		for(int j=0;j<words[i].size()-1;j++){

			a=words[i].substr(0,j);
			b=words[i+1].substr(words[i+1].size-j-1,j);
			if(a==b){
				count++;
			}
		}
	}
	return count;
}
