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

#include "bintree.h"

//--------------------------------------------------------- (<<) ---------------------------------------------------------------
// Description: Output stream to display.. 
//              the true inorder traversal
//------------------------------------------------------------------------------------------------------------------------------
ostream& operator<<(ostream& output, const BinTree& rhs){

	rhs.outputHelper(rhs.root);
	output << endl;
	return output;
}

//---------------------------------------------------- (outputHelper) ---------------------------------------------------------
// Description: Recursive helper for operator<<
//              It traverses in order and prints data
//------------------------------------------------------------------------------------------------------------------------------
void BinTree::outputHelper(Node * cur) const {

	if (cur != NULL){

		outputHelper(cur->left);
		cout << *cur->data << " ";
		outputHelper(cur->right);
	}
}

//-------------------------------------------------- (Default Constructor) -----------------------------------------------------
// Description: creates a new empty BSTree
//------------------------------------------------------------------------------------------------------------------------------
BinTree::BinTree(){
	root = NULL;
}
//--------------------------------------------------- (Copy Constructor) -------------------------------------------------------
// Description: creates a new BSTree that is.. 
//               an exact copy of another BSTree
//------------------------------------------------------------------------------------------------------------------------------
BinTree::BinTree(const BinTree &rhs){
	// calls recursive copy helper
	copyBinTree(root, rhs.root);
}

//----------------------------------------------------- (Destructor) ----------------------------------------------------------- 
// Description: Deletes Binary Search Tree
//------------------------------------------------------------------------------------------------------------------------------
BinTree::~BinTree(){
	if (isEmpty() == true) return;
	makeEmpty();//remove Nodes
}

//---------------------------------------------------------- (=) ---------------------------------------------------------------
// Description: Sets one BSTree equal to another
//------------------------------------------------------------------------------------------------------------------------------
const BinTree& BinTree::operator=(const BinTree &rhs){
	if (this == &rhs){//if BineTrees are equal
		return *this;
	}
	if (isEmpty() == false){
		makeEmpty();//delete current tree
	}
	copyBinTree(root, rhs.root);//copy tree
	return *this;
}

//------------------------------------------------------ (copyBinTree) ---------------------------------------------------------
// Description: Recursive Copy Helper.. 
//            for copy constructor and operator=
//------------------------------------------------------------------------------------------------------------------------------
void BinTree::copyBinTree(Node*& newNode, Node* copyNode){
	if (copyNode == NULL) { //if nothing to copy
		newNode = NULL;
	}
	else{//else has data to copy
		newNode = new Node;// create new Node
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->data = new NodeData(*copyNode->data); //copy data

		copyBinTree(newNode->left, copyNode->left);// recursively call left Node
		copyBinTree(newNode->right, copyNode->right);// recursively call right Node
	}
}

//---------------------------------------------------------- (==) --------------------------------------------------------------
// Description: Compares two BSTrees to..
//         determine if they have exactly the same..
//              data AND the same structure
//------------------------------------------------------------------------------------------------------------------------------
bool BinTree::operator==(const BinTree & rhs) const {
	
	return isEqual(root, rhs.root);
}
//---------------------------------------------------------- (!=) --------------------------------------------------------------
// Description: Compares two BSTrees to..
//         determine if they do NOT have exactly..
//         the same data AND the same structure
//------------------------------------------------------------------------------------------------------------------------------
bool BinTree::operator!=(const BinTree & rhs) const {
	
	return !(isEqual(root, rhs.root));
}
//-------------------------------------------------------- (isEqual) -----------------------------------------------------------
// Description: Checks recursively if two BSTrees.. 
//              have exactly the same data AND structure
//------------------------------------------------------------------------------------------------------------------------------
bool BinTree::isEqual(Node* curNode, Node* rhsNode) const {

	if (rhsNode == NULL && curNode == NULL)// both Nodes are null
		return true; //same

	if (rhsNode == NULL || curNode == NULL) // just one of Nodes is null
		return false; //not same

	if (*rhsNode->data != *curNode->data) //data does not match 
		return false; //not same

	bool check = isEqual(curNode->left, rhsNode->left);// traverse left sides
	
	if(check == false) // if left sides are not equal return false
		return false; 

	check = isEqual(curNode->right, rhsNode->right);  // traverse right sides
	return check;

}

