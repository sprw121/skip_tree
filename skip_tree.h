typedef struct skip_tree_node {
	struct skip_tree_node* s_par;			// The node's parent in the pre-structure, static
	struct skip_tree_node* s_lchild;		// The node's left child in the pre-structre, static
	struct skip_tree_node* s_rchild;		// The node's right child in the pre-structure, static
	struct skip_tree_node* d_par;			// The node's search parent, dyanmic
	struct skip_tree_node* d_lchild;		// The node's search left child, dynamic
	struct skip_tree_node* d_rchild;		// The node's search right child, dyanmic
	void * data;
} skip_tree_node;

int init(int);
void destroy(void);
void insert(int, void *);
void erase(int);
void print_dtree(void);
void print_stree(void);
void print_node(int);
int successor(int);
int predecessor(int);
int contains(int);
