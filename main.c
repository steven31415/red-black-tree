#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>

#include "RBT.h"

///////////////////////////
////   MAIN FUNCTIONS  ////
///////////////////////////

int main() {

	struct RBT_Node* root = RBT_emptyTree();

	root = RBT_insert(root, 30);
	root = RBT_insert(root, 20);
	root = RBT_insert(root, 40);
	root = RBT_insert(root, 50);
	root = RBT_insert(root, 3);
	root = RBT_insert(root, 1);
	root = RBT_insert(root, 2);
	root = RBT_insert(root, 64);
	root = RBT_insert(root, 37);
	root = RBT_insert(root, 40);
	root = RBT_insert(root, 11);
	root = RBT_insert(root, 51);

	RBT_printTree(root);
	RBT_printTreeList(root, false);

	RBT_deleteTree(root);
}