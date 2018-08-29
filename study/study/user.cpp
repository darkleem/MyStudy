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
	Node *newNode = new Node(item); // ������ ��� ����


	if (head == nullptr)      // ����Ʈ�� ����ٸ�
	{
		head = newNode;      //    ������ ��尡 ù ��尡 �ȴ�.
	}
	else
		tail->next = newNode;   // ����Ʈ�� ���Ұ� �ϳ��̻� �����Ѵٸ� ������ ������ ����� ������ ������ ���� �����Ѵ�.

	tail = newNode;      // ����Ʈ�� ������� ������ ������ ���� ����� ������.
	size++;         //������ 1 ����.
}

void List::popFront(int result[BLOCK_SIZE])
{
	if (head != nullptr)      // ����Ʈ�� ��尡 �ּ� �ϳ� �����ؾ��� ���Ű� ����
	{
		Node *removal = head;   // ���ŵ� ����� ������ ���� �ӽó�� ���� (swap �����Ҷ� temp ������ ���� �뵵)
		head = head->next;   // �ι�° ��尡 ù ��尡 �ȴ�.

		if (result != nullptr)
		{
			result[0] = removal->data[0];
			result[1] = removal->data[1];
			result[2] = removal->data[2];
			result[3] = removal->data[3];
		}

		delete removal;      // ù° ��� ����
		size--;         // ������ 1 ����
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
