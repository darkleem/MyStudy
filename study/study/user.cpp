#include <cstdio>

#define MAX_MAP_SIZE		64
#define BLOCK_SIZE			4

extern void brokenCamera(char zone[BLOCK_SIZE][BLOCK_SIZE]);

typedef struct _node
{
	int data[BLOCK_SIZE];
	struct _node* next;

	struct _node();
	struct _node(int item[BLOCK_SIZE])
	{
		data[0] = item[0];
		data[1] = item[1];
		data[2] = item[2];
		data[3] = item[3];
	}
}Node;

class List
{
private:
	Node * head;
	Node* tail;

public:
	int size;
	List();
	void pusBack(int item[BLOCK_SIZE]);
	void popFront(int Result[BLOCK_SIZE]);

	~List();
};

List::List()
{
	tail = head = nullptr;
	size = 0;
}

void List::pusBack(int item[BLOCK_SIZE])
{
	Node *newNode = new Node(item); // 삽입할 노드 생성


	if (head == nullptr)      // 리스트가 비었다면
	{
		head = newNode;      //    삽입할 노드가 첫 노드가 된다.
	}
	else
		tail->next = newNode;   // 리스트에 원소가 하나이상 존재한다면 현재의 마지막 노드의 다음을 삽입할 노드로 설정한다.

	tail = newNode;      // 리스트가 비었든지 말든지 삽입할 노드는 노드의 마지막.
	size++;         //사이즈 1 증가.
}

void List::popFront(int result[BLOCK_SIZE])
{
	if (head != nullptr)      // 리스트에 노드가 최소 하나 존재해야지 제거가 가능
	{
		Node *removal = head;   // 제거될 노드의 정보를 담을 임시노드 생성 (swap 구현할때 temp 변수와 같은 용도)
		head = head->next;   // 두번째 노드가 첫 노드가 된다.

		if (result != nullptr)
		{
			result[0] = removal->data[0];
			result[1] = removal->data[1];
			result[2] = removal->data[2];
			result[3] = removal->data[3];
		}

		delete removal;      // 첫째 노드 제거
		size--;         // 사이즈 1 감소
	}
}

List::~List()
{
	while (head != nullptr)
		popFront(nullptr);
}

void allmapPrint(int N, char(*map)[64]);

void completeMap(int N, char map[MAX_MAP_SIZE][MAX_MAP_SIZE])
{
	List* mylist = new List;
	//allmapPrint(N, map);

	int tmp = (N - 4)*(N - 4);
	while (tmp--)
	{
		char capture[BLOCK_SIZE][BLOCK_SIZE];
		brokenCamera(capture);
		mylist->pusBack((int*)capture);
	}

	{
		int listCnt = mylist->size;
		while (listCnt--)
		{
			int popData[BLOCK_SIZE];
			mylist->popFront(popData);

			int row = 0;
			for (int row = 0; row < N - 2; row += 2)
				for (int i = 0; i < N - 2; i += 2)
				{
					int compareCnt = 0;
					//printf("%d : %d\n", row, i);
					int *pTarget[BLOCK_SIZE];
					int targetSum = 0;
					for (int j = 0; j < BLOCK_SIZE; j++)
					{
						pTarget[j] = (int*)&map[row + j][i];
						//printf("%06X : %06X\n", *pTarget[j], popData[j]);

						targetSum += *pTarget[j];
						//compareCnt += (*pTarget[j] & 0xFF000000) == (popData[j] & 0xFF000000);
						//compareCnt += (*pTarget[j] & 0x00FF0000) == (popData[j] & 0x00FF0000);
						//compareCnt += (*pTarget[j] & 0x0000FF00) == (popData[j] & 0x0000FF00);
						//compareCnt += (*pTarget[j] & 0x000000FF) == (popData[j] & 0x000000FF);

						compareCnt += ((*pTarget[j] | popData[j]) != popData[j]);
					}
					//printf("result : %d\n", compareCnt);
					if (compareCnt == 0 && targetSum > 0)
					{
						*pTarget[0] = popData[0];
						*pTarget[1] = popData[1];
						*pTarget[2] = popData[2];
						*pTarget[3] = popData[3];
						//allmapPrint(N, map);
						break;
					}
					else
					{
						mylist->pusBack(popData);
					}
				}
		}
	}
}

void allmapPrint(int N, char(*map)[64])
{
	printf("----\n");
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			printf("%d ", map[row][col]);
		}
		printf("\n");
	}
	printf("\n\n");
}
