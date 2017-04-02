/* DP: Adjacent Bit */

/**
����
0�� 1�� �̷���� ���� S�� �־�����. S�� ù ���� s_1, ������ ���� s_N�̶�� �� ��, S�� ������ ��Ʈ�� ������ ������ ���� ���� �� �ִ�.

s_1 x s_2 + s_2 x s_3 + s_3 x s4 + ... + s(N-1) x s_N

���� ���� �̿��ϸ� ���� S���� ������ 1�� ������ ���� �� �ִ�. �������, 011101101�� ������ ��Ʈ�� ������ 3�� �ǰ�, 111101101�� 4, 010101010�� 0�� �ȴ�.

���� S�� ũ�� N�� K�� �־����� ��, ������ ��Ʈ�� ������ k�� ���� S�� ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

���� ���, N�� 5�̰�, K�� 2�̸�, ���� S�� �� �� �ִ� ������ ������ ���� 6������ �ִ�.

11100
01110
00111
10111
11101
11011


<�Է�>
ù ��° �ٿ� �׽�Ʈ ���̽��� �� T�� �־�����. (1 �� T �� 1,000)

�� �׽�Ʈ ���̽��� ù ��° �ٿ� �� ���� t, N, K�� �������� �и��Ǿ� �־�����. t�� �׽�Ʈ ���̽��� ��ȣ�̴�. (1 �� N �� 100)

���
�� �׽�Ʈ ���̽��� ���� �׽�Ʈ ���̽� ��ȣ�� ������ ��Ʈ�� ������ k�� ���� S�� ������ ���̿� ������ �ΰ� �� �ٿ� �ϳ��� ����Ѵ�.

�� ���� 2,147,483,647���� �۰ų� ����.

<Ǯ��>

���̰� N�� �������� �߿� N��° ���� x�̸鼭 (x = 0 or 1) ������ ��Ʈ�� ������ K�� ����� �� 
D[N][K][x]

D[N][K][0] = D[N-1][K][0] + D[N-1][K][1]
D[N][K][1] = D[N-1][K][0] + D[N-1][K-1][1]
 
���� = D[N][K][0] + D[N][K][1]

*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

#define DEBUG 

typedef long long INT64;

const int MAX_N = 100;
const INT64 MAX_MOD = 2147483647;
int CASE, T, N, K;
INT64 A[MAX_N + 9];

INT64 dp[MAX_N + 2][MAX_N + 1][3];

INT64 ADJ_BIT_r(int n, int k, int b)
{
	INT64& ref = dp[n][k][b];

	if (ref != -1)
		return ref;

	/* DP[0][x][x] = 0 */
	if (n == 1)
	{
		if (k == 0)
			return ref = 1;
		else
			return ref = 0;
	}

	/* 0 ���� ������ ����� �� */
	if (b == 0) {
		ref = ADJ_BIT_r(n - 1, k, 0) + ADJ_BIT_r(n - 1, k, 1);
	}
	else
	{
		/* 1 �� ������ ��� */
		ref = ADJ_BIT_r(n - 1, k, 0) + ADJ_BIT_r(n - 1, k - 1, 1);
	}

	return ref %= 2147483647;
}

int main()
{

#ifdef DEBUG
	freopen("C:\\temp\\adj_bit.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif

	scanf("%d", &CASE);

	memset(dp, -1ll, sizeof(dp));

	for (int t = 1; t <= CASE; ++t) {
		scanf("%d %d %d", &T, &N, &K);

		INT64 result = ADJ_BIT_r(N+1, K, 0);
		
#ifdef DEBUG
		if (N == 5)
		{
			for (int i = 0; i < N + 1; ++i)
				for (int j = 0; j < K; ++j) {
					printf("%10d", dp[i][j][0]);
				}
			printf("\n");
		}
#endif
		printf("%d %lld\n", T, result);
	}
}
