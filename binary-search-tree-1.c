/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */
void postorderFree(Node* ptr)						// freeBTS에 쓸 postorder 재귀함수
{
	if(ptr->left != NULL) postorderFree(ptr->left);
	if(ptr->right != NULL) postorderFree(ptr->right);
	free(ptr);										// 말단 노드부터 메모리 해제
}

int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("-----------------이한결---------------2021041055------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)				// inorder 하기 위해 왼쪽 노드 이동 - 키 출력 - 오른쪽 노드 이동으로 구성
{
	if(ptr->left != NULL) inorderTraversal(ptr->left); 
	printf("[%d] ", ptr->key);	
	if(ptr->right != NULL) inorderTraversal(ptr->right);
}

void preorderTraversal(Node* ptr)				// preorder 하기 위해 키 출력 - 왼쪽 노드 이동 - 오른쪽 노드 이동으로 구성	
{
	printf("[%d] ", ptr->key);
	if(ptr->left != NULL) preorderTraversal(ptr->left);
	if(ptr->right != NULL) preorderTraversal(ptr->right);
}

void postorderTraversal(Node* ptr)				//postorder 하기 위해 왼쪽 노드 이동 - 오른쪽 노드 이동 - 출력으로 구성
{
	if(ptr->left != NULL) postorderTraversal(ptr->left);
	if(ptr->right != NULL) postorderTraversal(ptr->right);
	printf("[%d] ", ptr->key);
}


int insert(Node* head, int key)
{
	Node* new = (Node*)malloc(sizeof(Node));	// 추가할 노드 동적 할당
	new->key = key;
	new->left = NULL;
	new->right = NULL;							// 노드 초기화
	if(head->left == NULL) head->left = new;	// BST가
	else{
		Node* ptr = head->left;					// 트리를 탐색할 포인터
		while(1){
			if(ptr->key <= key){				// 값이 크거나 같으면 오른쪽 노드로 이동해야함
				if(ptr->right == NULL){			// 오른쪽 노드가 NULL이면 new를 추가
					ptr->right = new;
					break;
				}
				ptr= ptr ->right;				// 오른쪽으로 이동
			}
			else{
				if(ptr->left == NULL){			// 왼쪽 노드가 NULL이면 new를 추가
					ptr->left = new;
					break;
				}
				ptr = ptr ->left;				// 왼쪽으로 이동
			}
		}
	}
	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	if (head->left == NULL) return 0;	// 트리가 비어있으면 함수 종료
	Node* ptr = head->left;				// 노드를 가르키는 포인터
	Node* pre = NULL;					// ptr이전의 노드를 가르키는 포인터
	while(1){
		if(ptr->key <= key){			
			if(ptr->key == key){		// key가 같은 노드를 찾으면
				if(ptr->right == NULL && ptr->left == NULL){	// 말단 노드인지 확인
					if(pre->right != NULL){
						if (pre->right->key == key) pre->right = NULL;	// 부모 노드의 자식 노드중에 어떤 노드가 말단 노드인지 확인	
					}
					if(pre->left != NULL){
						if(pre->left->key ==key) pre->left = NULL; 		// 말단 노드의 부모 노드가 가르키는 값이 NULL이 되도록 설정
					}
					free(ptr);											// 매모리 해제
				}
				else{
					printf("the node [%d] is not a leaf", key);			// 말단 노드가 아닐때
				}
				break;
			}
			pre = ptr;				
			ptr= ptr -> right;		// pre를 ptr로 바꾸고 ptr을 오른쪽 노드로 이동
		}
		else{
			pre = ptr;
			ptr = ptr -> left;		// pre를 ptr로 바꾸고 ptr을 왼쪽 노드로 이동
		}
	}
	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr->key == key) return ptr;		// key가 같은 노드를 반환
	if(ptr->key <= key ){
		if(ptr->right == NULL) return NULL;		// key가 같은 노드가 없음
		return searchRecursive(ptr->right, key);	// 오른쪽 노드를 매개변수로 재귀
	}
	else{
		if(ptr->left == NULL) return NULL;		// key가 같은 노두가 없음
		return searchRecursive(ptr->left, key);		// 왼쪽 노드를 매개변수로 재귀
	}
}

Node* searchIterative(Node* head, int key)
{
	if(head->left == NULL) return NULL;		// BST의 유무
	Node* ptr = head->left;					// 노드를 탐색할 포인터
	while(1){
		if(ptr->key == key) return ptr;		// key가 같은 노드를 찾으면 반환
		if(ptr->key <= key){
			if(ptr->right == NULL) return NULL;	// key가 같은 노드가 없음
			ptr = ptr->right;				// 오른쪽으로 이동
		}
		else{
			if(ptr->left == NULL) return NULL;	// key가 같은 노드가 없음
			ptr = ptr->left;				// 왼쪽으로 이동
		}
	}
	return 0;
}


int freeBST(Node* head)
{	
	postorderFree(head->left);		// 말단 노드부터 해제하기 위해 postoder 방식으로 해제하는 재귀함수를 사용
	return 0;
}