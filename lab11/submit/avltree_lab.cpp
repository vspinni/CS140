//Shravan Pinni
//Lab B
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include "avltree.hpp"
using namespace std;
using CS140::AVLTree;
using CS140::AVLNode;

/* avltree_lab.cpp Lab B
 *Shravan Pinni
 *This program defines remaining functions needed
 *for the AVL class.
 */

//Prototypes for non member functions.
bool imbalance(const AVLNode *n);
void rotate(AVLNode *n);
void fix_height(AVLNode *n);
void fix_imbalance(AVLNode *n);

//Equal sign Operator Overload
AVLTree& AVLTree::operator= (const AVLTree &t)        
{
	//Making a new sentinel.
	sentinel = new AVLNode;
	sentinel -> parent = NULL;
	sentinel -> left  = NULL;
	sentinel -> key = "---SENTINEL---";
	sentinel -> val = NULL;
	sentinel -> height = 0;	

	
	//Making a new vector of the old keys and vals.
	vector <string> keys = t.Ordered_Keys();
	vector <void *> vals = t.Ordered_Vals();

	//Setting them equal in the new tree.
	sentinel -> right = recursive_postorder_copy(t.sentinel -> right);


	//Returning a new tree.
	size = t.size;
	sentinel -> right -> parent = sentinel;
	return *this;
}


//The majority of insert and delete were Dr.Plank's.
/* I simply took Insert and Delete from their binary search tree
   implementations.  They aren't correct for AVL trees, but they are
   good starting points.  */

bool AVLTree::Insert(const string &key, void *val)
{
  AVLNode *parent;
  AVLNode *n;
  AVLNode *w;

  parent = sentinel;
  n = sentinel->right;

  /* Find where the key should go.  If you find the key, return false. */

  while (n != sentinel) {
    if (n->key == key) return false;
    parent = n;
    n = (key < n->key) ? n->left : n->right;
  }

  /* At this point, parent is the node that will be the parent of the new node.
     Create the new node, and hook it in. */

  n = new AVLNode;
  n->key = key;
  n->val = val;
  n->parent = parent;
  n->height = 1;
  n->left = sentinel;
  n->right = sentinel;

  /* Use the correct pointer in the parent to point to the new node. */

  if (parent == sentinel) {
    sentinel->right = n;
  } else if (key < parent->key) {
    parent->left = n;
  } else {
    parent->right = n;
  }

  /* Increment the size */

  size++;

  //Part of insert that I added.
  //Checking and fixing imbalances in the tree.
  w = n -> parent;

  while ( w != sentinel) {
   
	fix_height(w);
	if (imbalance(w)){
		fix_imbalance(w);
	}
	w  = w -> parent;
  }
  
  return true;
}
 
//Most of delete was also Dr.Plank's code.
bool AVLTree::Delete(const string &key)
{
  AVLNode *n, *parent, *mlc;
  AVLNode *w;
  string tmpkey;
  void *tmpval;

  /* Try to find the key -- if you can't return false. */

  n = sentinel->right;
  while (n != sentinel && key != n->key) {
    n = (key < n->key) ? n->left : n->right;
  }
  if (n == sentinel) return false;

  /* We go through the three cases for deletion, although it's a little
     different from the canonical explanation. */

  parent = n->parent;

  /* Case 1 - I have no left child.  Replace me with my right child.
     Note that this handles the case of having no children, too. */

  if (n->left == sentinel) {
    if (n == parent->left) {
      parent->left = n->right;
    } else {
      parent->right = n->right;
    }
    if (n->right != sentinel) n->right->parent = parent;
    delete n;
    size--;

  /* Case 2 - I have no right child.  Replace me with my left child. */

  } else if (n->right == sentinel) {
    if (n == parent->left) {
      parent->left = n->left;
    } else {
      parent->right = n->left;
    }
    n->left->parent = parent;
    delete n;
    size--;

  /* If I have two children, then find the node "before" me in the tree.
     That node will have no right child, so I can recursively delete it.
     When I'm done, I'll replace the key and val of n with the key and
     val of the deleted node.  You'll note that the recursive call 
     updates the size, so you don't have to do it here. */

  } else {
    for (mlc = n->left; mlc->right != sentinel; mlc = mlc->right) ;
    tmpkey = mlc->key;
    tmpval = mlc->val;
    Delete(tmpkey);
    n->key = tmpkey;
    n->val = tmpval;
    return true;
  }

  //Also the only additions I made to delete.
  //Checking and fixing imbalances in the tree.
  w = n -> parent;

  while ( w != sentinel) {   
	fix_height(w);
	if (imbalance(w)){
		fix_imbalance(w);
	}
	w  = w -> parent;
  }

  return true;
}
               
