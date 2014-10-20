#include <stdio.h>
#include "skip_tree.h"

#define SIZE 15

void print_ps(int key) {
	printf("Node %d:  Predecessor: %d  Sucessor: %d\n", key, predecessor(key), successor(key));
}

void print_pss(){
	for(int i = 0; i < SIZE; i++) {
		if(contains(i)) {
			print_ps(i);
		}
	}
}

int main() {
	int x;
	init(SIZE);

	print_stree();

	print_dtree();

	insert(1, &x);
	print_dtree();
	print_pss();

	insert(2, &x);
	print_dtree();
	print_pss();

	insert(3, &x);
	print_dtree();
	print_pss();

	erase(3);
	print_dtree();
	print_pss();

	insert(4, &x);
	print_dtree();
	print_pss();

	erase(1);
	print_dtree();
	print_pss();
	
	insert(4, &x);
	print_dtree();
	print_pss();

	erase(2);
	print_dtree();
	print_pss();

	insert(5, &x);
	print_dtree();
	print_pss();

	insert(11, &x);
	print_dtree();
	print_pss();

	erase(11);
	print_dtree();
	print_pss();

	destroy();

	return 0;
}
