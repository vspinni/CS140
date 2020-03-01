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

class FauxPalindromes {
  public:
    string classifyIt(string word);
};

bool isItP(string s){
	
	for (int i=0;i<s.size()/2;i++){
		if(s[i]!=s[s.size()-1-i]){
			return false;
		}
	}
	return true;
}

string FauxPalindromes::classifyIt(string w)
{

	if(isItP(w))
		return ("PALINDROME");
	
		char c;
		string faux;
	for (int i =0;i<w.size();i++){
		if(w[i] != c){
			faux.push_back(w[i]);
			c=w[i];
		}
	}

	if(isItP(faux))
	return "FAUX";

	return "NOT EVEN FAUX";

}
