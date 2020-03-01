//Shravan Pinni
//Lab A
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include "bstree.hpp"
using namespace std;
using CS140::BSTree;
using CS140::BSTNode;

/*bstree_lab.cpp Lab A
 *Shravan Pinni
 *This program implements the remaining functions in the 
 *BSTree class.
 */

//This function calculates the depth of a given key if it is inside the tree.
int BSTree::Depth(const string &key) const
{
	//Checks if the key is inside the tree.
	if (Find(key) == NULL)
		return -1;
	
	//Declaring variables.
	BSTNode *n;
	int count = 0;
	
	//Sets that the root is right of the sentinel.
	n  = sentinel -> right;
	
	//Keeps going until it finds the key.
	while(key != n -> key){
	
		//If the key is greater goes right and if less goes less..
		if (key > n-> key)
			n  = n -> right;
		else
			n = n -> left;
		
		//Increments depth counter.
		count++;	
	}
	return count;
}

//This function returns the max height of the tree.
int BSTree::Height() const
{
	//Calls recursive height function and returns the value.
	int height = recursive_find_height(sentinel -> right);
	return height;
}

//This function returns the keys in a tree in the form of an ordered vector.
vector <string> BSTree::Ordered_Keys() const
{
	//Calls recursive function to make ordered keys vector.
	vector <string> rv;
	make_key_vector(sentinel -> right, rv);
	return rv;
}
 
//Copy constructor.
BSTree::BSTree(const BSTree &t)        
{
	*this = t;
}

//Operator overloading of =.
BSTree& BSTree::operator= (const BSTree &t) 
{
	//Makes a new sentinel and sets its values to default.
	sentinel = new BSTNode;
	sentinel->parent = NULL;
	sentinel->left = NULL;
	sentinel->key = "---SENTINEL---";
	sentinel->val = NULL;

	//Orders the keys and vals.
	vector <string> keys = t.Ordered_Keys();
	vector <void *> vals = t.Ordered_Vals();
	
	//Starts the tree to the right of sentinel.
	sentinel->right = make_balanced_tree(keys,vals,0,keys.size());
	
	//Sets the size and returns the tree.
	size = t.size;
	return *this;	
}

//Recursive function to find height.
int BSTree::recursive_find_height(const BSTNode *n) const
{
	//Base Case of the current node pointing to the sentinel.
	if (n == sentinel)	return 0;
	
	//Initalizes a left and right height.
	int left = 1;
	int right = 1;

	//Recursive calls and sets the return += to the left and right.
	left += recursive_find_height(n -> left);
	right += recursive_find_height(n -> right);
	
	//Compares left and right and returns the larger one.
	return (right > left) ? right : left;
}

//Recursive function to make ordered keys vector.
void BSTree::make_key_vector(const BSTNode *n, vector<string> &v) const
{
	//Base case of n being the sentinel node.
	if (n == sentinel) return;
	
	//Recursive calls and then pushing the resulting key into a vector.
	make_key_vector(n->left, v);
	v.push_back(n->key);
	make_key_vector(n->right, v);
}

//Recursive function to balance the tree.
BSTNode *BSTree::make_balanced_tree(const vector<string> &sorted_keys, 
const vector<void *> &vals, size_t first_index,size_t num_indices) const
{
	//Base case of the number of indices remaining equal to 0.
	if (num_indices == 0) return sentinel;
	
	//Allocates memory for a new node.
	BSTNode *n = new BSTNode;
		
	//New node's left child recursion and setting itself as the child's parent.
	n-> left  = make_balanced_tree(sorted_keys, vals, first_index, num_indices/2);
	n -> left -> parent = n;

	//New node's right child recursion and setting itself as the child's parent.
	n-> right = make_balanced_tree(sorted_keys, vals, num_indices/2 + 1 + first_index, num_indices-1-num_indices/2);
	n -> right -> parent = n;

	//Setting the corresponding values for keys and nums for the node.
	n -> val = vals[first_index + num_indices/2];
	n -> key = sorted_keys[first_index+num_indices/2];
	
	return n;
}
