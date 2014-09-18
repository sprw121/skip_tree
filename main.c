#include <stdio.h>
#include "skip_tree.h"

int main() {
	int x;
	init(14);

	print_in_order();

	insert(1, &x);
	insert(3, &x);

	print_in_order();

	destroy();

	return 0;
}
