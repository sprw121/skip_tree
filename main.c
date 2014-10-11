#include <stdio.h>
#include "skip_tree.h"

int main() {
	int x;
	init(15);

	print_stree();

	print_dtree();

	insert(1, &x);

	insert(2, &x);

	insert(3, &x);

	insert(4, &x);

	erase(1);
	
	insert(4, &x);

	erase(2);

	erase(3);

	insert(5, &x);

	insert(11, &x);
	print_dtree();

	erase(1);

	erase(11);
	print_dtree();

	destroy();

	return 0;
}
