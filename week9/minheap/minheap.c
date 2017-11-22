/* Custom minHeap constructor.

* @Author: kolunderr
* @Date:   2017-11-21 11:58:57
* @Last Modified by:   kolunderr
* @Last Modified time: 2017-11-21 17:13:15
*/
#include "minheap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

//------------------------------------------------------------------------------------
// Structures, constructors, macros and utility functions.
//------------------------------------------------------------------------------------

#define left(x) 2 * x + 1;
#define right(x) 2 * x + 2
#define parent(x) (x - 1) / 2

struct node;
//typedef struct node node;

// Whole heap structure.
struct heap {
	unsigned size; // Current size.
	unsigned capacity; // Current capacity
	struct node **array; // Pointer to array of node pointers.
};

// Node constructor.
node *new_node(int data) {
	node *n = malloc(sizeof(node));
	n->data = data;
	n->left = n->right = NULL;
	return n;
}

//------------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------------

// Empty heap constructor..
static heap *init_heap(unsigned capacity) {
	heap *h = malloc(sizeof(heap));
	h->size = 0;
	h->capacity = capacity;
	h->array = malloc(capacity * sizeof(node));
	return h;
}

// Function to swap two nodes.
static void swap(node **n1, node **n2) {
	node *temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

// Two functions to restore heap-property, starting at index n in array of nodes.
static void heapify(heap *h, int n) {
	int smallest = n;
	int left = left(n);
	int right = right(n);

	if (left < h->size && h->array[left]->data < h->array[smallest]->data) {
		smallest = left;
	}
	if (right < h->size && h->array[right]->data < h->array[smallest]->data) {
		smallest = right;
	}
	if (smallest != n) {
		swap(&h->array[smallest], &h->array[n]);
		heapify(h, smallest);
	}
}
// ..see above..
static void build_heap(heap *h) {
	int n = h->size - 1; // last element.
	int i;
	for (i = parent(n); i >= 0; i--) heapify(h, i);
}

// Checks if size of heap equals to one.
static bool isOne(heap *h) {
	return (h->size==1);
}

// Checks if the node is a leaf.
static bool isLeaf(node *root) {
	return !(root->left) && !(root->right);
}

//------------------------------------------------------------------------------------
// Usable functions.
//------------------------------------------------------------------------------------

// TODO: Print an array of size n.
void printArr(int arr[], int n) {

}

// Print the heap.
void print_heap(heap *h, int size) {
	for (int i =0; i < size; i++) printf("%d ", h->array[i]->data);
	printf("\n");
	//h->size--;

}


// Returns a pointer to the root, whlist removing it from the array.
node *remove_root(heap *h) {
	node *n = h->array[0];
	h->array[0] = h->array[h->size-1];
	--h->size;
	heapify(h, 0);
	return n;
}

// Insert node.
void insert_node(heap *h, node *n) {
	h->size++;
	int i = h->size - 1;
	while (i && n->data < h->array[parent(i)]->data) {
		h->array[i] = h->array[parent(i)];
		i = parent(i);
	}
	h->array[i] = n;
}

// New heap from array of int size.
heap *new_heap(int data[], long size) {
	heap *h = init_heap(size);
	for (int i = 0; i < size; i++) {
		h->array[i]= new_node(data[i]);
	}
	h->size = size;
	build_heap(h);
	return h;
}

//------------------------------------------------------------------------------------
// Testing and Main.
//------------------------------------------------------------------------------------

void testRemove() {
	int arr[] = {1234,23,712,3,999,88};
	int size = sizeof(arr)/ sizeof(arr[0]);
	heap *h = new_heap(arr, size);
	node *n = remove_root(h);
	assert(n->data==3);
}

void testIsOne() {
	int arr[] = {2};
	int size = sizeof(arr)/ sizeof(arr[0]);
	heap *h = new_heap(arr, size);
	assert(isOne(h)==true);
}

void testIsLeaf() {
	int arr[] = {666};
	int size = sizeof(arr)/ sizeof(arr[0]);
	heap *h = new_heap(arr, size);
	assert(isLeaf(h->array[size-1])==true);
}

void testInsertNode() {
	int arr[] = {66,23,712,122,24,88};
	int size = sizeof(arr) / sizeof(arr[0]);
	heap *h = new_heap(arr, size);
	node *n = remove_root(h);
	assert(n->data==23);
	
	node *new = new_node(10);
	insert_node(h,new);
	node *r = remove_root(h);
	assert(r->data==10);

}

// TODO: complete.
void testNewHeap() {
	int arr[] = {1234,23,712,3,999,88};
	int size = sizeof(arr) / sizeof(arr[0]);
	heap *h = new_heap(arr, size);
	print_heap(h, h->size);
	node *a = remove_root(h);
	node *b = remove_root(h);

	print_heap(h, h->size);

	printf("The two removed nodes are: %d and %d\n", a->data, b->data);

	free(h);
	
}

// Run tests.
int minheapMain() {
	testRemove();
	testIsOne();
	testIsLeaf();
	testInsertNode();
	testNewHeap();
	
}


