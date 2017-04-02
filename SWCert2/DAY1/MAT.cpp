/* 
 * Matrix Multiplication 
 *
 --
 ���ϴ� �����ε�, ���� ���ϱ⸦ ��𿡼� �ϴ��ĸ� ���ϴ� RC�� 2���� ����
  
 --
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#define DEBUG 

const int MAX_M = 500;

int N;
int dim[MAX_M + 9];

int dp[MAX_M + 1][MAX_M + 1];
int dph[MAX_M + 1][MAX_M + 1];

int MAT()
{
	/* �ʱⰪ */
	for (int i = 1; i < N; ++i)
	{
		dp[i][i] = 0;
		dp[i][i + 1] = dim[i] * dim[i + 1] * dim[i + 2];
#ifdef DEBUG
		printf("dp[%d][%d] = %d\n", i, i+1, dp[i][i+1]);
#endif
	}
	dp[N][N] = 0;

	/* �缱���� ������� ��� (1���� distance�� �����ϴ� ������) */
	for (int d = 2; d <= N; ++d) {
		for (int i = 1; i+d <= N; ++i) {
			int j = i + d;
			int& v = dp[i][j];

			v = 1e10;
			for (int k = i; k < j; ++k)
			{
				int m = dp[i][k] + dp[k + 1][j] + dim[i] * dim[k+1] * dim[j + 1];

				if (m < v) {
					v = m;
					dph[i][j] = k;
				}
			}
#ifdef DEBUG
			printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
#endif
		}
	}

	return dp[1][N];
}

int MAT_r(int i, int j)
{
	int& ref = dp[i][j];

	if (ref != -1)
		return ref;

	if (i == j)
		return ref = 0;

	if (j == (i + 1))
		return ref = dim[i] * dim[i + 1] * dim[i + 2];


	ref = 1e10;

	for (int k = i; k < j; ++k)
	{
		int m = MAT_r(i, k) + MAT_r(k + 1, j) + dim[i] * dim[k + 1] * dim[j + 1];

		if (m < ref) {
			ref = m;
			dph[i][j] = k;
		}
	}

#ifdef DEBUG
	printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
#endif
	return ref;

}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\mat.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d", &N);

	for (int i = 1; i <= N + 1; ++i) {
		scanf("%d", dim + i);
	}

	memset(dp, -1, sizeof(dp));
	memset(dph, 0, sizeof(dph));

	int result = MAT_r(1, N);
	printf("%d\n", result);
}
