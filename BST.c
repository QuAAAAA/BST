#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define root (*root)

typedef struct listNode* listPointer;
typedef struct listNode {
	int data ;
	listPointer parent_node;
	listPointer left_node;
	listPointer right_node;
};

listPointer inorder_traversal(listPointer current);
listPointer Insert(listPointer root, int data);
listPointer FindMax(listPointer root);
listPointer Delete(listPointer root, int data);
listPointer Find(listPointer root0, int data);
listPointer NodeByRank(listPointer root, int rank);
int getLeftNodeSize(listPointer root);



int main(void) {

	listPointer first = NULL;
	FILE* fp = fopen("txt.txt", "r");
	int numElement = 0;
	char str[4];
int i =0; 
	for (i = 0;i < 30 && fscanf(fp, "%s", str) != EOF;i++) {
		
		int data = atoi(str);	
		if (Find(first, data)) {
			printf("Element already there.\n");			
		}
		else {
			Insert(&first, data);
			numElement++;
		}		
	}
	
	printf("\nInorder Traversal:\n");
	inorder_traversal(first);
	fclose(fp);
	do {
		int choice = 0;
		int key = 0;
		printf("\n\n1. �s�W�@�ӷskey��\n2. �R���Y��key��\n3. �M��Y��key��\n4. �M���N�p��key��\n5. ��Xkey�Ȫ��Ƨǵ��G\n6. �����{��\n�п�ܤW�z�\��>");
		scanf("%d", &choice);
		
		switch (choice) {
		case 1:
			printf("Enter value of key> ");
			scanf("%d", &key);
			if (Find(first, key)) {
				printf("Element already there.\n");
			}
			else {
				Insert(&first, key);
			}
			
			break;
		case 2:
			printf("Enter value of key> ");
			scanf("%d", &key);
			if (Find(first, key)) {
				Delete(&first, key);
			}
					
			break;
		case 3:
			printf("Enter value of key> ");
			scanf("%d", &key);
			if (Find(first, key)) {
				printf("Element is there.\n");
			}
			else {
				printf("Element not there.\n");
			}
			
			break;
		case 4:
			printf("Enter value of N> ");
			scanf("%d", &key);
			if (key>numElement) {
				printf("Element not there.\n");
			}
			else {
				NodeByRank(&first, key);
			}			
			break;
		case 5:			
			break;
		case 6:
			exit(0);
		default:
			printf("Invalid choice\n");
		}
		printf("\nInorder Traversal:\n");
		inorder_traversal(first);
	} while (1);



	return 0;
}


listPointer inorder_traversal(listPointer current) {
	if (current) {									// if current != NULL
		inorder_traversal(current->left_node);      // L
		printf("%d, ", current->data);				// V		
		inorder_traversal(current->right_node);     // R
	}
	
}
listPointer Insert(listPointer root, int data) {	
	if (root == NULL) {
		
		if (!((root) = malloc(sizeof(*root)))) {
				fprintf("stderr", "Insufficient memory");
				exit(EXIT_FAILURE);
		}

		root->data = data;
		printf("Insert %d.\n", data);
		root->right_node = root->left_node = NULL;

	}
	else {
		if (data < root->data)
			root->left_node = Insert(&root->left_node, data);
		else if (data > root->data)
			root->right_node = Insert(&root->right_node, data);
	}
	return root;
}
listPointer FindMax(listPointer root) {
	/*if (root0 == NULL)
		return NULL;*/
	while (root->right_node != NULL)
		root = root->right_node;
	return root;
}
listPointer Delete(listPointer root, int data) {
	listPointer temp;
	if (data < root->data)
		root->left_node = Delete(&root->left_node, data);
	else if (data > root->data)
		root->right_node = Delete(&root->right_node, data);
	else {
		//Found
		if (root->left_node != NULL && root->right_node != NULL) {
			//two children, and replace largest left subtree
			temp = FindMax(&root->left_node);
			root->data = temp->data;
			root->left_node = Delete(&root->left_node, &root->data);
		}
		else {
			//one child or no child
			temp = root;
			if (root->left_node == NULL)
				root = root->right_node;				
			if (root->right_node == NULL)
				root = root->left_node;
			free(temp);
		}
	}
	return root;
}
listPointer Find(listPointer root0, int data) {
	if (root0 == NULL) {
		printf("%d not there.\n", data);
		return NULL;
	}	
	if (data < root0->data)
		return Find(root0->left_node, data);
	else if (data > root0->data)
		return Find(root0->right_node, data);
	else if (data == root0->data) {
		return root0;
	}
}
listPointer NodeByRank(listPointer root, int rank) {

	// left children�ƶq �A�[�W current node
	int leftNodeSize = getLeftNodeSize(&root->left_node) + 1;

	// Found
	if (leftNodeSize == rank) {
		printf("value: %d\n", root->data);
		return root;
	}
		

	// �ؼФj���eleft node size�A�h��right children
	if (rank > leftNodeSize)
		return NodeByRank(&root->right_node, rank - leftNodeSize);
	else
		return NodeByRank(&root->left_node, rank);
}
int getLeftNodeSize(listPointer root) {
	if (root == NULL)
		return 0;
	return getLeftNodeSize(&root->left_node) + getLeftNodeSize(&root->right_node) + 1;

}
