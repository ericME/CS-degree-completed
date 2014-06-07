#include "BST.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


/* BST Node */
struct node {
	TYPE value;
	struct node * left;
	struct node * right;
};

/* BST Tree */
struct BinarySearchTree {
	struct node *root;
	int size;
};


/* Prototypes for internals */
struct node * _nodeAddBST(struct node *current, TYPE newValue);
int _containsBST(struct node *current, TYPE d);
struct node * _leftMostChild(struct node * current);
struct node * _nodeRemoveBST(struct node * current, TYPE d);


/*  initBST
	param tree the BST
	pre: tree is not null
	post: tree size is 0
 */
void initBST(struct BinarySearchTree *tree) {
	assert(tree != 0);

	tree->size = 0;
	tree->root = 0;
};

/*  sizeBST - Returns the size of BST
	param: tree the BST
	pre: tree is not null
 */
int sizeBST(struct BinarySearchTree *tree) {
	assert(tree != 0);

	return tree->size;
};

/* Node add (Node current, E newValue)
   if current is null then return a new Node with newValue
   otherwise if newValue is less than the value at current then
   set the left child to be the value returned by add(leftChild, newValue)
   otherwise set the right child to be add(rightChild, newValue)
   return the current node
 */
struct node * _nodeAddBST(struct node *current, TYPE newValue) {
	if(current == 0) {
		//printf("Putting %d here.\n\n", newValue);  // debug
		struct node *newNode = (struct node *) malloc(sizeof(struct node));
		newNode->value = newValue;
		return(newNode);
	}
	// There shouldn't be a node without a value, but just in case.
	if(current->value == 0) {
		//printf("Found node without a value.\n");  // debug
		current->value = newValue;
	// The value already exists
	} else if(newValue == current->value) {
		printf("Value %d already exists.\n", newValue);
	// Find where the new value belongs
	} else if(newValue > current->value) {
		//printf("Moving right from %d.\n", current->value);  // debug
		current->right = _nodeAddBST(current->right, newValue);
	} else if(newValue < current->value) {
		//printf("Moving left from %d.\n", current->value);  // debug
		current->left = _nodeAddBST(current->left, newValue);
	}
	return(current);
};

/*  addBST - Adds newValue to the BST
	param: tree the BST
	param: newValue the value to add
	pre: tree is not null
	pre: newValue is not null
	post: tree is not empty
 */
void addBST(struct BinarySearchTree *tree, TYPE newValue) {
	assert(tree != 0);
	assert(newValue != 0);

	//printf("Looking for place to put %d.\n", newValue);  // debug
	if(!containsBST(tree, newValue)) {
		tree->root = _nodeAddBST(tree->root, newValue);
		tree->size++;
	}
};

int _containsBST(struct node *current, TYPE d) {
	// Does node exist
	if(current == 0) {
		return(0);
	// Does node's value exist
	} else if(current->value == 0) {
		return(0);
	// The current node is the matching node
	} else if(d == current->value) {
		return 1;
	// Move left or right due to comparison
	} else if(d > current->value) {
		return(_containsBST(current->right, d));
	} else if(d < current->value) {
		return(_containsBST(current->left, d));
	}
	// Shouldn't reach this
	assert(0);
	return(0);
};

/* Search for a value in the BST
   pre: tree is not null
   pre: tree is not empty
   pre: d is not null
 */
int containsBST(struct BinarySearchTree *tree, TYPE d) {
	assert(tree != 0);
	assert(tree->size != 0);
	assert(d != 0);

	return(_containsBST(tree->root, d));
}

struct node * _leftMostChild(struct node *current) {
	assert(current != 0);

	if(current->left == 0)
		return current;
	return(_leftMostChild(current->left));
};

/* Node remove (Node current, E testValue)
   if current.value is the value we seek
   decrease the value of dataSize
   if right child is null
   return left child
   otherwise
   replace value of node with leftmost child of right child
   set right child to be removeLeftmost(right child)
   otherwise if testValue is smaller than current.value
   set left child to remove (left child, testValue)
   otherwise
   set right child to remove (right child, testValue)
   return current node
 */
struct node * _nodeRemoveBST(struct node *current, TYPE d) {
	assert(current != 0);
	assert(current->value != 0);

	struct node *temp;

	// This the node with value to remove
	if(d == current->value) {
		// Does current right exist?
		if(current->right == 0) {
			temp = current->left;
			current->value = temp->value;
			free(temp);
		} else {
			temp = _leftMostChild(current->right);
			current->value = temp->value;
			free(temp);
		}
		return(current);
	// Search left or right for the node to remove
	} else if(d > current->value) {
		return(_nodeRemoveBST(current->right, d));
	} else if(d < current->value) {
		return(_nodeRemoveBST(current->left, d));
	}
	// Shouldn't reach this
	assert(0);
	return(0);
};

/*  removeBST
	param: tree the BST
	pre: tree is not null
	pre: tree is not empty
	post: size is reduced by 1
 */
void removeBST(struct BinarySearchTree *tree, TYPE d) {
	assert(tree != 0);
	assert(tree->size != 0);

	if(containsBST(tree, d)) {
		tree->root = _nodeRemoveBST(tree->root, d);
		tree->size--;
	}
};

/* createBST
   param: none
   pre: none
   post: pointer to a BST
 */
struct BinarySearchTree * createBST() {
	struct BinarySearchTree *newBST = (struct BinarySearchTree *) malloc(sizeof(struct BinarySearchTree));
	return(newBST);
}

int main(int argc, char* argv[]){
	struct BinarySearchTree *B = createBST();

	initBST(B);
	if(sizeBST(B) != 0)
		printf("Current size is wrong... %d\n", sizeBST(B));
	addBST(B, 8);
	addBST(B, 4);
	addBST(B, 12);
	addBST(B, 1);
	if(sizeBST(B) != 4)
		printf("Current size is wrong... %d\n", sizeBST(B));
	addBST(B, 6);
	if(sizeBST(B) != 5)
		printf("Current size is wrong... %d\n", sizeBST(B));
	if(containsBST(B, 4) == 0)
		printf("BST does contain a 4.\n");
	if(containsBST(B, 5) != 0)
		printf("BST does not contain a 5.\n");
	addBST(B, 9);
	addBST(B, 2);
	addBST(B, 15);
	addBST(B, 7);
	removeBST(B, 4);
	if(containsBST(B, 4) != 0)
		printf("BST does not contain a 4.\n");
	if(containsBST(B, 1) == 0)
		printf("BST does contain a 1.\n");
	if(containsBST(B, 2) == 0)
		printf("BST does contain a 2.\n");
	if(containsBST(B, 6) == 0)
		printf("BST does contain a 6.\n");
	if(containsBST(B, 7) == 0)
		printf("BST does contain a 7.\n");
}
