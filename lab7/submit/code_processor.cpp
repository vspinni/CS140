//Shravan Pinni
//10/28/19

#include "code_processor.hpp"
#include <iostream>
#include <cstdio>
#include <fstream>
/*code_processor.cpp Lab 6
 *Shravan Pinni
 This file implemented the functions declared in
 code_processor.hpp. The program is supposed to
 take in values of users, phones, and codes and
 manipulate them in maps and sets. In terms of the
 user experience, its like an online  point and 
 prize tracker at an arcade.
 */


using namespace std;

//Adds a new prize to the prize map with the given information.
bool Code_Processor::New_Prize(const std::string &id, const std::string &description, int points, int quantity){

	//Error checking.
	if(Prizes.find(id) != Prizes.end())
		return false;	
	if (points <= 0)
		return false;
	if (quantity <=0)
		return false;	

	//Making new prize pointer and setting values.
	Prize *p = new Prize;
	p -> id = id;
	p -> description = description;
	p -> points = points;
	p -> quantity =  quantity;
	
	//Adding it to the prize map.
	Prizes[id] = p;

	return true;
}

//Adds a new user to the Names map with the given information.
bool Code_Processor::New_User(const std::string &username, const std::string &realname, int starting_points){

	//Error checking.
	if(Names.find(username) != Names.end())
		return false;
	if (starting_points < 0)
		return false;

	//Making a new User pointer and initializing values.
	User *u = new User();
	u -> username = username;
	u -> realname = realname;
	u -> points = starting_points;
	
	//Adding it the the Names map.
	Names.insert(make_pair<string, User*>(username, u));

	return true;
}

//Deletes a user from the Names map.
bool Code_Processor::Delete_User(const std::string &username){

	//Error checking.
	if (Names.find(username) == Names.end())
		return false;
	

	set<string>::iterator it;
	set<string>::iterator end;
	end = Names[username]->phone_numbers.end();

	//Removes all the phones from the user being deleted.
	for (it = Names.find(username) -> second -> phone_numbers.begin(); it != end; it++){
		Remove_Phone(username, (*it) );
	}

	//Deletes the user from the map and deletes the associated memory.
	User *tmp = Names.find(username) -> second;
	Names.erase(username);
	delete tmp;

	return true;
}

//Adds a phone to a specified user in the user info and the Phones map.
bool Code_Processor::Add_Phone(const std::string &username, const std::string &phone){

	//Error checking.
	if (Names.find(username) == Names.end())
		return false;
	if (Phones.find(phone) != Phones.end())
		return false;

	//Adds it to the two different locations it should be in.
	Names.find(username)->second -> phone_numbers.insert(phone);	
	Phones.insert(make_pair<string, User *>(phone,Names.find(username)->second));

	return true;
}

//Removes a phone from a user's phone set and the Phones map.
bool Code_Processor::Remove_Phone(const std::string &username, const std::string &phone){

	//Error checking.
	if (Names.find(username) == Names.end())
		return false;
	if (Phones.find(phone) ==Phones.end())
		return false;	
	if (Phones.find(phone) -> second -> username != username)
		return false;

	//Removes the phone from the map and the set within the user's data.
	Phones.erase(phone);
	Names.find(username) -> second -> phone_numbers.erase(phone);

	return true;
}

//Returns all of the phones that a user has registered.
string Code_Processor::Show_Phones(const std::string &username) const{

	//Error checking.
	if (Names.find(username) == Names.end())
		return "BAD USER";
	if (Names.find(username) -> second -> phone_numbers.empty())
		return "";

	set  <string> :: const_iterator itr;
	string phone;
	User *temp = Names.find(username)->second;

	//Adds all the phone numbers the user has to the return.
	for (itr = temp -> phone_numbers.begin();itr != temp -> phone_numbers.end();itr++){
		phone += *itr;
		phone += "\n";
	}
	
	return phone;
}

//Djb hash function from Dr.Plank's lecture.
unsigned int djb_hash(const string &s)
{
	size_t i;
	unsigned int h;
	  
	h = 5381;

	for (i = 0; i < s.size(); i++) {
	    h = (h << 5) + h + s[i];
	 }
	 return h;
}

