#include "RBT.h"

///////////////////////////
///  HELPER  FUNCTIONS  ///
///////////////////////////

// Returns a null node set to default values
struct RBT_Node* _makeNullNode(struct RBT_Node* parent) {
	// Allocate space for new node
	struct RBT_Node* newNode = (struct RBT_Node*) malloc(sizeof(struct RBT_Node));

	// Initialise all values
	newNode->dataPtr = NULL;
	newNode->colour = 'b';
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = parent;

	return newNode;
}

// Update target node to have same data as source node
void _copyNodeData(struct RBT_Node* source, struct RBT_Node* target) {
	target->dataPtr = source->dataPtr;
}

// Resursive function used by RBT_printTree
int _printTree(struct RBT_Node* tree, int is_left, int offset, int depth, char s[20][255])
{
    char b[20];

    // Width must match the character width of print format
    int width = 3;

    if (!tree) return 0;

    // Print format for non-null nodes
    if (RBT_isNullNode(tree)) {
    	sprintf(b, "nl%c", (tree->colour == 'r') ? 'R' : 'B');
    }
    // Print format for null nodes
    else {
    	sprintf(b, "%02d%c", *(tree->dataPtr), (tree->colour == 'r') ? 'R' : 'B');
    }
    

    int left  = _printTree(tree->left,  1, offset,                depth + 1, s);
    int right = _printTree(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
}

// Rotates given node to the left and returns pointer to new root
struct RBT_Node* _rotateLeft(struct RBT_Node* root) {
	if (!RBT_isNullNode(root)) {
		// Rotate children
		struct RBT_Node* temp = root->right;
		root->right = temp->left;
		temp->left = root;
		root = temp;

		
		// Update parents
		root->parent = root->left->parent;
		root->left->parent = root;
		root->left->right->parent = root->left;

		// Update parents children
		if (root->parent != NULL) {
			// Check if original root was a left child of its parent
			if (root->left == root->parent->left) {
				root->parent->left = root;
			}
			else {
				root->parent->right = root;
			}
		}
	}

	return root;
}

// Rotates given node to the right and returns pointer to new root
struct RBT_Node* _rotateRight(struct RBT_Node* root) {
	if (!RBT_isNullNode(root)) {
		// Rotate children
		struct RBT_Node* temp = root->left;
		root->left = temp->right;
		temp->right = root;
		root = temp;

		// Update parents
		root->parent = root->right->parent;
		root->right->parent = root;
		root->right->left->parent = root->right;

		// Update parents children
		if (root->parent != NULL) {
			// Check if original root was a left child of its parent
			if (root->right == root->parent->left) {
				root->parent->left = root;
			}
			else {
				root->parent->right = root;
			}
		}
	}

	return root;
}

// Free all memory associated with a node
void _deleteNode(struct RBT_Node* node) {
	if (node->dataPtr != NULL) {
		free(node->dataPtr);
	}

	free(node);
}

// Correctly recolour nodes in tree starting with newly inserted node
struct RBT_Node* _fixInsertedNodeColour(struct RBT_Node* root, struct RBT_Node* node) {
	// If new node is root node, colour black
	if (node->parent == NULL) {
		node->colour = 'b';
	}
	// If new node has red parent
	else if (node->parent->colour == 'r') {
		// Determine node relations
		struct RBT_Node* parent = node->parent;
		struct RBT_Node* grandparent = node->parent->parent;
		struct RBT_Node* uncle = (node->parent == grandparent->right) ? grandparent->left : grandparent->right;
		
		// Uncle is red
		if (uncle->colour == 'r') {
			parent->colour = 'b';
			uncle->colour = 'b';
			grandparent->colour = 'r';

			// Repeat for grandparent
			root = _fixInsertedNodeColour(root, grandparent);
		}
		// Uncle is black
		else {
			if (parent == grandparent->left) {
				// LEFT LEFT Case
				if (node == parent->left) {
					// Update root
					if (root == grandparent) {
						root = parent;
					}

					// Rotate grandparent right
					_rotateRight(grandparent);

					// Swap colours of parent and grandparent
					bool temp = grandparent->colour;
					grandparent->colour = parent->colour;
					parent->colour = temp;
				}
				// LEFT RIGHT Case
				else {
					// Update root
					if (root == grandparent) {
						root = node;
					}

					// Rotate parent left
					_rotateLeft(parent);

					// Rotate grandparent right
					_rotateRight(grandparent);

					// Swap colours of node and grandparent
					bool temp = grandparent->colour;
					grandparent->colour = node->colour;
					node->colour = temp;
				}
			}
			else {
				// RIGHT LEFT Case
				if (node == parent->left) {
					// Update root
					if (root == grandparent) {
						root = node;
					}

					// Rotate parent right
					_rotateRight(parent);

					// Rotate grandparent left
					_rotateLeft(grandparent);

					// Swap colours of node and grandparent
					bool temp = grandparent->colour;
					grandparent->colour = node->colour;
					node->colour = temp;
				}
				// RIGHT RIGHT Case
				else {
					// Update root
					if (root == grandparent) {
						root = parent;
					}

					// Rotate grandparent left
					_rotateLeft(grandparent);

					// Swap colours of parent and grandparent
					bool temp = grandparent->colour;
					grandparent->colour = parent->colour;
					parent->colour = temp;
				}
			}
		}
	}

	return root;
}



///////////////////////////
///   RED BLACK TREE    ///
///////////////////////////

struct RBT_Node* RBT_emptyTree() {
	return _makeNullNode(NULL);
}

bool RBT_isNullNode(struct RBT_Node* node) {
	return (node->dataPtr == NULL);
}

struct RBT_Node* RBT_findMin(struct RBT_Node* root) {
	// Return null if tree consists only of null node
	if (RBT_isNullNode(root)) {
		return NULL;
	}

	// Move left in tree until a null node reached
	while (!RBT_isNullNode(root->left)) {
		root = root->left;
	}

	return root;
}

struct RBT_Node* RBT_findMax(struct RBT_Node* root) {
	// Return null if tree consists only of null node
	if (RBT_isNullNode(root)) {
		return NULL;
	}

	// Move right in tree until a null node reached
	while (!RBT_isNullNode(root->right)) {
		root = root->right;
	}

	return root;
}

struct RBT_Node* RBT_findNode(struct RBT_Node* root, int data) {
	// Move left or right in tree accordingly until data found or null node reached
	while (!RBT_isNullNode(root)) {
		if (data < *(root->dataPtr)) {
			root = root->left;
		}
		else if (data > *(root->dataPtr)) {
			root = root->right;
		}
		else {
			return root;
		}
	}

	return NULL;
}

struct RBT_Node* RBT_insert(struct RBT_Node* root, int data) {
	// Create current node
	struct RBT_Node * current = root;

	// Find null node at location of new insertion
	while (!RBT_isNullNode(current)) {
		if (data <= *(current->dataPtr)) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	// Allocate new node to replace null node
	int* dataPtr = (int*) malloc (sizeof(int));
	*dataPtr = data;

	current->dataPtr = dataPtr;
	current->left = _makeNullNode(current);
	current->right = _makeNullNode(current);

	// Colour new node red initially
	current->colour = 'r';

	// Maintain correct colouring of tree
	root = _fixInsertedNodeColour(root, current);

	// Return tree root
	return root;
}

void RBT_preorderTraverse(struct RBT_Node* root, void (*visit)(struct RBT_Node*), bool includeNull) {
	if ((includeNull && root == NULL) || (!includeNull && RBT_isNullNode(root))) {return;}

	visit(root);
	RBT_preorderTraverse(root->left, visit, includeNull);
	RBT_preorderTraverse(root->right, visit, includeNull);
}

void RBT_inorderTraverse(struct RBT_Node* root, void (*visit)(struct RBT_Node*), bool includeNull) {
	if ((includeNull && root == NULL) || (!includeNull && RBT_isNullNode(root))) {return;}

	RBT_inorderTraverse(root->left, visit, includeNull);
	visit(root);
	RBT_inorderTraverse(root->right, visit, includeNull);
}

void RBT_postorderTraverse(struct RBT_Node* root, void (*visit)(struct RBT_Node*), bool includeNull) {
	if ((includeNull && root == NULL) || (!includeNull && RBT_isNullNode(root))) {return;}

	RBT_postorderTraverse(root->left, visit, includeNull);
	RBT_postorderTraverse(root->right, visit, includeNull);
	visit(root);
}

void RBT_printNode(struct RBT_Node* node) {
	char format[] = "%s\t%s\t%s\t%s\t%s\n";

	int data = 0;
	int left_data = 0;
	int right_data = 0;
	int parent_data = 0;

	if (!RBT_isNullNode(node)) {
		data = *(node->dataPtr);
		format[1] = 'd';
	}

	if (node->left != NULL && !RBT_isNullNode(node->left)) {
		left_data = *(node->left->dataPtr);
		format[4] = 'd';
	}

	if (node->right != NULL && !RBT_isNullNode(node->right)) {
		right_data = *(node->right->dataPtr);
		format[7] = 'd';
	}

	if (node->parent != NULL) {
		parent_data = *(node->parent->dataPtr);
		format[10] = 'd';
	}

	printf(format, data, left_data, right_data, parent_data, (node->colour == 'r') ? "Red" : "Black");
}

void RBT_printTree(struct RBT_Node* root)
{
    char s[20][255] = {};
    for (int i = 0; i < 20; i++) {
        sprintf(s[i], "%80s", " ");
    }

    _printTree(root, 0, 0, 0, s);

    for (int i = 0; i < 20; i++) {
        printf("%s\n", s[i]);
    }
}

void RBT_printTreeList(struct RBT_Node* root, bool includeNull) {
	// Print column headings
	printf("NODE\tLEFT\tRIGHT\tPARENT\tCOLOUR\n");

	// Traverse tree in data order and print each node
	RBT_inorderTraverse(root, RBT_printNode, includeNull);
}

void RBT_deleteTree(struct RBT_Node* root) {
	// Traverse tree and delete each node
	RBT_postorderTraverse(root, _deleteNode, true);
}