//-------------------------------------------------------- (retrieve) ----------------------------------------------------------
// Description: Checks if BSTree has Object;
// if found will return true + point to object
//------------------------------------------------------------------------------------------------------------------------------
bool BinTree::retrieve(const NodeData & dataItem, NodeData* & dataFound){

	retrieveHelper(root, dataItem, dataFound);

	if (dataFound != NULL)
		return true;
	else
		false;
}
//----------------------------------------------------- (retrieveHelper) -------------------------------------------------------
// Description: Recursively Checks for Object
//------------------------------------------------------------------------------------------------------------------------------
void BinTree::retrieveHelper(Node* curNode, const NodeData& dataItem,NodeData*& dataFound)const{
	if (curNode == NULL)//NOT found
		dataFound = NULL;
	else if (dataItem == *curNode->data){//Found

		dataFound = curNode->data;
	}
	else if (dataItem < *curNode->data){//check left

		retrieveHelper(curNode->left, dataItem, dataFound);
	}
	else{//if(dataItem > *curNode->data)//check right
	
		retrieveHelper(curNode->right, dataItem, dataFound);
	}
}

//-------------------------------------------------------- (insert) ------------------------------------------------------------
// Description: Inserts NodeData into BSTree; 
//        returns true if successfully added to tree
//------------------------------------------------------------------------------------------------------------------------------
bool BinTree::insert(NodeData* data){

	Node* newPtr = new Node; // new Node to store data 
	newPtr->data = data; //points to data
	data = NULL; //nulls given pointer
	newPtr->left = NULL; 
	newPtr->right = NULL;
	
	if (isEmpty() == true){//if tree is empty

		root = newPtr;//make newly created Node the root
	}
	else{//tree is not empty

		Node* cur = root;//pointer for traversing tree
		bool inserted = false;//to tell if insert was successful

		while (!inserted){

			if (*newPtr->data == *cur->data){//if data is already in tree; delete duplicate
				
				delete newPtr;
				newPtr = NULL;
				return false;
			}
			else if (*newPtr->data < *cur->data){//if data is less than cur->data, go left

				if (cur->left == NULL){//if no more data to compare with, add to tree

					cur->left = newPtr;
					inserted = true;
				}
				else
					cur = cur->left; //there still is data to compare with, transverse
			}
			else {//data is greater than cur->data, go right
				
				if (cur->right == NULL){//if no more data to compare with, add to tree

					cur->right = newPtr;
					inserted = true;
				}
				else
					cur = cur->right;//there still is data to compare with, transverse
			}
		}
	}
	return true;
}


//-------------------------------------------------------- (getHeight) ---------------------------------------------------------
// Description: gets height of a Node on the tree.
// Works for General Binary Trees, not just BSTs
//------------------------------------------------------------------------------------------------------------------------------
int BinTree::getHeight(const NodeData & item){
	int height = 0;
	getHeightHelper(root, item, height);
	return height;
}
//----------------------------------------------------- (getHeightHelper) ------------------------------------------------------
// Description: recursive checks for item, 
//			if found saves its height in variable
//------------------------------------------------------------------------------------------------------------------------------
int BinTree::getHeightHelper(Node *& current, const NodeData & item, int & height){
	
	if (current == NULL) return 0;

	int leftH = getHeightHelper(current->left, item, height);
	int rightH = getHeightHelper(current->right, item, height);
	
	if (*current->data == item){
		
		if (leftH > rightH)
			height = leftH + 1;
		else //(leftH < rightH)
			height = rightH + 1;
	}
	if (leftH > rightH)
		return leftH + 1;
	else //(leftH < rightH)
		return rightH + 1;
}


