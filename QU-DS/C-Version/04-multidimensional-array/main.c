#include <stdio.h>

static int board[20][20];
static int M, N;

static int bang(int x, int y, int kill)
{
    int ret = 0;
    if ((x >= 0 && x < M) && (y >= 0 && y < N) && board[x][y] > 0)
    {
        board[x][y] -= kill;
        if (board[x][y] <= 0)
        {
            ret++;
        }
    }
    return ret;
}

int main(void)
{
    scanf("%d%d", &M, &N);
    getchar();
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            board[i][j] = getchar() == '0' ? 0 : 2;
        }
        getchar();
    }
    int k;
    scanf("%d", &k);
    for (int i = 1; i <= k; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        int count = 0;
        count += bang(x, y, 2);
        count += bang(x - 1, y, 1);
        count += bang(x + 1, y, 1);
        count += bang(x, y - 1, 1);
        count += bang(x, y + 1, 1);
        printf("%d\n", count);
    }
    return 0;
}