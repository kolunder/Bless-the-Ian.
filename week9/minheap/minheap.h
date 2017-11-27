//------------------------------------------------------------------------------------
// A Custom library to create a Min Heap from Array.
//------------------------------------------------------------------------------------

// Single node structure. Access the data within node via:
//	> node *n
//	> n->data == data
struct node {
	int data;
	char letter;
	struct node *left;
	struct node *right;
}; 

// Whole heap structure.
struct heap {
	unsigned size; // Current size.
	unsigned capacity; // Current capacity
	struct node **array; // Pointer to array of node pointers.
};

typedef struct heap heap;
typedef struct node node;

// Create a new node for insertion. 
node *new_node(int data);

// Create a new Min Heap from array.
heap *new_heap(int data[], long size);

// Insert node into a given list.
void insert_node(heap *h, node *n);

// Get the root (node at position heap[0]) from the heap.
node *remove_root(heap *h);

// Printing an array.
void printArr(int arr[], int n);

// Print the heap.
void print_heap(heap *h, int size);


