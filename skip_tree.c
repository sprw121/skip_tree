#include "skip_tree.h"
#include <stdio.h>
#include <stdlib.h>

static skip_tree_node * s;
static int s_root = -1;
static int d_root = -1;
static int len = 0;

int is_subtree_root(int key) {
	if(key == -1) {
		return 1;
	}

	return (s[key].d_lchild != -1) && (s[key].d_rchild != -1);
}

void print_node(int key) {
	if(s_root == -1) {
		printf("Uninitialized tree\n\n");
		return;
	}

	printf("Node %d: Static: (%d, %d, %d)\n        Dyamnic:(%d, %d, %d)\n", key,
			s[key].s_par, s[key].s_lchild, s[key].s_rchild,
			s[key].d_par, s[key].d_lchild, s[key].d_rchild);
}

void __print_stree(int root, int level, int* print_branchs) {
	if(root == -1) {
		return;
	}

	print_branchs[level+1] = 1;

	int flip = print_branchs[level];

	if(print_branchs[level]) {
		print_branchs[level] = 0;
	} else{
		print_branchs[level] = 1;
	}

	__print_stree(s[root].s_rchild, level + 1, print_branchs);
	print_branchs[level] = flip;

	for(int i = 0; i < level; i++) {
		if(print_branchs[i] == 1) {
			printf("|   ");	
		} else{
			printf("    ");	
		}
	}

	printf("+---%d\n", root);

	print_branchs[level+1] = 0;

	__print_stree(s[root].s_lchild, level + 1, print_branchs);
}

void print_stree(void) {
	printf("\n\n---------------------------------\n\n");

	if(s_root == -1) {
		printf("Uninitialized tree\n\n");
		return;
	}

	int print_branchs[10] = {0};

	print_branchs[0] = 2;
	__print_stree(s_root, 0, print_branchs);

	printf("\n\n---------------------------------\n\n");
}

void __print_dtree(int root, int level, int* print_branchs) {
	if(root == -1) {
		return;
	}

	print_branchs[level+1] = 1;

	int flip = print_branchs[level];

	if(print_branchs[level]) {
		print_branchs[level] = 0;
	} else{
		print_branchs[level] = 1;
	}

	__print_dtree(s[root].d_rchild, level + 1, print_branchs);
	print_branchs[level] = flip;

	for(int i = 0; i < level; i++) {
		if(print_branchs[i] == 1) {
			printf("|   ");	
		} else{
			printf("    ");	
		}
	}

	printf("+---%d\n", root);

	print_branchs[level+1] = 0;

	__print_dtree(s[root].d_lchild, level + 1, print_branchs);
}

void print_dtree(void) {
	printf("\n\n---------------------------------\n\n");
	if(s_root == -1) {
		printf("Uninitialized tree\n\n");
		return;
	}

	if(d_root == -1) {
		printf("Empty tree\n\n");
		return;
	}

	int print_branchs[10] = {0};
	print_branchs[0] = 2;

	__print_dtree(d_root, 0, print_branchs);

	printf("\n\n---------------------------------\n\n");
}

void insert(int key, void * data) {
	printf("Inserting %d\n", key);

	if(s_root == -1) {
		printf("Uninitialized tree\n\n");
		return;
	}

	if(d_root == -1 || s[key].d_lchild == d_root || s[key].d_rchild == d_root) {
		d_root = key;
	}

	s[key].data = data;
	int child = key, current = key;

	if(is_subtree_root(key)) {
		return;
	}

	if(s[current].d_rchild != -1) {
		s[s[current].d_rchild].d_par = current;
	}

	if(s[current].d_lchild != -1) {
		s[s[current].d_lchild].d_par = current;
	}

	while(1) {
		int last = current;
		current = s[current].s_par;

		if(current == -1) {
			s[child].d_par = current;
			break;
		} else if(is_subtree_root(current)) {
			if(current < last) {
				s[current].d_rchild = child;
			} else {
				s[current].d_lchild = child;
			}

			s[child].d_par = current;
			break;
		} else {
			if(current < last) {
				s[current].d_rchild = child;
			} else {
				s[current].d_lchild = child;
			}

			if(is_subtree_root(current)) {
				s[s[current].d_lchild].d_par = current;
				s[s[current].d_rchild].d_par = current;
				child = current;

				if(d_root == s[current].d_lchild || d_root == s[current].d_rchild) {
					d_root = current;
				}
			}
		}
	}
}

