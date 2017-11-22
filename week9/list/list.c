#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

//------------------------------------------------------------------------------------
// Structure declarations and utility functions.
//------------------------------------------------------------------------------------

// Structure for one node
struct node {
	item data;
	bool sent;
	struct node *next;
	struct node *back;
};
typedef struct node node;

// The structure for the whole list.
struct list {
	struct node *current;
};

// Print a fail message.
void fail(char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//------------------------------------------------------------------------------------
// Library functions.
//------------------------------------------------------------------------------------

// Create a new empty list and a sentinel node.
list *newList() {
	list *new = malloc(sizeof(list));
	node *sentinel = malloc(sizeof(node));
	sentinel->sent = true;

	new->current = sentinel;
	new->current->next = sentinel;
	new->current->back = sentinel;
	return new;
}

static void checkNext(list *l) {
	node *next =l->current->next;
	if (next->sent == true) fail("Warning! Beggining of list. Item out of range.");

}

static void checkBack(list *l) {
	node *back =l->current->back;
	if (back->sent == true) fail("Warning! End of list. Item out of range.");

}

// Move the current position one place forwards or backwards.  It is an error
// to call forward when at the end of the list, or backward when at the start.
void forward(list *l) {
	checkNext(l);
	node *next =l->current->next;
	l->current = next;

}

void backward(list *l) {
	checkBack(l);
	node *back =l->current->back;
	l->current = back;

}

// Special function to traverse the whole doubly-linked list.
static void go(list *l) {
	node *next =l->current->next;
	l->current = next;
}

// Check whether the current position is at the start or end, e.g. to test
// whether a traversal has finished.
static bool atSent(list *l) {
	if (l->current->sent == true) return true;
	else return false;
}

static void sentinel(list *l) {
	while(! atSent(l)) {
		go(l);
	}
}

// Set the current position before the first item or after the last item, e.g.
// to begin a forward or backward traversal.
// Sets current posiiton to sentinel node.
void start(list *l) {
	sentinel(l);

}
void end(list *l) {
	sentinel(l);

}

// Check whether the current position is at the start or end, e.g. to test
// whether a traversal has finished.
bool atStart(list *l) {
	return atSent(l);

}

bool atEnd(list *l) {
	return atSent(l);
	
}

// Insert an item before or after the current position (i.e. at the current
// position, but with the current position ending up after or before the new
// item).  The second argument is a pointer to the item to be copied.
void insertBefore(list *l, item x) {
	node *new = malloc(sizeof(node));
	new->data = x;
	new->sent = false;

	node *current = l->current;

	new->next = current;
	new->back = current->back;

	l->current->back = new;
}

void insertAfter(list *l, item x) {
	node *new = malloc(sizeof(node));
	new->data = x;
	new->sent = false;

	node *current = l->current;

	new->next = current->next;
	new->back = current;

	l->current->next = new;
}

// Get the item before or after the current position. It is an error to call
// getBefore when at the start, or getAfter when at the end.
item getBefore(list *l) {
	checkBack(l);
	return l->current->back->data;
}

item getAfter(list *l) {
	checkNext(l);
	return l->current->next->data;
	
}

// Set the item before or after the current position. It is an error to call
// setBefore when at the start, or setAfter when at the end.
void setBefore(list *l, item x) {
	checkBack(l);
	l->current->back->data = x;

}

void setAfter(list *l, item x) {
	checkNext(l);
	l->current->next->data = x;

}

// Delete the item before or after the current position. It is an error to call
// deleteBefore when at the start, or deleteAfter when at the end.
void deleteBefore(list *l) {
	checkBack(l);
	node *current = l->current;
	node *back = l->current->back;
	node *beforeBack = l->current->back->back;

	current->back = beforeBack;
	beforeBack->next  = current;
	back->next = NULL;
	back->back = NULL;
	free(back);

}

void deleteAfter(list *l) {
	checkNext(l);
	node *current = l->current;
	node *next = l->current->next;
	node *afterNext = l->current->next->next;

	current->next = afterNext;
	afterNext->back  = current;
	next->next = NULL;
	next->back = NULL;
	free(next);

}

//------------------------------------------------------------------------------------
// Testing
//------------------------------------------------------------------------------------

// Test travelling forward one item.
void testForward() {
	list *l = newList();
	insertAfter(l, -6);
	forward(l);
	assert(atSent(l)==false);
	assert(l->current->data==-6);
	free(l);


}

// Test travelling backward one item.
void testBackward() {
	list *l = newList();
	insertBefore(l, 2);
	backward(l);
	assert(atSent(l)==false);
	assert(l->current->data==2);
	free(l);
}

// Test if at sentinel.
void testAtSent() {
	list *l = newList();
	insertBefore(l, 6);
	insertAfter(l, -6);
	assert(atSent(l)==true);
	free(l);

}

// Test inserting an item before the current.
void testInsertBefore() {
	list *l = newList();
	insertBefore(l, 5);
	backward(l);
	assert(l->current->data == 5);
	free(l);
}

// Test inserting an item after the current.
void testInsertAfter() {
	list *l = newList();
	insertAfter(l, 44);
	forward(l);
	assert(l->current->data == 44);
	free(l);
}

// Test aquiring data in previous item.
void testGetBefore() {
	list *l = newList();
	insertBefore(l, 8);
	assert(getBefore(l) == 8);
	free(l);

}

// Test aquiring data in next item.
void testGetAfter() {
	list *l = newList();
	insertAfter(l, 5);
	assert(getAfter(l) == 5);
	free(l);
}

// Test setting data before current position.
void testSetBefore() {
	list *l = newList();
	insertBefore(l, 6);
	assert(getBefore(l) == 6);
	setBefore(l, 2);
	assert(getBefore(l) == 2);
	free(l);	
}

// Test setting data after the current position.
void testSetAfter() {
	list *l = newList();
	insertAfter(l, 3);
	assert(getAfter(l) == 3);
	setAfter(l, 0);
	assert(getAfter(l) == 0);
	free(l);
}


// Test finding the sentinel node.
void testSentinel() {
	list *l = newList();
	insertBefore(l,6);
	insertBefore(l,123442523);
	insertBefore(l,21312);
	insertBefore(l,101010);
	backward(l);
	backward(l);
	sentinel(l);
	assert(atSent(l)==true);
	free(l);
}

// Test deleting an item before the current.
void testDeleteBefore() {
	list *l = newList();
	insertBefore(l, 5);
	insertBefore(l, 2020);
	deleteBefore(l);
	assert(getBefore(l)==5);
	free(l);
}

void testDeleteAfter() {
	list *l = newList();
	insertAfter(l, 5);
	insertAfter(l, 666);
	deleteAfter(l);
	assert(getAfter(l)==5);
	free(l);

}

// Run tests.
int listMain() {
	testForward();
	testBackward();
	testAtSent();
	testInsertBefore();
	testInsertAfter();
	testGetBefore();
	testGetAfter();
	testSetBefore();
	testSetAfter();
	testSentinel();
	testDeleteBefore();
	testDeleteAfter();
	//printf("All test pass.\n");

}
