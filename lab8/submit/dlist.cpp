//Shravan Pinni
//11/4/19

#include <iostream>
#include "dlist.hpp"

/*dlist.cpp Lab8
 *Shravan Pinni
 *This program implements the functions in the 
 *dlist class that is declared by the provided 
 *dlist.hpp header file.
 */

using namespace std;

//Constructor.
Dlist::Dlist(){

	//Allocates new memory, initializes front and back pointers, sets size to zero.
	sentinel = new Dnode;
	size = 0;
	sentinel -> flink = sentinel;
	sentinel -> blink = sentinel;
}

//Copy constructor using the overloaded =.
Dlist::Dlist(const Dlist &d){
	*this = d;	
}

//Overloading the = operator to set dlists equal.
Dlist& Dlist::operator= (const Dlist &d){
	//Clears the current list.
	Dnode *i;	
	Clear();

	//makes a new sentinel for the current list.
	sentinel = new Dnode();
	sentinel->flink = sentinel;
	sentinel->blink = sentinel;
	
	//Pushes back the values from the provided list into the new list.
	for (i  = d.Begin(); i != d.End(); i = i -> flink){
		Push_Back(i -> s);
	}
	return *this;	
}

//Destructor. Clears the Dlist and deletes the sentinel.
Dlist::~Dlist(){
	Clear();
	delete sentinel;
}

//Uses Pop_Front to delete all of the elements in the dlist.
void Dlist:: Clear(){	
	while (size != 0){
		Pop_Front();
	}
}      

//Checks if the size is 0 or not of the dlist.
bool Dlist::Empty() const{
	if (size==0)
		return true;
	else
		return false;
}

//Returns the size of the dlist.
size_t Dlist:: Size() const{
	return size;
}

//Inserting after the sentinel pushes the addition in the front.
void Dlist::Push_Front(const std::string &s){
	Insert_After(s,sentinel);
}

//Inserting before the sentinel pushes the addition to the end.
void Dlist::Push_Back(const std::string &s){
	Insert_Before(s,sentinel);		
} 

//Returns the string in the front and erases the associated dnode.
string Dlist::Pop_Front(){
	//Stores the string to return.
	string s = sentinel -> flink -> s;
	
	//Erases the front dnode.
	Erase(sentinel -> flink);
	return s;
}

//Returns the string in the back and erases the associated dnode.
string Dlist::Pop_Back(){
	//Stores the string to return.
	string s = sentinel -> blink -> s;
	
	//Erases the last dnode. 
	Erase(sentinel -> blink);
	return s;
}

//Returns the first dnode.
Dnode* Dlist::Begin() const{
	return sentinel -> flink;
}

//Returns the sentinel because it marks the end.
Dnode* Dlist::End() const{
	return sentinel;
}  

//Returns the last dnode.
Dnode* Dlist::Rbegin() const{
	return sentinel -> blink;
}   

//Returns the sentinel because it marks the reverse end.
Dnode* Dlist::Rend() const{
	return sentinel;
} 

//Inserts a new dnode with a given string into the Dlist.
void Dlist::Insert_Before(const std::string &s, Dnode *n){

	//Allocates space for a new dnode and sets the string value.
	Dnode *d = new Dnode;
	d -> s = s;
	
	//Sets the new dnode's back to the back of the dnode it is before.
	d -> blink  = n -> blink;

	//Sets the given dnode's back to the inserted dnode.
	n -> blink -> flink  = d;

	//Sets the new dnode's front to the given dnode.
	d -> flink = n;

	//Sets the given dnode's back to the new dnode.
	n -> blink = d;

	//Incrementing dlist size.
	size++;
}

//Inserting before the dnode after the given dnode is inserting after n.
void Dlist::Insert_After(const std::string &s, Dnode *n){	
	Insert_Before(s,n->flink);
}

//Erases a given dnode from the dlist.
void Dlist::Erase(Dnode *n){
	//Only erases if the size is greater than 0.
	if (size>0){

		//Sets the front of the dnode behind n to the dnode infront of n.
		n -> blink -> flink = n -> flink;

		//Sets the behind of the dnode in front of n to the dnode behind n.
		n -> flink -> blink = n -> blink;

		//Deletes n and decrements the size.
		delete n;
		size--;
	}		
}

