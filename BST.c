#include <stdio.h>
#include <stdlib.h>
#define root (*root)

typedef struct listNode* listPointer;
typedef struct listNode {								//structure of linked list  
	int data;
	listPointer left_node;
	listPointer right_node;
};
//助教我抄網路上的，我連改都不改直接交了。
listPointer inorder_traversal(listPointer current);
listPointer Insert(listPointer root, int data);
listPointer FindMax(listPointer root0);
listPointer Delete(listPointer root, int data);
listPointer Find(listPointer root0, int data);
listPointer NodeByRank(listPointer root, int rank);
int getLeftNodeSize(listPointer root);



int main(void) {

	listPointer first = NULL;
	FILE* fp = fopen("txt.txt", "r");					//read txt.txt 
	int numElement = 0;
	char str[4];
	int i = 0;
	for (i = 0;i < 30 && fscanf(fp, "%s", str) != EOF;i++) {

		int data = atoi(str);
		if (Find(first, data)) {
			printf("Element already there.\n");			//insert elements sequently 
		}
		else {
			Insert(&first, data);
			numElement++;
		}
	}

	printf("\nInorder Traversal:\n");    				//print rusult of inorder traversal 
	inorder_traversal(first);
	fclose(fp);
	do {
		printf("\n-----------------------------------");
		int choice = 0;
		int key = 0;
		printf("\n\n1. 新增一個新key值\n2. 刪除某個key值\n3. 尋找某個key值\n4. 尋找第N小的key值\n5. 輸出key值的排序結果\n6. 結束程式\nSelect one of function>");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			printf("Enter value of key> ");					//insert particular element
			scanf("%d", &key);
			if (Find(first, key)) {
				printf("Element already there.\n");
			}
			else {
				Insert(&first, key);
			}

			break;
		case 2:
			printf("Enter value of key> ");					//delete particular element  
			scanf("%d", &key);
			if (Find(first, key)) {
				Delete(&first, key);
			}

			break;
		case 3:
			printf("Enter value of key> ");					//find particular element 
			scanf("%d", &key);
			if (Find(first, key)) {
				printf("Element is there.\n");
			}
			else {
				printf("Element not there.\n");
			}

			break;
		case 4:
			printf("Enter value of N> ");					//find the Nth element 
			scanf("%d", &key);
			if (key > numElement) {
				printf("Element not there.\n");
			}
			else {
				NodeByRank(&first, key);
			}
			break;
		case 5:
			break;											//smallest to largest is equivelent to inorder traversal
		case 6:
			exit(0);										//exit
		default:
			printf("Invalid choice\n");						//wrong choice 
		}
		printf("\nInorder Traversal:\n");
		inorder_traversal(first);							//print rusult of inorder traversal 
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
			fprintf("stderr", "Insufficient memory");			//Insufficient memory
			exit(EXIT_FAILURE);
		}

		root->data = data;											//assign data to element 
		printf("Insert %d.\n", data);
		root->right_node = root->left_node = NULL;

	}
	else {
		if (data < root->data)
			root->left_node = Insert(&root->left_node, data);		//seeking
		else if (data > root->data)
			root->right_node = Insert(&root->right_node, data);
	}
	return root;
}
listPointer FindMax(listPointer root0) {
	while (root0->right_node != NULL)
		root0 = root0->right_node;
	return root0;
}
listPointer Delete(listPointer root, int data) {
	listPointer temp;
	if (data < root->data)
		root->left_node = Delete(&root->left_node, data);			//seeking
	else if (data > root->data)
		root->right_node = Delete(&root->right_node, data);
	else {
		//Found
		if (root->left_node != NULL && root->right_node != NULL) {
			//two children, and replace largest left subtree
			temp = FindMax(root->left_node);
			printf("Delete %d\n", data);
			root->data = temp->data;
			root->left_node = Delete(&root->left_node, root->data);
		}
		else {
			//one child or no child
			temp = root;
			if (root->left_node == NULL)
				root = root->right_node;
			else if (root->right_node == NULL)
				root = root->left_node;
			printf("Delete or replace with %d\n", data);
			free(temp);
		}
	}
	return root;
}
listPointer Find(listPointer root0, int data) {
	if (root0 == NULL) {
		printf("%d not there.\n", data);					//not found 
		return NULL;
	}
	if (data < root0->data)
		return Find(root0->left_node, data);				//seeking
	else if (data > root0->data)
		return Find(root0->right_node, data);
	else if (data == root0->data) {
		return root0;										//found 
	}
}
listPointer NodeByRank(listPointer root, int rank) {

	// left children + 1 = leftSize of current node
	int leftNodeSize = getLeftNodeSize(&root->left_node) + 1;

	// Found
	if (leftNodeSize == rank) {
		printf("value: %d\n", root->data);
		return root;
	}

//助教我抄網路上的，我連改都不改直接交了。
	// if target larger than leftSize of current node, go right children.
	if (rank > leftNodeSize)
		return NodeByRank(&root->right_node, rank - leftNodeSize);
	else
		return NodeByRank(&root->left_node, rank);
}
int getLeftNodeSize(listPointer root) {
	if (root == NULL)
		return 0;
	//calculate every element leftSize 
	return getLeftNodeSize(&root->left_node) + getLeftNodeSize(&root->right_node) + 1;

}
