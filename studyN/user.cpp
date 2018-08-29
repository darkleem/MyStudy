#include <cstdio>

#define MAX_MAP_SIZE		64
#define BLOCK_SIZE			4

extern void brokenCamera(char zone[BLOCK_SIZE][BLOCK_SIZE]);

bool blockCheck(char map[MAX_MAP_SIZE][MAX_MAP_SIZE], const char capture[BLOCK_SIZE][BLOCK_SIZE], const int y, const int x)
{
    // debug
    printf("\nblock check start\n");
    for (int row = 0; row < BLOCK_SIZE; row++)
        printf("%d %d %d %d\t%d %d %d %d\n", map[row+y][0+x], map[row+y][1+x], map[row+y][2+x], map[row+y][3+x],
            capture[row][0], capture[row][1], capture[row][2], capture[row][3]);
    printf("block check end : ");

    // ���⼭ Ȯ��
    int zeroCnt = 0;
    int sum = 0;
    for (int row = 0; row < BLOCK_SIZE; row++)
    {
        for (int col = 0; col < BLOCK_SIZE; col++)
        {
            if (map[row + y][col + x] == 0)
            {
                zeroCnt++;
                continue;
            }

            int n = map[row + y][col + x] - capture[row][col];
            if (n != 0)
            {
                printf("false \n");
                return false; // xor����� 0�� �ƴϸ� false
            }
            else
                sum += n;
        }
    }

    if (zeroCnt <= 8 && sum == 0)
    {
        for (int y2 = 0; y2 < BLOCK_SIZE; y2++)
            for (int x2 = 0; x2 < BLOCK_SIZE; x2++)
                map[y2 + y][x2 + x] = capture[y2][x2];

        printf("true \n");
        return true;
    }
    
    printf("false \n");
    return false;
}

bool searchTotalArea(int N, char map[MAX_MAP_SIZE][MAX_MAP_SIZE], char capture[BLOCK_SIZE][BLOCK_SIZE], int &outY, int &outX)
{
    for (int y = 0; y < N - 2; y += 2)
    {
        for (int x = 0; x < N - 2; x += 2)
        {
            // ����� ������, 
            if (blockCheck(map, capture, y, x))
            {
                outY = y;
                outX = x;

                return true;
            }
        }
    }
    return false;
}


char que[MAX_MAP_SIZE][BLOCK_SIZE][BLOCK_SIZE] = { 0 };
int queStart = 0;
int queEnd = 0;

void addQue(const char src[BLOCK_SIZE][BLOCK_SIZE])
{
    for (int row = 0; row < BLOCK_SIZE; row++)
    {
        for (int col = 0; col < BLOCK_SIZE; col++)
        {
            que[queEnd][row][col] = src[row][col];
        }
    }
    queEnd = (queEnd + 1) % MAX_MAP_SIZE;
}

void completeMap(int N, char map[MAX_MAP_SIZE][MAX_MAP_SIZE])
{
    printf("�⺻ ���� \n");
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            printf("%d ", map[row][col]);
        }
        printf("\n");
    }
    printf("\n\n");

    char capture[BLOCK_SIZE][BLOCK_SIZE] = { 0 };
    int maxN = (N - 4)*(N - 4);
    while (maxN--)
    {
        // ĸó ����
        brokenCamera(capture);

        // ��ü Ž�� �� �´� ���� �ִٸ� ����(true)
        int outRow = -1, outCol = -1;
        if (searchTotalArea(N, map, capture, outRow, outCol))
        {
            // ĳ�̵� ���� �ִٸ�,
            // ĳ�̵� ���� ���յ� ���� �ֺ� ����(�����¿� +2)�� Ȯ��
            // �Ź� ����
            for (int i = queStart; i < queEnd; i++)
            {
                if (searchTotalArea(N, map, que[i], outRow, outCol))
                {
                    printf("que in\n");
                }
            }

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
        else // search�� ���� ���޴ٸ� que�� �߰�
        {
            addQue(capture);
        }
    }

    for (int i = queStart; i < queEnd; i++)
    {
        for (int row = 0; row < BLOCK_SIZE; row++)
        {
            for (int col = 0; col < BLOCK_SIZE; col++)
            {
                printf("%d ", que[i][row][col]);
            }
            printf("\n");
        }
        printf("\n\n");
    }
    //// debug
    //for (int i = 0; i < maxN; i++)
    //{
    //    brokenCamera(capture);

    //    for (int row = 0; row < BLOCK_SIZE; row++)
    //        printf("%d %d %d %d\n", capture[row][0], capture[row][1], capture[row][2], capture[row][3]);
    //    printf("\n");
    //}

}