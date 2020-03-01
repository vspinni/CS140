#include "hash_140.hpp"
#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

/*	hash_140.cpp		
	Venkata Shravan Pinni
	September 24, 2019

	This program sets up and applies a hash table that
	uses XOR and Last7 functions and the collision strategies
	of Linear probing and Double Hashing. */

//Prototypes.
int Xor (const string key,int table_size);
int Last7 (const string key, int table_size);

//Function that sets up the hash table.
string Hash_140::Set_Up(size_t table_size, const std::string &fxn, const std::string &collision)
{

	//Error checking.
	if ((Keys.size()!=0) || Vals.size()!=0)
		return "Hash table already set up";
	
	if(table_size <=0)
		return "Bad table size";
	
	if((fxn != "XOR") && (fxn != "Last7"))
		return "Bad hash function";

	if((collision != "Linear") && (collision != "Double"))
		return "Bad collision resolution strategy";

	//Setting up table, function, and strategy.
	Keys.resize(table_size,"");
	Vals.resize(table_size,"");

	//Error checking
	if(fxn == "XOR")
		Fxn = 0;
	else 
		Fxn = 1;
	
	if(collision == "Linear")
		Coll = 'L';
	else 
		Coll = 'D';
	
		return "";			
}

//Function that adds values to the hash table.
string Hash_140::Add(const string &key, const string &val)
{
	//Error checking.
	if ((Keys.size()==0) ||  Vals.size()==0)
		return "Hash table not set up";	
	if (key == "")
		return "Empty key";


//Checking the proper hex.	
	for (unsigned int i = 0;i<key.size();i++){
		
		char k = key[i];
		//Error checking
		switch (k){
			case '0': break;
			case '1': break;
			case '2': break;
			case '3': break;
			case '4': break;
			case '5': break;
			case '6': break;
			case '7': break;
			case '8': break;
			case '9': break;
			case 'a': break;
			case 'b': break;
			case 'c': break;
			case 'd': break;
			case 'e': break;
			case 'f': break;
			case 'A': break;
			case 'B': break;
			case 'C': break;
			case 'D': break;
			case 'E': break;
			case 'F': break;
			default: return "Bad key (not all hex digits)";		
		}
	}

//More error checking.
	if (val == "")
		return "Empty val";
	int spaces = 0;
	for (unsigned int i  = 0; i < Keys.size();i++){
		if (Keys[i] ==""){
			spaces++;	
		}
	}
	if (spaces == 0)
		return "Hash table full";

//One index for the first hash, one for 2nd, one for combined index;
	int index = 0;
	int index2 = 0;
	int newIndex = 0;
	
	//Last 7.
	if (Fxn == 1){
		//Last7 and Linear.
		if (Coll == 'L'){
			index = Last7 (key, Keys.size());
			//Making sure that the searching continues until a space is found.
			while (Keys[index] != ""){
				//Incrementing by one and modding to go back around.
				index = (index + 1) % Keys.size();	
				//Error checking.
				if (key == Keys[index])
					return "Key already in the table";
			}
			newIndex = index;
		
		//Last7 and Double.	
		}else {
			int count = 0;			
			//Calculating both for Double Hashing.
			index = Last7 (key, Keys.size());
			index2 = Xor(key, Keys.size());
			if (index2 ==0 )
				index2 = 1;
		
			//Calculating new index.
			newIndex = (index + (count * index2)) % Keys.size();
			//Making sure that the probing continues while possible.
			while (Keys[newIndex] != ""){			
				newIndex = (index + (index2 * count)) % Keys.size();
				
				//Error checking.
				if (count >= (int)Keys.size())
					return "Cannot insert key";
				if (key == Keys[newIndex])
					return "Key already in the table";

				count++;
			}
		}

	//XOR.
	}else{

		//XOR and Linear. Same as above except switched hashes.
		if (Coll == 'L'){

			index = Xor (key, Keys.size());
			//Probe keeps going until a spot is found.	
			while (Keys[index] != ""){
				index = (index +1) % Keys.size();
				index = index % Keys.size();
				if (key == Keys[index])
					return "Key already in the table";
			}
			newIndex = index;
		
		//XOR and Double. Same as above double except switched hashes.
		}else{
			int count = 0;			
			index = Xor(key, Keys.size());
			index2 = Last7(key, Keys.size());
			if (index2 ==0)
				index2 = 1;

			newIndex = (index + (count * index2)) % Keys.size();
			//Probing keeps going until reasonable amount.
			while (Keys[newIndex] != ""){			
				newIndex = (index + (index2 * count)) % Keys.size();
		
				//Error checking.
				if (count >= (int)Keys.size())
					return "Cannot insert key";
				if (key == Keys[newIndex])
					return "Key already in the table";

				count++;
			}
		}		
	}
	//Inputting the keys and vals.
	Keys[newIndex] = key;
	Vals[newIndex] = val;
	return "";
}

