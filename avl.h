#ifndef AVL_H
#define AVL_H

struct node
{
	int key;
	struct node *llink;
	struct node *rlink;
	int h;
	int bf;
};
typedef struct node node_t;


int maxq(int a, int b);				//returns the maximum of two
void balance_factor(node_t *treeptr);		//calculates the balance factor
void balancee(node_t **treeptr);		//balances the unbalanced tree
void insert(node_t **treeptr, node_t *temp);	//inserts a node into the tree
int height(node_t *temp);			//calculates the height of each node
void traverse(node_t *treeptr, node_t **parent, node_t **child,node_t **cur);	//finds the parent, child and current node
void find_gp(node_t *treeptr, node_t *parent, node_t **gp);			//finds the grand parent
void search(node_t *treeptr, int z);		//searches a given key value
void make(node_t **treeptr,int n);		//makes a tree
void free_node(node_t **treeptr);		//it will free all the nodes
void inorder(node_t *treeptr);			//displays in INORDER fashion
void display(node_t *treeptr);			//displays the tree


#endif
