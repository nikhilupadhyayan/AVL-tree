#include"avl.h"
#include<stdio.h>
#include<stdlib.h>

void make(node_t **treeptr,int n)		//makes the tree
{
	int i;
	node_t *temp=0;
	for(i=0;i<n;++i)
	{
		temp=(node_t *)malloc(sizeof(node_t));
		printf("\nEnter the key : ");
		scanf("%d",&temp->key);
		temp->rlink=0;
		temp->llink=0;
		insert(treeptr,temp);
		balance_factor(*treeptr);
		balancee(treeptr);
		balance_factor(*treeptr);
	}
}

void insert(node_t **treeptr, node_t *temp)		//inserts a node inside the tree
{
	if(*treeptr==NULL)
		*treeptr=temp;
	else
	{
		node_t *cur=*treeptr;
		node_t *prev=0;
		while(cur)
		{
			prev=cur;
			if(temp->key<cur->key)
				cur=cur->llink;
			else
				cur=cur->rlink;
		}
		if(temp->key<prev->key)
			prev->llink=temp;
		else
			prev->rlink=temp;
	}
}


void inorder(node_t *treeptr)			//displays in INORDER fashion
{
	if(treeptr)
	{
		inorder(treeptr->llink);
		printf("%d\t\t%d\n",treeptr->key,treeptr->bf);
		inorder(treeptr->rlink);
	}
}

void display(node_t *treeptr)			//displays the tree
{
	printf("\n-------------------------------------\n");
	printf("\nValue | Balance factor\n");
	printf("\n-------------------------------------\n");
	inorder(treeptr);
	printf("\n-------------------------------------\n");
}


void balance_factor(node_t *treeptr)		//calculates the balnace factor of each node
{
	node_t *temp=treeptr;
	if(temp)
	{
		temp->h=height(temp);
		temp->bf=(height(temp->llink)-height(temp->rlink));
		balance_factor(temp->llink);
		balance_factor(temp->rlink);
	}
}


int height(node_t *temp)			//calculates the height of each node
{
	int h;
	if(temp==NULL)
		h=0;
	else
		h=maxq(height(temp->llink),height(temp->rlink))+1;
	return h;
}

int maxq(int a, int b)				//returns the maximum of two
{
	return (a>b)?a:b;
}

void traverse(node_t *treeptr, node_t **parent, node_t **child,node_t **cur)	//finds the parent, child and current node
{
	node_t *temp=treeptr;
	if(temp)
	{
		if(temp->bf==2||temp->bf==-2)
		{

			if((temp->h)<((*parent)->h))
				*parent=temp;
			{
				if(temp->bf==2)
						*cur=(*parent)->llink;
				else
						*cur=(*parent)->rlink;
				if((*cur)->bf==1)
						*child=(*cur)->llink;
				if((*cur)->bf==-1)
						*child=(*cur)->rlink;
			}

		}
		traverse(temp->llink,parent,child,cur);
		traverse(temp->rlink,parent,child,cur);
	}
}

void find_gp(node_t *treeptr, node_t *parent, node_t **gp)		//finds the grand parent
{
	node_t *temp=treeptr;
	if(temp)
	{
		if(temp->rlink==parent)
		{
			*gp=temp;
			(*gp)->rlink=parent;
		}
		if(temp->llink==parent)
		{
			*gp=temp;
			(*gp)->llink=parent;
		}
		find_gp(temp->llink,parent,gp);
		find_gp(temp->rlink,parent,gp);
	}
}

void balancee(node_t **treeptr)			//balances the unbalanced tree
{
	node_t *gp=*treeptr;
	node_t *parent=*treeptr;
	node_t *child=0;
	node_t *temp=*treeptr;

	traverse(*treeptr,&parent,&child,&temp);
	find_gp(*treeptr,parent,&gp);

	if(parent->bf==2||parent->bf==-2)
	{

		node_t *q=child->rlink;
		node_t *r=child->llink;
		node_t *s=temp->llink;
		node_t *t=temp->rlink;
		node_t *p=parent->rlink;
		node_t *u=parent->llink;


		if(parent->bf==2)
		{
			if(temp->bf==1)					//LL case
			{
				if(gp->llink==parent)
					gp->llink=temp;
				if(gp->rlink==parent)
					gp->rlink=temp;
				if(gp==parent)
					*treeptr=temp;
				temp->rlink=parent;
				temp->llink=child;
				if(t!=NULL)
					parent->llink=t;
				else parent->llink=0;
				printf("\nLL case\n");
			}

			if(temp->bf==-1)				//LR case
			{
				if(gp->llink==parent)
					gp->llink=child;
				if(gp->rlink==parent)
					gp->rlink=child;
				if(gp==parent)
					*treeptr=child;
				child->rlink=parent;
				child->llink=temp;
				if(q!=NULL)
					temp->rlink=r;
				else temp->rlink=0;
				if(s!=NULL)
					temp->llink=s;
				else temp->llink=0;
				if(r!=NULL)
					parent->llink=q;
				else parent->llink=0;
				printf("\nLR case\n");

			}
			if(p!=NULL)
				parent->rlink=p;
			else parent->rlink=0;
		}

		if(parent->bf==-2)
		{
			if(temp->bf==1)					//RL case
			{
				if(gp->llink==parent)
					gp->llink=child;
				if(gp->rlink==parent)
					gp->rlink=child;
				if(gp==parent)
					*treeptr=child;
				child->llink=parent;
				child->rlink=temp;
				if(t!=NULL)
					temp->rlink=t;
				else temp->rlink=0;
				if(q!=NULL)
				temp->llink=q;
				else temp->llink=0;
				if(r!=NULL)
					parent->rlink=r;
				else parent->rlink=0;
				printf("\nRL case\n");
			}

			if(temp->bf==-1)				//RR case
			{
				if(gp->llink==parent)
					gp->llink=temp;
				if(gp->rlink==parent)
					gp->rlink=temp;
				if(gp==parent)
					*treeptr=temp;
				temp->llink=parent;
				temp->rlink=child;
				if(s!=NULL)
					parent->rlink=s;
				else parent->rlink=0;
				printf("\nRR case\n");
			}
			if(u!=NULL)
				parent->llink=u;
			else parent->llink=0;
		}
	}
}

void search(node_t *treeptr, int z)			//searches the given node in the tree
{
	node_t *temp=treeptr;
	if(temp)
	{
		if(z<temp->key)
			search(temp->llink,z);
		if(z>temp->key)
			search(temp->rlink,z);
		if(z==temp->key)
			printf("\nElement found\n");
	}
	else
	printf("\nElement not found\n");
}

void free_node(node_t **treeptr)			//it will free all the nodes of tree
{
	node_t *rnode,*lnode;
	if(*treeptr)
	{
		rnode=(*treeptr)->rlink;
		lnode=(*treeptr)->llink;
		free(*treeptr);
		free_node(&rnode);
		free_node(&lnode);
	}
}