//Function that finds out if a given key is in the hash table.
string Hash_140::Find(const string &key)
{

	//Error checking
	if ((Keys.size()==0) ||  Vals.size()==0)
		return "";
	//Same error checking for key as in Add function above.
	for (unsigned int i = 0;i<key.size();i++){

		char k = key[i];
		switch (k){
			case '0': break;
			case '1': break;
			case '2': break;
			case '3': break;
			case '4': break;
			case '5': break;
			case '6': break;
			case '7': break;
			case '8': break;
			case '9': break;
			case 'a': break;
			case 'b': break;
			case 'c': break;
			case 'd': break;
			case 'e': break;
			case 'f': break;
			case 'A': break;
			case 'B': break;
			case 'C': break;
			case 'D': break;
			case 'E': break;
			case 'F': break;
			default: return "";		
		}	
	}
	//Making sure Nprobes is 0.
	Nprobes = 0;
	int index;
	//All of my find is similar to add above except counting 
	//the number of collisions.
	if (Fxn == 1){
		//Find for last7 Linear.
		if (Coll=='L'){
			index = Last7(key,Keys.size());	
			//Searches entire table for key.		
			for (unsigned int i = 0;i<Keys.size();i++){
					
				if (Keys[index] == key)
					return Vals[index];
				
				index = (index + 1) % Keys.size();
				//Incrementing probes.
				Nprobes++;

			}
		}else{
			
			//Find for Last7 Double.
			index = Last7(key, Keys.size());
			int index2 = Xor(key, Keys.size());
			if (index2 == 0)
				index2 =1;
			
			//Searches for key.
			for (unsigned int i  = 0; i < Keys.size(); i++){
				int newIndex = (index + (i * index2)) % Keys.size();
				if (Keys[newIndex] == key){
					return Vals[newIndex];
			   }
				//Incrementing probes.
				Nprobes++;
				
			}
		}	
	}else{
		
		//Find for XOR linear.
		if (Coll =='L'){	
			index = Xor(key,Keys.size());
			//Searches entire table.
			for (unsigned int i  = 0; i< Keys.size();i++){
				
				if (Keys[index] == key)
					return Vals[index];
				
				index =  (index + 1) % Keys.size();
				//Incrementing probes.
				Nprobes++;
			}
		}else{
			
			//Find for XOR Double.
			index = Xor(key, Keys.size());
			int index2 = Last7(key, Keys.size());
			if (index2 == 0)
				index2 = 1;
			//Checks a reasonable number of times.
			for (unsigned int i  = 0; i < Keys.size(); i++){
				int newIndex = ((index + (i * index2)) % Keys.size());
				if (Keys[newIndex] == key)
					return Vals[newIndex];
				//Incrementing nprobes.
				Nprobes++;
			}
		}
	}
	//Sets nprobes to 0 if it couldnt find the key.
	Nprobes = 0;
	return "";
}

//Print function that iterates through and prints existing values.
void Hash_140::Print() const
{
	for (unsigned int i = 0; i < Keys.size();i++){
		if (Keys[i] != "")
			printf ("%5d %s %s\n", i, Keys[i].c_str(), Vals[i].c_str());	
	}
}


//Counts the total collisions in a set of commands.
size_t Hash_140::Total_Probes()
{	
	Nprobes = 0;
	int count = 0;


//Resets Nprobes at each find and adds that count to count.
	for (unsigned int i = 0; i < Keys.size();i++){
		if (Keys[i] != ""){
			Find(Keys[i]);
		count += Nprobes;
		}
	}
	return count;
}

//Function for the last7 hash.
int Last7 (const string key, int table_size){
	
	string keyc = key;
	stringstream ss;
	int index = 0;

	//If the key is less than 8 long, it just uses the key.
	if (key.size()>7)
		keyc = keyc.substr(keyc.size()-7,7);

	ss.str(keyc);
	ss >> hex >> index;
	index = index % table_size;
	return index;
}

//Function for the XOR hash.
int Xor (string key, int table_size){
	
	
	int temp = 0;
	int xsize = key.size()/7;
	//One vector for the segmented strings and one for the ints.
	vector <string> xs;
	vector <int> xi;
	stringstream ss;

	//Cutting the key.
	for(int i = 0; i <xsize; i++)
		xs.push_back(key.substr(i*7,7));
		
		//Getting the last segment if there is one.
		if(key.size() % 7 !=0){
			xs.push_back(key.substr(7*xsize,key.size()%7));
		}
		
		xi.resize(xs.size());

		//Converting and then XORing.
		for (unsigned int i = 0;i<xs.size();i++){
			ss.clear();
			ss.str(xs[i]);
			ss >> hex >> xi[i];
			temp = xi[i] ^ temp;
		}
		//Making sure temp finds in table and returning it.
		temp = temp % table_size;
		return temp;
	}



