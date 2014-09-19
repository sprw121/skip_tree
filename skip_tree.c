#include "skip_tree.h"
#include <stdio.h>
#include <stdlib.h>

static skip_tree_node * s;
static int root;
static int len;

int is_subtree_root(int key) {
	if(s[key].par == -1)
		return 1;

	return (s[key].s_lchild != -1) && (s[key].s_rchild != -1);
}

void print_in_order_(int node) {
	if(node == -1)
		return;

	print_in_order_(s[node].lchild);

	fprintf(stderr, "%d\n   %d %d %d\n   %d %d %d\n",
			node, s[node].par, s[node].lchild, s[node].rchild,
			s[node].s_par, s[node].s_lchild, s[node].s_rchild);

	print_in_order_(s[node].rchild);
}

void print_in_order(void) {
	fprintf(stderr, "Printing\n");
	print_in_order_((len-1)/2);
}

void insert(int key, void * data) {
	s[key].data = data;
	int child = key, current = key;

	if(is_subtree_root(key))
		return;

	while(1) {
		int last = current;
		current = s[current].par;

		if(is_subtree_root(current)) {
			if(current < last) {
				s[current].s_rchild = child;
			} else {
				s[current].s_lchild = child;
			}

			s[child].s_par = current;
			break;
		} else {
			if(current < last) {
				s[current].s_rchild = child;
			} else {
				s[current].s_lchild = child;
			}

			if(is_subtree_root(current)) {
				s[s[current].s_lchild].s_par = current;
				s[s[current].s_rchild].s_par = current;
				child = current;
			}
		}
	}
}

int get_child(int key) {
	return s[key].s_lchild == -1 ? s[key].s_rchild : s[key].s_lchild;
}

void erase(int key) {
	s[key].data = NULL;

	if(is_subtree_root(key)) {
		return;
	} else if (s[key].s_lchild != -1) {
		s[s[key].s_lchild].s_par = s[key].s_par;
	} else if (s[key].s_rchild != -1) {
		s[s[key].s_rchild].s_par = s[key].s_par;
	}

	int child = get_child(key), current = key;

	while(1) {
		int last = current;
		current = s[current].par;
		int was_subtree_root = is_subtree_root(current);

		if(current > last) {
			s[current].s_lchild = child;
		} else {
			s[current].s_rchild = child;
		}

		if(s[current].data != NULL) {
			break;
		}

		if(is_subtree_root(current)) {
			break;
		}

		if(was_subtree_root) {
			child = get_child(current);
			s[child].s_par = s[current].s_par;
		}
	}
}

int set_structure(int left_bound, int right_bound, int par) {
	int node = left_bound + (right_bound - left_bound) / 2;
	s[node].par = par;
	s[node].s_par = -1;
	s[node].s_lchild = -1;
	s[node].s_rchild = -1;

	if(left_bound != node) {
		s[node].lchild = set_structure(left_bound, node - 1, node);
	} else {
		s[node].lchild = -1;
	}

	if(right_bound != node) {
		s[node].rchild = set_structure(node + 1, right_bound, node);
	} else {
		s[node].rchild = -1;
	}

	return node;
}

int init(int l) {
	if((s = (skip_tree_node*) malloc(l * sizeof(skip_tree_node))) == NULL) {
		return 1;
	}

	root = set_structure(0, l - 1, -1);

	len = l;

	return 0;
}

void destroy(void) {
	if(s)
		free(s);

	len = 0;
}
