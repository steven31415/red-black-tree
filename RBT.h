#ifndef RBT_H_
#define RBT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Tree node structure
struct RBT_Node {
	int* dataPtr;
	char colour;
	struct RBT_Node* left;
	struct RBT_Node* right;
	struct RBT_Node* parent;
};

// Return an empty tree
struct RBT_Node* RBT_emptyTree();

// Return true if node is a null node, false otherwise
bool RBT_isNullNode(struct RBT_Node* node);

// Return a pointer to the node with the smallest data item in the given tree
struct RBT_Node* RBT_findMin(struct RBT_Node* root);

// Return a pointer to the node with the smallest data item in the given tree
struct RBT_Node* RBT_findMax(struct RBT_Node* root);

// Return a pointer to the node with the given data item in the given tree
struct RBT_Node* RBT_findNode(struct RBT_Node* root, int data);

// Insert a data item into the tree starting at provided root.
// Returns root which may or may not have changed.
struct RBT_Node* RBT_insert(struct RBT_Node* root, int data);

// Preorder traversal (node, left tree, right tree) performing given function on each node
void RBT_preorderTraverse(struct RBT_Node* root, void (*visit)(struct RBT_Node*), bool includeNull);

// Inorder traversal (left tree, node, right tree) performing given function on each node
void RBT_inorderTraverse(struct RBT_Node* root, void (*visit)(struct RBT_Node*), bool includeNull);

// Postorder traversal (left tree, right tree, node) performing given function on each node
void RBT_postorderTraverse(struct RBT_Node* root, void (*visit)(struct RBT_Node*), bool includeNull);

// Print details of a single node
void RBT_printNode(struct RBT_Node* node);

// Print an ASCII representation of the given tree
void RBT_printTree(struct RBT_Node* root);

// Print a list of all nodes in data order
void RBT_printTreeList(struct RBT_Node* root, bool includeNull);

// Delete tree and free all associated memory
void RBT_deleteTree(struct RBT_Node* root);

#endif