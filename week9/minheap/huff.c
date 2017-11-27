/*
* @Author: kolunderr
* @Date:   2017-11-21 11:45:32
* @Last Modified by:   pew
* @Last Modified time: 2017-11-26 15:53:58
*/

#include "minheap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


int main() {
	int arr[] = {1,23,712,122,24,88};
	heap *h = new_heap(arr, 6);
	node *m = remove_root(h);
	printf("Min element : %d\n",m->data);
	node *n = remove_root(h);
	printf("Min element : %d\n",n->data);

	free(h);

}


