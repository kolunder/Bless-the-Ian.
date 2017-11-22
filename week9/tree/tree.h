// Tree manipulation library.
#include <stdbool.h>

// Structure to initialise a tree via newTree(),
// to be passed to all the other functions.
struct tree;
typedef struct tree tree;

// Structure for nodes.
struct node;
typedef struct node node;

// Create a new empty tree.
tree *newTree();

//------------------------------------
// Node manipulation.

// Insert an element.
void insert(tree *t, int n);

// Check if the element is in the tree.
bool contains(tree *t, int n);

// Find and return a node using its value (data).
node *find(tree *t, int n)

//------------------------------------
// Traversals.

// Preorder traversal : (Root, Left, Right).
void printPreorder(tree *t);

// Inorder traversal : (Left, Root, Right).
void printInorder(tree *t);

// Postorder traversal : (Left, Right, Root).
void printPostorder(tree *t);








