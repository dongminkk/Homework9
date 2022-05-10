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

	/* create a head node */ //해드를 만들어줌 초기상태
	*h = (Node*)malloc(sizeof(Node)); //동적할당
	(*h)->left = NULL;	/* root */
	(*h)->right = *h; //자기자신 
	(*h)->key = -9999; // 데이터 
	return 1; //리턴 1
}



void inorderTraversal(Node* ptr) //중위 순회 함수
{
	if(ptr) {
		inorderTraversal(ptr->left); //왼쪽으로 이동하고 다시 중위 순회
		printf(" [%d] ", ptr->key); // 노드 키값 출력
		inorderTraversal(ptr->right); //오른쪽으로 이동하고 다시 중위 순회
	}
}

void preorderTraversal(Node* ptr) //전위 순회 함수
{
	if(ptr) {
		printf(" [%d] ", ptr->key); // 노드 키값 출력
		preorderTraversal(ptr->left); //왼쪽으로 이동하고 전위 순회
		preorderTraversal(ptr->right); //오른쪽으로 이동하고 전위 순회
	}
}

void postorderTraversal(Node* ptr) //전위 순회 함수
{
	if(ptr) {
		postorderTraversal(ptr->left); //왼쪽으로 이동하고 다시 전위 순회
		postorderTraversal(ptr->right); //오른쪽으로 이동하고 다시 전위 순회
		printf(" [%d] ", ptr->key); // 노드 키값 출력
	}
}


int insert(Node* head, int key) //트리에 노드 삽입하는 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // 동적할당
	newNode->key = key; //노드에 받은 키값 대입
	newNode->left = NULL; //왼쪽 노드 NULL
	newNode->right = NULL;// 오른쪽 NULL

	if (head->left == NULL) { // 해드 왼쪽 하위 노드가 없는 경우
		head->left = newNode; //해드 왼쪽 하위 노드에 새로운 노드 삽입
		return 1; //리턴 1
	}

	/* head->left is the root */
	Node* ptr = head->left; // Node형 포인터 구조체 ptr선언 해드 노드의 왼쪽 하위 노드 주소 대입

	Node* parentNode = NULL; //Node형 포인터 구조체 parentNode선언
	while(ptr != NULL) { //  // 반복문 ptr이 널이 될때까지

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; //키와 같은 노드가 있으면 리턴1

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //parentNode에 ptr대입

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)  //ptr 키값이 입력 받은 키값 보다 작은 경우
			ptr = ptr->right; //오른쪽 하위 트리로 이동
		else
			ptr = ptr->left; //외쪽 하위 트리로 이동
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) // 노드의 키가 입력받은 키값보다 큰 경우
		parentNode->left = newNode; //하위 왼쪽 트리에 새노드
	else
		parentNode->right = newNode; // 오른 쪽 트리에 새노드
	return 1;// 리턴1
}

int deleteLeafNode(Node* head, int key) //데이터에 맞는 노드 삭제 하는 함수
{
	if (head == NULL) { //해드가 널인 경우
		printf("\n Nothing to delete!!\n"); // 오류 출력
		return -1; //리턴 -1
	}

	if (head->left == NULL) { // 해드 왼쪽 하위 노드가 없는 경우
		printf("\n Nothing to delete!!\n"); //오류 출력
		return -1; //리턴 -1
	}

	/* head->left is the root */
	Node* ptr = head->left; // Node형 포인터 구조체 ptr선언 해드 노드의 왼쪽 하위 노드 주소 대입


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;  //Node형 포인터 구조체 parentNode선언 하고 해드 대입

	while(ptr != NULL) { // 반복문 ptr이 널이 될때까지

		if(ptr->key == key) { //ptr키 값이 입력 받은 키값과 같은 경우
			if(ptr->left == NULL && ptr->right == NULL) {

				/* root node case */
				if(parentNode == head)  //parentNode == head
					head->left = NULL; //해드 하위 노드 NULL

				/* left node case or right case*/
				if(parentNode->left == ptr) 
					parentNode->left = NULL;
				else
					parentNode->right = NULL; 

				free(ptr); //동적할당해제
			}
			else { // leaf가 아닐때
				printf("the node [%d] is not a leaf \n", ptr->key); // leaf가 아님 오류 출력
			}
			return 1; //리턴 1
		}

		/* keep the parent node */
		parentNode = ptr; //parentNode에 ptr대입

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)  // 노드의 키같은 찾는 키값보다 작을 경우
			ptr = ptr->right; //오른쪽 하위 트리
		else
			ptr = ptr->left; //왼쪽 하위 트리


	}

	printf("Cannot find the node for key [%d]\n ", key); //오류 출력

	return 1; //리턴 1
}

Node* searchRecursive(Node* ptr, int key) //데이터에 맞는 노드 검색하는 함수 (Recursive 방식)
{
	if(ptr == NULL) // ptr이 NULL인 경우
		return NULL; //널 리턴

	if(ptr->key < key)  // 노드의 키같은 찾는 키값보다 작을 경우
		ptr = searchRecursive(ptr->right, key); //오른쪽으로 이동하고 반복
	else if(ptr->key > key)  // 노드의 키같은 찾는 키값보다 클을 경우
		ptr = searchRecursive(ptr->left, key); //왼쪽으로 이동하고 반복

	/* if ptr->key == key */
	return ptr; //리턴 ptr

}
Node* searchIterative(Node* head, int key) //데이터에 맞는 노드 검색하는 함수 (Iterative 방식)
{
	/* root node */
	Node* ptr = head->left; // Node형 포인터 구조체 p선언 해드 노드의 왼쪽 하위 노드 주소 대입

	while(ptr != NULL) // 반복문 ptr이 널이 될때까지
	{
		if(ptr->key == key) //해당 노드의 키값이 찾는 노드와 같을 경우 ptr 리턴
			return ptr; // ptr 리턴

		if(ptr->key < key) ptr = ptr->right; // 노드의 키같은 찾는 키값보다 작을 경우 ptr에 ptr노드의 오른쪽 하위 노드 주소 대입 
		else
			ptr = ptr->left; //ptr에 ptr노드의 왼쪽 하위 노드 주소 대입 
	}

	return NULL;
}

void freeNode(Node* ptr)
{
	if(ptr) { // 트리에 할당된 모든 메모리를 해제
		freeNode(ptr->left); //왼쪽 하위 노드로 이동하고 다시freeNode
		freeNode(ptr->right); //오른쪽 하위 노드로 이동하고 다시 freeNode
		free(ptr); //동적할당 해제
	}
}

int freeBST(Node* head) //트리에 할당된 모든 메모리를 해제 하는 함수 해드도
{

	if(head->left == head) //head->left가 자기 자신일때
	{
		free(head); //해드 동적할당 해제
		return 1; //리턴1
	}

	Node* p = head->left; // Node형 포인터 구조체 p선언 해드 노드의 왼쪽 하위 주소 대입

	freeNode(p); // 트리에 할당된 모든 메모리를 해제

	free(head); // 해드 해제
	return 1; //리턴 1
}