//Adds a code to the Codes set and adds the proper points to the user's points.
int Code_Processor::Enter_Code(const std::string &username, const std::string &code){

	//Error checking.
	if (Names.find(username) ==Names.end())
		return -1;	
	if (Codes.find(code) != Codes.end())
		return -1;
	if ((djb_hash(code) % 17 != 0) && (djb_hash(code) % 13)!=0)
		return 0;
	int pointsadd = 0;

	//Checks the points value and adds it.
	if (djb_hash(code) % 17==0){
		Names.find(username) -> second -> points += 10;
		pointsadd = 10;
	}else{
		Names.find(username) -> second -> points += 3;
		pointsadd = 3;
	}

	//Adds the code to the Codes set and returns the points.	
	Mark_Code_Used(code);
	return pointsadd;
}

//Adds a code to a user by an associated phone number.
int Code_Processor::Text_Code(const std::string &phone, const std::string &code){

	//Error checking.
	if (Phones.find(phone) == Phones.end())
		return -1;
	if (Codes.find(code) != Codes.end())
		return -1;
	if ((djb_hash(code) % 17 != 0) && (djb_hash(code) % 13)!=0)
		return 0;

	int pointsadd = 0;


	//Checking points value.
	if (djb_hash(code) % 17==0)
		pointsadd = 10;
	else
		pointsadd = 3;
	
	//Adding code to Codes set, adds the points to the user and returns points. 
	Mark_Code_Used(code);
	Phones.find(phone) -> second -> points +=pointsadd;

	return pointsadd;
}

//Adds a code to the Codes set.
bool Code_Processor::Mark_Code_Used(const std::string &code){

	//Error checking.
	if (Codes.find(code) != Codes.end())
		return false;
	if ((djb_hash(code) % 17 != 0) && (djb_hash(code) % 13)!=0)
		return false;
	
	//Adds code to the Codes set.
	Codes.insert (code);
	return true;
}

//Returns the user's point balance.
int Code_Processor::Balance(const std::string &username) const{
	
	//Error checking.
	if (Names.find(username) == Names.end())
		return -1;
	
	//Gets and return's the user's points.
	int current = 0;
	current = Names.find(username) -> second -> points;

	return current;
}

//Redeems a prize using the user's points if able.
bool Code_Processor::Redeem_Prize(const std::string &username, const std::string &prize){
	
	//Error checking.
	if (Names.find(username) == Names.end())
		return false;
	if (Prizes.find(prize) == Prizes.end())
		return false;
	if (Names.find(username) -> second -> points < Prizes.find(prize) -> second -> points)
		return false;

	//Subtracts prize points from the user's points.
	Names.find(username) -> second -> points -= Prizes.find(prize) -> second -> points;

	//Subtracts the prize's quantity by 1 and deletes it if it hits 0.
	Prizes.find(prize) -> second -> quantity--;
	if (Prizes.find(prize) -> second -> quantity ==0){
		delete Prizes.find(prize)->second;
		Prizes.erase(prize);
	}

	return true;
}

//Deconstructor.
Code_Processor::~Code_Processor(){

	map <string, User *> :: const_iterator itr;
	map <string, Prize *> :: const_iterator it;

	//Deletes all the space from the maps.
	for (itr  = Names.begin(); itr != Names.end();itr++){
		delete itr -> second;
	}
	for (it = Prizes.begin();it != Prizes.end(); it++){
		delete it ->second;
	}

}

//Writes the proper output to the given file.
bool Code_Processor::Write(const std::string &filename) const{
	
	ofstream of;
	of.open(filename.c_str());
	
	//Error checking.
	if (of.fail())
		return false;

	map <string, Prize *> :: const_iterator itr;
	map <string, User *> :: const_iterator it;
	set <string> ::const_iterator iter;

	//Printing the commands and changes made to prizes.
	for (itr = Prizes.begin();itr != Prizes.end();itr++){
		of << "PRIZE     " << itr -> second -> id.c_str() << "    " << itr -> second -> points << "    "
			<< itr -> second -> quantity << "    " << itr -> second -> description.c_str() << endl; 
	
	}

	//Printing commands and changes made to users.
	for (it = Names.begin();it != Names.end();it++){
		of << "ADD_USER     " << it -> second -> username.c_str() << "    " << it -> second -> points << "    "
			<< it -> second -> realname.c_str() << endl;	
	}
	
	//Printing the commands and changes made to phones.
	for (it = Phones.begin();it != Phones.end();it++){ 
		of << "ADD_PHONE     " << it -> second -> username.c_str() << "    " << it -> first.c_str() << endl; 
	}

	//Printing the codes that have been used.
	for (iter = Codes.begin();iter != Codes.end();iter++){
		of <<"MARK_USED     " <<  *iter << endl;
	
	}

	of.close();
	return true;;
}
