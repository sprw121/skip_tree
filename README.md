# Overview

This data structure uses a binary tree format to store ordered data. Rather than constructing the
tree as dyanmicaly as data is input, this data structure pre-structures a binary tree the size of
the input space at initialization, and then fills in this tree as data is added. This leads to
some interesting properties, namely that the insertion and deletion operations get faster as the
tree gets denser. Each node in the tree has two sets of children and parents. The first set is
generated at initialization and remains static through the life of the tree. The second set, named
the skip parents and skip children, are used to navigate the data the has been input thus far, and
thus dyanmic in the runtime. This is not a balanced search tree, however the degree of inbalance
is bounded by the height of the tree (O(log(N)).

# Properties

Letting N be the input space size and n be the current number of elements held by the tree, the
upper bounds on different operations is as follows:

*	Insertion: O(log(N/n))
*	Deletion: O(log(N/n))
*	Next/Previous element lookup: O(log(n))
*	Membership test: O(1)
