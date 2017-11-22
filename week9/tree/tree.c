// Description of the tree manipulation module.
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

//---------------------------------------------------------------
// Structures and constructors.

// Node structure.
struct node {
	int data;
	struct node *left;
	struct node *right;
};

// Wrapper structure.
struct tree {struct node *root;};

// Node constructor.
node *new_node(int data) {
	node *n = malloc(sizeof(node));
	n->data = data;
	n->left = NULL;
	n->right = NULL;
	return n;
}

// Wrapper constructor.
tree *newTree() {
	tree *t = malloc(sizeof(tree));
	t->root = NULL;
	return t;
}

//---------------------------------------------------------------
// Implementation functions to be ignored. User should refer to Wrapper functions.

// Insert a node n.
node *insert_node(node *p, int n) {
	if (p==NULL) p = new_node(n);
	else if (n < p->data) p->left = insert_node(p->left,n);
	else if (n > p->data) p->right = insert_node(p->right,n);
	return p;
}

// Find the node n in tree.
node *find_node(node *p, int n) {
	if (p==NULL) { }
	else if (n < p->data) p = find_node(p->left, n);
	else if (n > p->data) p = find_node(p->right, n);
	return p;
}

//---------------------------------------------------------------
// Traversals.

// Preorder traversal.
void preorder(node *n) {
	if (n != NULL) {
        printf("%d ", n->data);
        preorder(n->left);
        preorder(n->right);
    }
}

// Inorder traversal/
void inorder(node *n) {
	if(n != NULL) {
      inorder(n->left);
      printf("%d ",n->data);          
      inorder(n->right);
  	}
}

// Postorder traversal.
void postorder(node *n) {
	if (n != NULL) {
      postorder(n->left);
      postorder(n->right);
      printf("%d ", n->data);
   }
}

//---------------------------------------------------------------
// Wrapper functions.

// Insert.
void insert(tree *t, int n) {
	t->root = insert_node(t->root, n);
}

// Find. Returns a node.
node *find(tree *t, int n) {
	return find_node(t->root, n);
}

// Checks if tree contains n.
bool contains(tree *t, int n) {
	return find_node(t->root, n) != NULL;
}

// Order wrappers. Unable to test.
void printPreorder(tree *t) {
	preorder(t->root);
	printf("\n");

}

void printInorder(tree *t) {
	inorder(t->root);
	printf("\n");

}

void printPostorder(tree *t) {
	postorder(t->root);
	printf("\n");
}

//---------------------------------------------------------------
// Testing.

tree *testTree() {
	tree *t = newTree();
	insert(t,6);
	insert(t,7);
	insert(t,3);
	return t;

}

void testInsert() {
	tree *t = newTree();
	insert(t, -1);
	assert(t->root->data == -1);
	free(t);
}

void testContains() {
	tree *t = newTree();
	insert(t, 5);
	assert(contains(t,5)==true);
	assert(contains(t,10)==false);
}

void testFind() {
	tree *t = testTree();
	node *n = find(t, 6);
	assert(n->data==t->root->data);
	free(t);

}





//---------------------------------------------------------------
// Running.

int treeMain() {
	testInsert();
	testContains();
	testFind();
}
