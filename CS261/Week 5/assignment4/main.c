#include<stdio.h>
#include<stdlib.h>
#include "bst.h"
#include "structs.h"

/* Example main file to begin exercising your tree */

int main(int argc, char *argv[])
{
	struct BSTree *tree	= newBSTree();

	/*Create value of the type of data that you want to store*/
	struct data myData1;
	struct data myData2;
	struct data myData3;
	struct data myData4;
	struct data myData5;

	myData1.number = 5;
	myData1.name = "rooty";
	myData2.number = 1;
	myData2.name = "lefty";
	myData3.number = 10;
	myData3.name = "righty";
	myData4.number = 3;
	myData4.name = "righty";
	myData5.number = -1;
	myData5.name = "wine";

	/*add the values to BST*/
	addBSTree(tree, &myData1);
	addBSTree(tree, &myData2);
	addBSTree(tree, &myData3);
	addBSTree(tree, &myData4);
	//addBSTree(tree, &myData5);
	/*test remove */
	removeBSTree(tree, &myData4);

	/*test contains*/
	printf("contains mydata1?: %d \n",containsBSTree(tree, &myData1));
	printf("contains mydata2?: %d \n",containsBSTree(tree, &myData2));
	printf("contains mydata3?: %d \n",containsBSTree(tree, &myData3));
	printf("contains mydata4?: %d \n",containsBSTree(tree, &myData4));
	printf("contains mydata5?: %d \n",containsBSTree(tree, &myData5));




	/*Print the entire tree*/
	printTree(tree);
	/*(( 1 ( 3 ) ) 5 ( 10 ))*/
	return 1;
}

