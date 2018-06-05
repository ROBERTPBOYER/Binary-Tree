/*                                                                                                              #THE KILLER BUNNY
Robert Boyer                                                                                                         (\_/)
CSS 343 (Fall 2015)                                                                                                  (o o)
-------------------------------------------------------------------------------------------------------------       (     )
Creation Date: 10/13/2015
Date of Last Modification: 10/24/2015
--------------------------------------------------------------------------------------------------------------------------------
Purpose: Assignment to create a Binary Search Tree
--------------------------------------------------------------------------------------------------------------------------------
Notes: Data stored in this Binary Search Tree are in the form of Strings
--------------------------------------------------------------------------------------------------------------------------------
*/

#ifndef BINTREE_H
#define BINTREE_H

#include "nodedata.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class BinTree {

	friend ostream &operator<<(ostream &out, const BinTree &rhs); // Stream O

 public:
	 BinTree();                                                   // Default Constructor
	 BinTree(const BinTree &rhs);                                 // Copy Constructor

	 ~BinTree();                                                  // Destructor

	 const BinTree& operator=(const BinTree &rhs);                // Assignment Operator

	 bool operator==(const BinTree & rhs) const;                  // Comparison Operators
	 bool operator!=(const BinTree & rhs) const;

	 bool retrieve(const NodeData &, NodeData* &);                // Retrieves Node
	 bool insert(NodeData*);                                      // Inserts Node 
	 
	 int getHeight(const NodeData &);                             // Finds Height of Node in tree
	 
	 void bstreeToArray(NodeData* []);                            // Binary Search Tree to Array
	 void arrayToBSTree(NodeData* []);                            // Array to Binary Search Tree

	 bool isEmpty() const;                                        // Checks if Empty
	 void makeEmpty();                                            // Make BS Tree Empty
	 
	 void displaySideways() const;                                // Print out Sideways
	
 private:

	 struct Node {
		 NodeData* data; // pointer to data object
		 Node* left;	 // left subtree pointer
		 Node* right;	 // right subtree pointer
	 };
	 Node* root;

	 // Utility functions
	 void outputHelper(Node*) const;                                              //recursive helper for operator<<
	 
	 void copyBinTree(Node*&, Node*);                                            //recursive helper for: copy constructor and operator=
	 
	 bool isEqual(Node*, Node*) const;                                           //recursive helper for: operator==
	 
	 void retrieveHelper(Node*, const NodeData&, NodeData*&) const;              //recursive helper for: retrieve()
	 
	 int getHeightHelper(Node*&, const NodeData&, int&);                         //recursive helper for: getHeight()
	 
	 void bstreeToArrayHelper(Node*, NodeData*[], int&);                         //recursive helper for: bstreeToArray()

	 void arrayToBSTreeHelper(NodeData*[], const Node*, int, int);               //recursive helper for: arrayToBSTree()
	 
	 void makeEmptyHelper(Node*&);                                               //recursive helper for: makeEmpty()

	 void sideways(Node*, int) const;	                          		         //provided helper for: displaySideways()
};

#endif
