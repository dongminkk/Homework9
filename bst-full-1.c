#include <stdio.h>
#include <stdlib.h>

typedef struct node { //트리 구조체 선언 데이터와 왼쪽과 오른쪽자식이 있음
	int key; //데이터
	struct node *left; //왼쪽 노드 
	struct node *right; //오른쪽 노드
} Node;

int initializeBST(Node** h); //초기화 함수

void inorderTraversal(Node* ptr); //중위 순회 함수 
void preorderTraversal(Node* ptr); //전위 순회 함수
void postorderTraversal(Node* ptr); //후위 순회 함수
int insert(Node* head, int key);  //트리에 노드 삽입하는 함수
int deleteLeafNode(Node* head, int key); //데이터에 맞는 노드 삭제 하는 함수
Node* searchRecursive(Node* ptr, int key); //데이터에 맞는 노드 검색하는 함수 (Recursive 방식)
Node* searchIterative(Node* head, int key); //데이터에 맞는 노드 검색하는 함수 (Iterative 방식)
int freeBST(Node* head); //트리에 할당된 모든 메모리를 해제 하는 함수



int main()
{
	char command;  // 문자형 변수 선언
	int key; // / int형 변수 선언 트리 노드에 넣을 키를 받음
	Node* head = NULL; // 해드 노드 선언
	Node* ptr = NULL;	/* temp */
	printf("[----- [kim dongmin] [2017038093] -----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //기능 선택

		switch(command) {
		case 'z': case 'Z': 
			initializeBST(&head); //초기화
			break;
		case 'q': case 'Q':
			freeBST(head); //트리에 할당된 모든 메모리를 해제
			break;
		case 'n': case 'N':
			printf("Your Key = "); 
			scanf("%d", &key); //키값 입력받음
			insert(head, key); //트리에 노드 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); //키값 입력받음
			deleteLeafNode(head, key); //키에 맞는 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); //키값 입력
			ptr = searchIterative(head, key); //키에 맞는 노드 검색 (Iterative 방식)
			if(ptr != NULL) //값이 있을때
				printf("\n node [%d] found at %p\n", ptr->key, ptr);  //찾은 노드 주소 출력
			else
				printf("\n Cannot find the node [%d]\n", key); // 같은 키값을 찿을 수 없음
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key); //키값 입력
			ptr = searchRecursive(head->left, key); //데이터에 맞는 노드 검색 (Recursive 방식)
			if(ptr != NULL) //값이 있을때
				printf("\n node [%d] found at %p\n", ptr->key, ptr);  //찾은 노드 주소 출력
			else
				printf("\n Cannot find the node [%d]\n", key); // 같은 키값을 찿을 수 없음
			break;

		case 'i': case 'I':
			inorderTraversal(head->left); //중위 순회하여 트리 출력
			break;
		case 'p': case 'P':
			preorderTraversal(head->left); //전위 순회하여 트리 출력
			break;
		case 't': case 'T':
			postorderTraversal(head->left); //후위 순회하여 트리 출력
			break;
		default: //
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //잘못입력에 대한 오류 처리
			break;
		}

	}while(command != 'q' && command != 'Q'); //'q' && 'Q' 이면 반복문 종료

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) //해드가 가리키는 곳이 널이 아니면 
		freeBST(*h); //트리에 할당된 모든 메모리를 해제

	/* create a head node */ //해드를 만들어줌
	*h = (Node*)malloc(sizeof(Node)); //동적할당
	(*h)->left = NULL;	/* root */
	(*h)->right = *h; //자기자신 
	(*h)->key = -9999; // 데이터 
	return 1; //리턴 1
}



void inorderTraversal(Node* ptr) //중위 순회 함수
{
	if(ptr) {
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr) //전위 순회 함수
{
	if(ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr) //후위 순회 함수
{
	if(ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key) //트리에 노드 삽입하는 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left;


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;

	while(ptr != NULL) {

		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {

				/* root node case */
				if(parentNode == head)
					head->left = NULL;

				/* left node case or right case*/
				if(parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;

				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;


	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL)
		return NULL;

	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	/* if ptr->key == key */
	return ptr;

}
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;

	while(ptr != NULL)
	{
		if(ptr->key == key)
			return ptr;

		if(ptr->key < key) ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	return NULL;
}

void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}