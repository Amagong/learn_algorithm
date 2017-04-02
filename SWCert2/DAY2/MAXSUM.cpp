/* DP: �ִ� �κ��� */

/**
����
ũ��
N
N�� ���� �迭�� ������ �� ���� �κ� ���� �� ���� �ִ��� ���� ���� ���Ͻÿ�.

<�Է�>
ù ��° �ٿ� ũ��N�� �־�����.(1��N��1,000,000)
�� ��° �ٿ� ũ��N�� ���� �迭�� �־�����. �־����� ���� ���밪�� 2,000,000 ���� ũ�� �ʴ�.

<���>
���� �κ� ������ �� �� �ִ밪�� ����Ͻÿ�. (��, ��°��� int ������ ��� �� �ִ�.)

<Ǯ��>

 D[e] :e �� ������ ���� �κм����߿� �ִ� �� 

 D[e]�߿� �ִ밪�� �� 
 
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

#define DEBUG 

typedef long long INT64;

const int MAX_N = 1000000;
const int MAX_V = 2000000;
int N;
INT64 A[MAX_N + 9];

/* D[e] :e �� ������ ���� �κм����߿� �ִ� �� */

INT64 dp[MAX_N + 1];

INT64 MAXSUM_r(int e)
{
	INT64& ref = dp[e];

	if (ref != -1)
		return ref;

	/* ������ */
	if (e == 0)
	{
		return ref = 0ll;		/* ������ */
	}
		
	/* DP[n] = MAX { DP[n-1] + A[i], A[i] } */	

	ref = max(MAXSUM_r(e - 1) + A[e], A[e]);

	return ref;
}

int main()
{

#ifdef DEBUG
	freopen("C:\\temp\\maxsum.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif

	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%lld", A + i);
	}

	memset(dp, -1, sizeof(dp));

	INT64 result = MAXSUM_r(N);


	INT64 max_result = result;

	for (int i = 1; i <= N; ++i)
		max_result = max(dp[i], max_result);

	printf("%lld\n", max_result);
	return 0;
}
