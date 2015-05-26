#include "skip_tree.h"
#include <stdio.h>
#include <stdlib.h>

static skip_tree_node* s;
static skip_tree_node* s_root = NULL;
static skip_tree_node* d_root = NULL;
static int len = 0;

int contains(int key)
{
    return s[key].data != NULL;
}

static inline int is_subtree_root(skip_tree_node* node)
{
    if(node == NULL)
    {
        return 1;
    }

    return (node->d_lchild != NULL) && (node->d_rchild != NULL);
}

static inline int stn_ptr_to_int(skip_tree_node* node)
{
    if(node == NULL)
    {
        return -1;
    }

    return node - s;
}

void print_node(int key)
{
    if(s_root == NULL)
    {
        printf("Uninitialized tree\n\n");
        return;
    }

    printf("Node %d: Static: (%d, %d, %d)\n        Dyamnic:(%d, %d, %d)\n", key,
            stn_ptr_to_int(s[key].s_par), stn_ptr_to_int(s[key].s_lchild),
            stn_ptr_to_int(s[key].s_rchild), stn_ptr_to_int(s[key].d_par),
            stn_ptr_to_int(s[key].d_lchild), stn_ptr_to_int(s[key].d_rchild));
}

static inline int flip(int i)
{
    return i == 0 ? 1 : 0;
}

static void __print_stree(skip_tree_node* node, int level, int* print_branchs)
{
    if(node == NULL)
    {
        return;
    }

    print_branchs[level+1] = 1;

    print_branchs[level] = flip(print_branchs[level]);

    __print_stree(node->s_rchild, level + 1, print_branchs);

    print_branchs[level] = flip(print_branchs[level]);

    if(level != 0)
    {
        printf("    ");
    }

    for(int i = 1; i < level; i++)
    {
        if(print_branchs[i])
        {
            printf("|   ");
        }
        else
        {
            printf("    ");
        }
    }

    printf("+---%d\n", stn_ptr_to_int(node));

    print_branchs[level+1] = 0;

    __print_stree(node->s_lchild, level + 1, print_branchs);
}

void print_stree(void)
{
    printf("\n\n---------------------------------\n\n");

    if(s_root == NULL)
    {
        printf("Uninitialized tree\n\n");
        return;
    }

    int print_branchs[10] = {0};

    __print_stree(s_root, 0, print_branchs);

    printf("\n\n---------------------------------\n\n");
}

static void __print_dtree(skip_tree_node* node, int level, int* print_branchs)
{
    if(node == NULL)
    {
        return;
    }

    print_branchs[level+1] = 1;

    print_branchs[level] = flip(print_branchs[level]);

    __print_dtree(node->d_rchild, level + 1, print_branchs);

    print_branchs[level] = flip(print_branchs[level]);

    if(level != 0)
    {
        printf("    ");
    }

    for(int i = 1; i < level; i++)
    {
        if(print_branchs[i] == 1)
        {
            printf("|   ");
        }
        else
        {
            printf("    ");
        }
    }

    printf("+---%d\n", stn_ptr_to_int(node));

    print_branchs[level+1] = 0;

    __print_dtree(node->d_lchild, level + 1, print_branchs);
}

void print_dtree(void)
{
    printf("\n\n---------------------------------\n\n");

    if(s_root == NULL)
    {
        printf("Uninitialized tree\n\n");
        return;
    }

    if(d_root == NULL)
    {
        printf("Empty tree\n\n");
        return;
    }

    int print_branchs[10] = {0};

    __print_dtree(d_root, 0, print_branchs);

    printf("\n\n---------------------------------\n\n");
}

void insert(int key, void * data)
{
    printf("Inserting %d\n", key);

    if(s_root == NULL)
    {
        printf("Uninitialized tree\n\n");
        return;
    }

    if(s[key].data)
    {
        printf("Node %d occupied\n", key);
    }

    if(d_root == NULL || s[key].d_lchild == d_root || s[key].d_rchild == d_root)
    {
        d_root = s + key;
    }

    s[key].data = data;
    skip_tree_node * child = s + key, *current = s + key;

    if(is_subtree_root(current))
    {
        return;
    }

    if(current->d_rchild != NULL)
    {
        (current->d_rchild)->d_par = current;
    }

    if(current->d_lchild != NULL)
    {
        (current->d_lchild)->d_par = current;
    }

    while(1)
    {
        skip_tree_node* last = current;
        current = current->s_par;

        if(current == NULL)
        {
            child->d_par = current;
            break;
        }
        else if(is_subtree_root(current) || current->data)
        {
            if(current < last)
            {
                current->d_rchild = child;
            }
            else {
                current->d_lchild = child;
            }

            child->d_par = current;
            break;
        }
        else
        {
            if(current < last)
            {
                current->d_rchild = child;
            }
            else
            {
                current->d_lchild = child;
            }

            if(is_subtree_root(current))
            {
                (current->d_lchild)->d_par = current;
                (current->d_rchild)->d_par = current;
                child = current;

                if(d_root == current->d_lchild || d_root == current->d_rchild)
                {
                    d_root = current;
                }
            }
        }
    }
}

