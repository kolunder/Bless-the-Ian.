//------------------------------------------------------------------------------------
// A Custom library to create a Min Heap from Array.
//------------------------------------------------------------------------------------

// Opaque heap type.
struct heap;
typedef struct heap heap;

// Opaque node type.
// Single node structure.
struct node {
	int data;
	struct node *left;
	struct node *right;
}; typedef struct node node;


// Create a new node of value data.
node *new_node(int data);

// Create a new Min Heap from array.
heap *new_heap(int data[], long size);

// Insert node into a given list.
void insert_node(heap *h, node *n);

// Get the root from the heap.
node *remove_root(heap *h);

// Printing an array.
void printArr(int arr[], int n);

// Print the heap.
void print_heap(heap *h, int size);


