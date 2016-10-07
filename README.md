red-black-tree
===================
An implementation of a red-black tree using integers, written in C

Details of such trees and their implementation can be found
[here](http://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/)

# Setup

The repo comes with a `main.c` that includes an example implementation. Within the repo directory run the following command: 

```
make; ./a.out
```


# Functions


### `struct RBT_Node* RBT_emptyTree();`

Create an empty tree

**Returns** A `struct BST_Node` that represents the new empty tree.


### `bool RBT_isNullNode(struct RBT_Node* node)`

Test if a node is a null node

* `node` is the node to be tested

**Returns** `true` if `node` is a null node, otherwise `false`


### `struct RBT_Node* RBT_findMin(struct RBT_Node* root);`

Find the node with the smallest data item in a tree

* `root` is the root node of the tree to be searched

**Returns** A pointer to a `RBT_Node` which holds the smallest data item


### `struct RBT_Node* RBT_findMax(struct RBT_Node* root);`

Find the node with the largest data item in a tree

* `root` is the root node of the tree to be searched

**Returns** A pointer to a `RBT_Node` which holds the largest data item


### `struct RBT_Node* RBT_findNode(struct RBT_Node* root, int data)`

Find the node with the given data item in a tree

* `root` is the root node of the tree to be searched
* `data` is an integer to be found in the tree

**Returns** A pointer to a `RBT_Node` which holds the value `data`


### `struct RBT_Node* RBT_insert(struct RBT_Node* root, int data)`

Insert a data item into a tree starting at provided root

* `root` is the root node of the tree
* `data` is an integer to be inserted

**Returns** The root of the given tree (which may have changed as a result of insertion)


### `void RBT_preorderTraverse(struct RBT_Node* root, void (*visit)(struct RBT_Node*), bool includeNull)`

Perform a given function on every node in a tree via a ***preorder*** traversal (node, left tree, right tree)

* `root` is the root node of the tree
* `visit` is a function acting on a node
* `includeNull` specifies whether or not to traverse null nodes


### `void RBT_inorderTraverse(struct RBT_Node* root, void (*visit)(struct RBT_Node*), bool includeNull)`

Perform a given function on every node in a tree via a ***inorder*** traversal (left tree, node, right tree)

* `root` is the root node of the tree
* `visit` is a function acting on a node
* `includeNull` specifies whether or not to traverse null nodes


### `void RBT_postorderTraverse(struct RBT_Node* root, void (*visit)(struct RBT_Node*), bool includeNull)`

Perform a given function on every node in a tree via a ***postorder*** traversal (left tree, right tree, node)

* `root` is the root node of the tree
* `visit` is a function acting on a node
* `includeNull` specifies whether or not to traverse null nodes


### `void RBT_printNode(struct RBT_Node* node)`

Print details of a single node

* `node` is the node to be printed


### `RBT_printTree(struct RBT_Node* root)`

Print an ASCII representation of a tree

* `root` is the root node of the tree


### `void RBT_printTreeList(struct RBT_Node* root, bool includeNull)`

Print a list of all nodes in numerical order with associated properties

* `root` is the root node of the tree
* `includeNull` specifies whether or not to include null nodes


### `void RBT_deleteTree(struct RBT_Node* root)`

Delete a tree and free all associated memory

* `root` is the root node of the tree


# Credits
(c) 2016 Steven Watts