static inline int get_child(int key) {
	return s[key].d_lchild == -1 ? s[key].d_rchild : s[key].d_lchild;
}

void erase(int key) {
	printf("Erasing %d\n", key);

	if(s_root == -1) {
		printf("Uninitialized tree\n\n");
		return;
	}

	if(s[key].data == NULL) {
		printf("Erase failed: Key %d does not exist\n", key);
		return;
	}

	s[key].data = NULL;

	if(is_subtree_root(key)) {
		return;
	} else if (s[key].d_lchild != -1) {
		s[s[key].d_lchild].d_par = s[key].d_par;
	} else if (s[key].d_rchild != -1) {
		s[s[key].d_rchild].d_par = s[key].d_par;
	}

	int child = get_child(key), current = key;

	if(d_root == key) {
		d_root = child;
	}

	while(1) {
		int last = current;
		current = s[current].s_par;

		if(current == -1) {
			return;
		}

		int was_subtree_root = is_subtree_root(current);

		if(current > last) {
			s[current].d_lchild = child;
		} else {
			s[current].d_rchild = child;
		}

		if(s[current].data != NULL) {
			break;
		}

		if(is_subtree_root(current)) {
			break;
		}

		if(was_subtree_root) {
			child = get_child(current);
			s[child].d_par = s[current].d_par;
		}

		if(current == d_root && s[current].data == NULL) {
			d_root = get_child(current);
		}
	}
}

int predecessor(int key) {
	if(s_root == -1) {
		printf("Uninitialized tree\n\n");
		return -1;
	}

	if(s[key].data == NULL) {
		printf("Element with key %d has not yet been inserted\n", key);
	}

	if(s[key].d_lchild != -1) {
		key = s[key].d_lchild;

		while(s[key].d_rchild != -1) {
			key = s[key].d_rchild;
		}

		return key;
	} else {
		int prev;

		do {
			prev = key;
			key = s[key].d_par;
		} while(key != -1 && key > prev);

		if(key == -1) {
			return -1;
		}

		if(s[key].data) {
			return key;
		}

		key = s[key].d_lchild;

		while(s[key].d_rchild != -1) {
			key = s[key].d_rchild;
		}

		return key;
	} 
}

int successor(int key) {
	if(s_root == -1) {
		printf("Uninitialized tree\n\n");
		return -1;
	}

	if(s[key].data == NULL) {
		printf("Element with key %d has not yet been inserted\n", key);
	}

	if(s[key].d_rchild != -1) {
		key = s[key].d_rchild;
		while(s[key].d_lchild != -1) {
			key = s[key].d_lchild;
		}

		return key;
	} else {
		int prev;

		do {
			prev = key;
			key = s[key].d_par;
		} while(key != -1 && key < prev);

		if(key == -1) {
			return -1;
		}

		if(s[key].data) {
			return key;
		}

		key = s[key].d_rchild;

		while(s[key].d_lchild != -1) {
			key = s[key].d_lchild;
		}

		return key;
	} 
}

int set_structure(int left_bound, int right_bound, int par) {
	int node = left_bound + (right_bound - left_bound) / 2;
	s[node].s_par = par;
	s[node].d_par = -1;
	s[node].d_lchild = -1;
	s[node].d_rchild = -1;
	s[node].data = NULL;

	if(left_bound != node) {
		s[node].s_lchild = set_structure(left_bound, node - 1, node);
	} else {
		s[node].s_lchild = -1;
	}

	if(right_bound != node) {
		s[node].s_rchild = set_structure(node + 1, right_bound, node);
	} else {
		s[node].s_rchild = -1;
	}

	return node;
}

int init(int l) {
	if((s = malloc(l * sizeof(skip_tree_node))) == NULL) {
		return 1;
	}

	s_root = set_structure(0, l - 1, -1);
	d_root = -1;

	len = l;

	return 0;
}

void destroy(void) {
	if(s_root == -1) {
		printf("Uninitialized tree\n\n");
		return;
	}

	if(s) {
		free(s);
	}

	s_root = -1;
	d_root = -1;
	len = 0;
}
