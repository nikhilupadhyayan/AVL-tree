#include"avl.h"
#include<stdio.h>
#include<stdlib.h>

int main()
{
	node_t *avl=0;
	int k,z,opt;
	while(1)
	{
		printf("\n1.Insert\n2.Display\n3.Search\n4.free tree\n5.Exit\n");
		scanf("%d",&opt);
		printf("\n");
		switch(opt)
		{
			case 1: printf("\nEnter the no of nodes : ");
				scanf("%d",&k);
				make(&avl,k);
				break;

			case 2: display(avl);
				break;

			case 3: printf("\nEnter the element to be searched : ");
				scanf("%d",&z);
				search(avl,z);
				printf("\n");
				break;

			case 4: free_node(&avl);
				avl=NULL;
				break;

			case 5:	free_node(&avl);
				exit(0);
				break;

			default: printf("\nInvalid input\n");
		}
	}
	return 0;
}
