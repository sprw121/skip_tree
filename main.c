#include <stdio.h>
#include "skip_tree.h"

int main() {
	int x;
	init(15);

	print_tree();

	print_stree();

	insert(1, &x);
	print_stree();
	insert(3, &x);
	print_stree();
	insert(11, &x);
	print_stree();
	erase(1);
	print_stree();
	erase(3);
	print_stree();
	erase(11);
	print_stree();

	destroy();

	return 0;
}
