/*
 * DP: ���� �ݱ� 
 *
 --
<����>
N��N ���ڷ� �̷���� ���ð� �ִ�. �� ���� ������������ ������ ������ �ִ�.

������ ���� ���� �� ���� (1, 1)���� ����Ͽ� ���� ������ �Ʒ� ���� (N, N)���� �̵��ϸ� ������ �ݴµ�, 
�ִ� ��θ� ���󰡾߸� �Ѵ�. ��, ������ ������ ĭ �Ǵ� �Ʒ��� ĭ���θ� �̵��� �� �ִ�. �� ��, 
������ ������ �� �ִ� ������ �ִ밪�� ����Ͻÿ�.

������� �������� ��ġ�� ���� ���� �ֿ� �� �ִ�.

 --
 
A[x][y] : (x,y)�� �ִ� ������ ��

������ ������ ������ �������� ������ + ���������� ���� ��� ������Ʈ.
 
D[x][y] = max (D[x-1][y] + A[x][y], D[x][y-1] + A[x][y])


 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_N = 200;
const int MAX_G = 1000;

int N;
int A[MAX_N + 9][MAX_N + 9];

int dp[MAX_N + 9][MAX_N + 9];
int dph[MAX_N + 9][MAX_N + 9];

int PAPER(int sx, int sy)
{
	int& ref = dp[sx][sy];

	if (ref != -1)
		return ref;

	if (sx == N && sy == N)
		return ref = A[sx][sy];

	ref = 0;
	if (sx >= 1 && sx < N)
		ref = max(ref, A[sx][sy] + PAPER(sx + 1, sy));
	if (sy >= 1 && sy < N)
		ref = max(ref, A[sx][sy] + PAPER(sx, sy + 1));

	return ref;
}
 
int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\paper.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d", &N);

	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j) {
			(void) scanf("%d", &A[i][j]);
		}

	memset(dp, -1, sizeof(dp));
	int result = PAPER(1, 1);

#ifdef DEBUG
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			printf("%3d", dp[i][j]);
		}
		printf("\n");
	}
#endif

	printf("%d\n", dp[1][1]);

}