static inline skip_tree_node* get_child(skip_tree_node* node)
{
    return node->d_lchild == NULL ? node->d_rchild : node->d_lchild;
}

void erase(int key)
{
    printf("Erasing %d\n", key);

    if(s_root == NULL)
    {
        printf("Uninitialized tree\n\n");
        return;
    }

    if(s[key].data == NULL)
    {
        printf("Erase failed: Key %d does not exist\n", key);
        return;
    }

    s[key].data = NULL;

    if(is_subtree_root(s + key))
    {
        return;
    }
    else if (s[key].d_lchild != NULL)
    {
        (s[key].d_lchild)->d_par = s[key].d_par;
    }
    else if (s[key].d_rchild != NULL)
    {
        (s[key].d_rchild)->d_par = s[key].d_par;
    }

    skip_tree_node* child = get_child(s + key), *current = s + key;

    if(d_root == s + key)
    {
        d_root = child;
    }

    while(1)
    {
        skip_tree_node* last = current;
        current = current->s_par;

        if(current == NULL)
        {
            return;
        }

        int was_subtree_root = is_subtree_root(current);

        if(current > last)
        {
            current->d_lchild = child;
        }
        else
        {
            current->d_rchild = child;
        }

        if(current->data != NULL)
        {
            break;
        }

        if(is_subtree_root(current))
        {
            break;
        }

        if(was_subtree_root)
        {
            child = get_child(current);
            child->d_par = current->d_par;
        }

        if(current == d_root && current->data == NULL)
        {
            d_root = get_child(current);
        }
    }
}

int predecessor(int key)
{
    if(s_root == NULL)
    {
        printf("Uninitialized tree\n\n");
        return -1;
    }

    if(s[key].data == NULL)
    {
        printf("Element with key %d has not yet been inserted\n", key);
    }

    skip_tree_node* current = s + key;

    if(current->d_lchild != NULL)
    {
        current = current->d_lchild;

        while(current->d_rchild != NULL)
        {
            current = current->d_rchild;
        }

        return stn_ptr_to_int(current);
    }
    else
    {
        skip_tree_node* prev;

        do
        {
            prev = current;
            current = current->d_par;
        } while(current != NULL && current > prev);

        if(current == NULL)
        {
            return -1;
        }

        if(current->data)
        {
            return stn_ptr_to_int(current);
        }

        current = current->d_lchild;

        while(current->d_rchild != NULL)
        {
            current = current->d_rchild;
        }

        return stn_ptr_to_int(current);
    }
}

int successor(int key)
{
    if(s_root == NULL)
    {
        printf("Uninitialized tree\n\n");
        return -1;
    }

    if(s[key].data == NULL)
    {
        printf("Element with key %d has not yet been inserted\n", key);
    }

    skip_tree_node* current = s + key;

    if(current->d_rchild != NULL)
    {
        current= current->d_rchild;
        while(current->d_lchild != NULL)
        {
            current = current->d_lchild;
        }

        return stn_ptr_to_int(current);
    }
    else
    {
        skip_tree_node* prev;

        do
        {
            prev = current;
            current = current->d_par;
        } while(current != NULL && current < prev);

        if(current == NULL)
        {
            return -1;
        }

        if(current->data)
        {
            return stn_ptr_to_int(current);
        }

        current = current->d_rchild;

        while(current->d_lchild != NULL)
        {
            current = current->d_lchild;
        }

        return stn_ptr_to_int(current);
    }
}

static skip_tree_node* set_structure(int left_bound, int right_bound, skip_tree_node* par)
{
    int node = left_bound + (right_bound - left_bound) / 2;
    s[node].s_par =  par;
    s[node].d_par = NULL;
    s[node].d_lchild = NULL;
    s[node].d_rchild = NULL;
    s[node].data = NULL;

    if(left_bound != node)
    {
        s[node].s_lchild = set_structure(left_bound, node - 1, s + node);
    }
    else
    {
        s[node].s_lchild = NULL;
    }

    if(right_bound != node)
    {
        s[node].s_rchild = set_structure(node + 1, right_bound, s + node);
    }
    else
    {
        s[node].s_rchild = NULL;
    }

    return s + node;
}

int init(int length)
{
    if((s = malloc(length * sizeof(skip_tree_node))) == NULL)
    {
        return 1;
    }

    s_root = set_structure(0, length - 1, NULL);
    d_root = NULL;

    len = length;

    return 0;
}

void destroy(void)
{
    if(s_root == NULL)
    {
        printf("Uninitialized tree\n\n");
        return;
    }

    if(s)
    {
        free(s);
    }

    s_root = NULL;
    d_root = NULL;
    len = 0;
}
