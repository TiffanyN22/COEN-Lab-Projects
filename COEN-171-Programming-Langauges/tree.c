/*
 * Reads a list of integers from standard input and inserts them into
 * a binary search tree.  Then, reads a list of integers from standard
 * input and checks if each integer is present in the tree.  Both
 * lists are terminated by -1.
 */

# include <stdio.h>
# include <stdlib.h>

typedef struct node *tree;

struct node {
    int  info;
    tree left;
    tree right;
};


/*
 * Inserts an integer into the specified binary search tree.  If the
 * integer is already present in the tree, then the tree is unchanged.
 * If the tree is NULL, then a single node is created as the tree.
 * Otherwise, a new node is created at the appropriate place in the
 * tree.  The root of the subtree is returned.
 */

tree insert(tree root, int value)
{
    if (root == NULL) {
	root = malloc(sizeof(struct node));
	root->left = NULL;
	root->right = NULL;
	root->info = value;

    } else if(root->info < value) {
	root->right = insert(root->right, value);

    } else if (root -> info > value)
	root->left = insert(root->left, value);

    return root;
}


/*
 * Returns nonzero if the value is found in the specified binary
 * search tree.  If the value is not found then zero is returned.
 */

int member(tree root, int value)
{
    if (root == NULL)
	return 0;

    if (value < root->info)
	return member(root->left, value);

    if (value > root->info)
	return member(root->right, value);

    return 1;
}


int main(void)
{
    tree t;
    int x;


    t = NULL;
    scanf("%d", &x);

    while (x != -1) {
	t = insert(t, x);
	scanf("%d", &x);
    }

    scanf("%d", &x);

    while (x != -1) {
	printf("%s\n", member(t, x) ? "true" : "false");
	scanf("%d", &x);
    }

    return 0;
}
