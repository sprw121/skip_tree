typedef struct skip_tree_node {
	int par;			// The node's parent in the pre-structure, static
	int lchild;			// The node's left child in the pre-structre, static
	int rchild;			// The node's right child in the pre-structure, static
	int s_par;			// The node's search parent, dyanmic
	int s_lchild;		// The node's search left child, dynamic
	int s_rchild;		// The node's search right child, dyanmic
	void * data;
} skip_tree_node;

int init(int);
void destroy(void);
void insert(int, void *);
void erase(int);
void print_tree(void);
void print_stree();
void print_node(int);
int successor(int);
int predecessor(int);