//Calls the recursive vector function to copy keys..
vector <string> AVLTree::Ordered_Keys() const
{
	vector <string> rv;
	make_key_vector(sentinel -> right, rv);
	return rv;
}
 // Makes a vector of keys in the tree recursively.
void AVLTree::make_key_vector(const AVLNode *n, vector<string> &v) const
{
	//Base case.
	if (n==sentinel) return;

	//Recursion call and push back.
	make_key_vector(n->left, v);
	v.push_back(n->key);
	make_key_vector(n->right,v);
}

//Returns the height of the tree.
size_t AVLTree::Height() const
{
	return sentinel -> right -> height;
}


/* You need to write this to help you with the assignment overload.
   It makes a copy of the subtree rooted by n.  That subtree is part
   of a different tree -- the copy will be part of the tree that
   is calling the method. */

//Recursive program to copy the tree.
AVLNode *AVLTree::recursive_postorder_copy(const AVLNode *n) const
{
	//Base case.
	if (n -> height == 0) return sentinel;

	//Node t to store the information of the present node.
	AVLNode *t = new AVLNode;

	//Recursion.
	t -> left  = recursive_postorder_copy( n -> left);
	t -> right = recursive_postorder_copy(n -> right);

	//Assigning values t after recursion for post order.
	t -> left -> parent = t;
	t -> right -> parent = t;
	t -> key = n -> key;
	t -> val = n -> val;
	t -> height = n -> height;

	return t;
}
//Checks if there is an imbalance in the tree.
bool imbalance(const AVLNode *n){
	
	//Makes sets nodes for left and right.
	int right = n -> right -> height;
	int left = n -> left -> height;
	int diff;
	bool imb = false;

	//Compares left an right nodes for a difference.
	if (right > left)
		diff = right - left;
	else
		diff = left - right;
	
	//If a difference > 1 is there then there is an imbalance.
	if(diff > 1)
		imb = true;
	
	return imb;
}

//Function that rotates about a given node.
void rotate(AVLNode *n){
	//Nodes for parent and grandparent.
	AVLNode *parent = n -> parent;
	AVLNode *grandparent =  n -> parent -> parent;
	
	//Does the pointer reassigning for the rotation.
	parent -> parent = n;
	n -> parent = grandparent;
	
	//Checks if it is a right or left imbalance and acts in it.
	if (parent -> right == n){
		
		//Assigning the proper pointing for the rotations.
		parent -> right = n -> left;
		n -> left -> parent = parent;
		n -> left = parent;	
		
		//Only necessary if statement is for whether the grandparent is for left or right.
		if(grandparent -> right == parent)
			grandparent -> right = n;
		else
			grandparent -> left = n;
	}
	else{
		
		//Basically just a mirrored version of the above if-statement.
		parent -> left = n -> right;
		n -> right -> parent = parent;
		n -> right = parent;	
		
		if(grandparent -> left == parent)
			grandparent -> left = n;
		else
			grandparent -> right = n;
	}

	//Fixing the heights after a rotation.
	fix_height(parent);
	fix_height(n);
}

//Fixes Height of the passed in Node.
void fix_height(AVLNode *n){

	//Sets the proper height of a node.
	int left = n -> left -> height;
	int right = n -> right -> height;

	//Setting proper height.
	if (right > left)
		n -> height = right + 1;
	else
		n -> height = left + 1;
}

//Function that finds out what kind of imbalance it is and fixes it.
void fix_imbalance(AVLNode *n){

	//Temporary node.
	AVLNode *t;

	
	//Deciding whether its left or right problem.
	if (n -> left -> height > n -> right -> height){
		t = n -> left;

		//Zig-Zig
		if (t -> left -> height +1 >= t -> height){
			rotate(t);
		
		//Zig-Zag, 2 rotations.
		}else{
			t = t -> right;
			rotate(t);
			rotate(t);
		}
	//Right imbalance.
	}else{
		t = n -> right;

		//Zig-Zig.
		if (t -> right -> height +1 >= t -> height){
			rotate(t);
		
		//Zig-Zag, 2 rotations.
		}else{
			t = t -> left;
			rotate(t);
			rotate(t);
		}

	}
}