//------------------------------------------------------ (bstreeToArray) -------------------------------------------------------
// Description: Fills an array of Nodedata* using.. 
//       in order traversal of tree. It leaves tree empty
//------------------------------------------------------------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* tempArray[]){

	int index = -1;//counter for index of array
	bstreeToArrayHelper(root, tempArray, index);//call helper
	makeEmpty(); //delete empty tree
}

//--------------------------------------------------- (bstreeToArrayHelper) ----------------------------------------------------
// Description: Recursive helper for bstreeToArray;
// Traverses entire BSTree and Fills Array with its data
//------------------------------------------------------------------------------------------------------------------------------
void BinTree::bstreeToArrayHelper(Node* cur, NodeData* tempArray[], int& index)
{
	if (cur == NULL) 
		return; // found leaf

	bstreeToArrayHelper(cur->left, tempArray, index);//traverse left

	++index;                      // increase index
	tempArray[index] = cur->data; // point array at index to node->data
	cur->data = NULL;             // null data

	bstreeToArrayHelper(cur->right, tempArray, index);//traverse right
}


//------------------------------------------------------ (arrayToBSTree) -------------------------------------------------------
// Description: Builds a balanced BSTree from sorted.. 
// array of Nodedata* leaving the array filled with NULLs
//------------------------------------------------------------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* tempArray[]){

	int high = 0;//counts the total number of array slots that are filled 

	for (int i = 0; i < 100; i++){//runs through array size 100
	
		if (tempArray[i] != NULL)
			high++;
		else//tempArray[i] == NULL 
			tempArray[i] = NULL;
	}

	//call recursive helper 
	arrayToBSTreeHelper(tempArray, root, 0, high - 1);
}
//--------------------------------------------------- (arrayToBSTreeHelper) ----------------------------------------------------
// Description: Recursive helper for arrayToBSTree;
//
//------------------------------------------------------------------------------------------------------------------------------
void BinTree::arrayToBSTreeHelper(NodeData* array[], const Node* cur, int low, int high){

	if (low > high) //stop
		cur = NULL;
	else {

		int idx = (low + high) / 2; //calculate middle index 
		NodeData *temp; //temp pointer
		temp = array[idx]; //temp saves string data
		array[idx] = NULL; //Null index data

		insert(temp); //add data to tree

		arrayToBSTreeHelper(array, cur, low, idx - 1);//go left of index
		arrayToBSTreeHelper(array, cur, idx + 1, high);//go right of index
	}

}
//-------------------------------------------------------- (isEmpty) -----------------------------------------------------------
// Description: Checks if BSTree is empty
//------------------------------------------------------------------------------------------------------------------------------
bool BinTree::isEmpty() const{
	if (root != NULL)
		return false;
	else
		return true;
}
//------------------------------------------------------- (makeEmpty) ----------------------------------------------------------
// Description: Makes BSTree empty
//------------------------------------------------------------------------------------------------------------------------------
void BinTree::makeEmpty(){
	//calls recursive helper to delete Nodes
	makeEmptyHelper(root);
}
//---------------------------------------------------- (makeEmptyHelper) -------------------------------------------------------
// Description: Recursive makeEmpty Helper.. 
//              for traversing/deleting Nodes
//------------------------------------------------------------------------------------------------------------------------------
void BinTree::makeEmptyHelper(Node*& node){
	if (node == NULL)
		return;

	makeEmptyHelper(node->left);
	makeEmptyHelper(node->right);

	delete node->data;// delete NodeData
	node->data = NULL;
	delete node;// delete Node
	node = NULL;
}

//--------------------------------------------------- (displaySideways) --------------------------------------------------------
// Description: Displays a binary tree as though.. 
// you are viewing it from the side hard coded..
// displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
//------------------------------------------------------------------------------------------------------------------------------
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//------------------------------------------------------- (sideways) -----------------------------------------------------------
// Description: Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
//------------------------------------------------------------------------------------------------------------------------------
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}

