/* DP: �պ��� */

/** 
����
0���� N ������ ���� K ���� ���ؼ� �� ���� N �� �Ǵ� ����� ���� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

������ ������ �ٲ� ���� �ٸ� ���� ����(1+2�� 2+1�� ���� �ٸ� ���). ���� �� ���� ���� ���� �� �� ���� �ִ�.

<�Է�>
ù ��° �ٿ� �� ����N,K�� �������� �и��Ǿ� �־�����.
(1 �� N , K �� 200 )(1��N,K��200)

<���>
ù ��° �ٿ� ����1000000000���� ���� �������� ����Ѵ�.

<Ǯ��> 
D[i][j] = i���� ���� ���ؼ� j�� ����� ����� ��

�ʱⰪ D[0][0] = 1

D[i][j] = Sum of D[i-1][j-k] for all 0 �� k �� j
D[i-1][j-k]: �������� ���� ���� k�� ����� ��

*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

#define DEBUG 

typedef long long INT64;

const int MAX_N = 200;
const INT64 MOD_VALUE = 1000000000;

int N, K;

INT64 dp[MAX_N + 1][MAX_N + 1];

INT64 SUMDIV_r(int n, int k)
{
	INT64& ref = dp[n][k];

	if (ref != -1)
		return ref;

	if (n == 0)
		return ref = 1ll;

	if (k == 0)
		return ref = 0ll;

	ref = 0ll;
	for (int j = 0; j <= n; ++j)
	{
		ref += SUMDIV_r(n - j, k - 1);
		ref %= MOD_VALUE;
//		printf("SUMDIV_r(%d, %d)_ref = %lld\n", n - j, k - 1, SUMDIV_r(n - j, k - 1));
	}
	return ref;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\sumdiv.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d %d", &N, &K);

	memset(dp, -1, sizeof(dp));

	INT64 result = SUMDIV_r(N, K);

	printf("%lld\n", result);
	return 0;
}
