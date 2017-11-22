/*
* @Author: kolunderr
* @Date:   2017-11-21 11:45:32
* @Last Modified by:   kolunderr
* @Last Modified time: 2017-11-21 14:47:23
*/

#include "minheap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


int main() {
	int arr[] = {66,23,712,122,24,88};
	heap *h = new_heap(arr, 6);
	node *m = get_min(h);
	printf("Min element : %d\n",m->data);
	node *n = get_min(h);
	printf("Min element : %d\n",n->data);

	free(h);

}


