#include <stdio.h>
#include "skip_tree.h"

int main() {
	int x;
	init(15);

	print_stree();

	print_dtree();

	insert(1, &x);
	print_dtree();
	print_node(1);
	print_node(2);
	print_node(3);
	print_node(7);

	insert(2, &x);
	print_dtree();
	print_node(1);
	print_node(2);
	print_node(3);
	print_node(7);

	insert(3, &x);
	print_dtree();
	print_node(1);
	print_node(2);
	print_node(3);
	print_node(7);

	insert(4, &x);
	print_dtree();

	erase(1);
	print_dtree();
	
	insert(4, &x);
	print_dtree();

	erase(2);
	print_dtree();

	erase(3);
	print_dtree();

	insert(5, &x);
	print_dtree();

	insert(11, &x);
	print_dtree();

	erase(11);
	print_dtree();

	destroy();

	return 0;
}
