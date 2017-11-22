#include "text.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

struct text {
    int size;
    char *array;
};

// Create a new text structure, containing a copy of the given string.
// Note that this function is impossible to test fully.
// Counts null character as well to determine the full capacity of array.
text *new(char *s) {
    int n = strlen(s) + 1;
    text *t = malloc(sizeof(text) + n);
    t->array = malloc(n);

    strcpy(t->array, s);
    t->size = n;
    return t;
}

// Free up both the space for the struct and the space for the character array.
// Be careful not to access anything after it has been freed.
// Note that this function is imnpossible to test.
void discard(text *t) {
    free(t);
   
}

// Find the length of a text (equivalent to strlen).
int length(text *t) {
    return t->size - 1;
}

// Extract the i'th character (equivalent to s[i]).
char get(text *t, int i) {
    return t->array[i];
}

// Set the i'th character (equivalent to s[i] = c).
void set(text *t, int i, char c) {
    t->array[i] = c;
}

// Make a copy (equivalent to strcpy).
text *copy(text *t) {
    return t;
}

// Compare two texts (equivalent to strcmp).
int compare(text *t1, text *t2) {
    return (strcmp(t1->array, t2->array));
}

// Join a second text to the end of a first (equivalent to strcat).
void append(text *t1, text *t2) {
    int capacity = strlen(t1->array) + strlen(t2->array) + 1;
    t1->array = realloc(t1->array, capacity);
    strcat(t1->array, t2->array);
    t1->size = capacity;
}

// Extract a subtext (no exact equivalent for strings).
text *slice(text *t, int i, int j) {
    int newSize = (j - i) + 1;
    char temp[newSize];
    
    for (int k = 0; (k + i) < j; k++) {
        temp[k] = get(t, k + i);
    }
    temp[newSize - 1] = '\0';
    
    return new(temp);

}

// Search for a subtext (roughly equivalent to strstr).
int find(text *t, text *p) {
    char *found = strstr(t->array, p->array);
    if (found == NULL) return -1;

    return found - t->array;
}

//-----------------------------------------------------------------------------
// Tests and a textMain function (renamed to main when compiled for testing).

// Check whether a text is like a given string, as far as can be checked
// without knowing how much memory has been allocated.
bool like(text *t, char *s) {
    if (t == NULL) return false;
    if (t->size <= strlen(s)) return false;
    if (strcmp(t->array, s) != 0) return false;
    
    return true;
}

// Check that everything is as expected after calling new.
void testNew() {
    text *t = new("");
    assert(like(t, ""));
    text *t2 = new("cat");
    assert(like(t2, "cat"));
    discard(t);
    discard(t2);
}

void testLength() {
    text *t = new("cat");
    assert(length(t) == 3);
    discard(t);
}

void testGet() {
    text *t = new("cat");
    assert(get(t,0) == 'c');
    assert(get(t,1) == 'a');
    assert(get(t,2) == 't');
    discard(t);
}

void testSet() {
    text *t = new("cat");
    set(t, 0, 'b');
    set(t, 2, 'r');
    assert(like(t, "bar"));
    discard(t);
}

void testCopy() {
    text *t = new("cat");
    text *t2 = copy(t);
    assert(like(t2, "cat"));
    discard(t);
    discard(t2);
}

void testCompare() {
    text *t = new("cat");
    text *t2 = new("cat");
    assert(compare(t, t2) == 0);
    text *t3 = new("cas");
    assert(compare(t, t3) > 0);
    text *t4 = new("cau");
    assert(compare(t, t4) < 0);
    discard(t);
    discard(t2);
    discard(t3);
    discard(t4);
}

void testAppend() {
    text *t = new("car");
    text *t2 = new("pet");
    append(t, t2);
    assert(like(t, "carpet"));
    discard(t);
    discard(t2);
}

void testSlice() {
    text *t = new("carpet");
    text *t2 = slice(t, 0, 3);
    assert(like(t2, "car"));
    text *t3 = slice(t, 3, 6);
    assert(like(t3, "pet"));
    discard(t);
    discard(t2);
    discard(t3);
}

void testFind() {
    text *t = new("carpet");
    text *t2 = new("car");
    assert(find(t, t2) == 0);
    text *t3 = new("pet");
    assert(find(t, t3) == 3);
    text *t4 = new("cat");
    assert(find(t, t4) == -1);
    discard(t);
    discard(t2);
    discard(t3);
    discard(t4);
}

// Test the library.  (With a real library, a renaming scheme would be needed.)
int textMain() {
    testNew();
    testLength();
    testGet();
    testSet();
    testCopy();
    testCompare();
    testAppend();
    testSlice();
    testFind();
    printf("Tests all pass.\n");
    return 0;
}

