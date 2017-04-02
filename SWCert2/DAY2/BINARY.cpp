/* DP: ������ --> ��ģ�� 
 *
 --
 ����
 0�� 1�� �̷���� ������ �� ���� ������ �����ϴ� ���� ��ģ����� �Ѵ�.

 ��ģ���� 0���� �������� �ʴ´�.
 ��ģ�������� 1�� �� �� �������� ��Ÿ���� �ʴ´�. ��, 11�� �κ� ���ڿ��� ���� �ʴ´�.
 ���� ���, 1, 10, 100 ���� ��ģ���� �ȴ�. ������ 010�̳� 110�� ���� 1, 2�� ��Ģ�� ����ǹǷ� ��ģ���� �ƴϴ�.

 N�� �־����� ��, N�ڸ� ��ģ���� ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

 <�Է�>
 ù ��° �ٿ� N �� �־�����. ( 1  ��  N  ��  90  ),  (1��N��90)
 
 <���>
 ù ��° �ٿ� N�ڸ� ��ģ���� ������ ����Ѵ�.
--

D[i] = ���̰� i�� ��ģ���� ����

D[0] = 0, D[1] = 1

D[i] = D[i-1] + D[i-2]
D[i-1]: ���̰� i-1�� ������ �����ʿ� 0�� �̾���̴� ���
D[i-2]: ���̰� i-2�� ������ �����ʿ� 01�� �̾���̴� ���

D[2] = 1, D[3] = 2, D[4] = 3, D[5] = 5, ��
Fibonacci ��!


 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_N = 90;
int N;

typedef long long INT64;

INT64 dp[MAX_N + 1];

INT64 BINARY_r(int w)
{
	INT64& ref = dp[w];

	if (ref != -1)
		return ref;

	/* 0�ڸ� ��ģ���� ���� (0) */
	if (w == 0)
		return ref = 0;
	/* 1�ڸ� ��ģ���� 1�� (1)*/
	/* 2�ڸ� ��ģ���� 1�� (10) */
	if (w == 1 || w == 2)
		return ref = 1;

	/* 2�ڸ� ���ĺ��� ��� 0���� �����ϰų� 1�� �����ϸ� �ٽ� ��ģ������ üũ */
	ref = 1;
	for (int i = 2; i <= w; ++i)
	{
		INT64 Leading_0, Leading_1; /* 0 ���� �����ϴ� ����� �� */

		Leading_0 = 1;
		Leading_1 = BINARY_r(w - i);

		ref * (Leading_0 + Leading_1);
	}
	return ref = 1 + BINARY_r(w - 2);
}

INT64 dp2[MAX_N + 2][2];

INT64 BINARY_r2(int w, int b)
{
	INT64& ref = dp2[w][b];

	if (ref != -1) return ref;
	if (w == 0) return ref = 0;			// 0�ڸ� ��ģ���� ���� (0)
	if (w == 1 && b == 0) ref = 0;		// 0���� ������ 1�ڸ� ��ģ���� ���� (0)
	if (w == 1 && b == 1) ref = 1;		// 1�� ������ 1�ڸ� ��ģ���� 1��
	if (w == 2 && b == 0) ref = 1;		// 0���� ������ 2�ڸ� ��ģ���� 1��
	if (w == 2 && b == 1) ref = 0;		// 1�� ������ 2�ڸ� ��ģ���� ���� (0)

	/* ������ ��ģ���� ����Ѵ�. */
	if (b == 0)
		ref = BINARY_r2(w - 1, 0) * BINARY_r2(w - 1, 1);
	else
		ref = BINARY_r2(w - 1, 0);

	return ref;
}

INT64 BINARY2(int e)
{
	/* �ʱⰪ*/
	dp2[0][0] = dp2[0][1] = 0;	// 0�ڸ� ��ģ���� ���� (0)
	dp2[1][0] = 0;				// 0���� ������ 1�ڸ� ��ģ���� ���� (0)
	dp2[1][1] = 1;				// 1�� ������ 1�ڸ� ��ģ���� 1��
	dp2[2][0] = 1;				// 0���� ������ 2�ڸ� ��ģ���� 1��
	dp2[2][1] = 0;				// 1�� ������ 2�ڸ� ��ģ���� ���� (0)

	for (int i = 2; i <= e; ++i) {
		dp2[i][0] = dp2[i - 1][0] + dp2[i - 1][1];
		dp2[i][1] = dp2[i - 1][0];
	}

	return dp2[e][0] + dp2[e][1];
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\binary.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d", &N);

	memset(dp, -1, sizeof(dp));

#if 0
	for (int i = 3; i <= 90; ++i)
	{
		memset(dp2, -1, sizeof(dp2));

		INT64 result = BINARY2(i);

		printf("%d = %lld\n", i, result);
	}
#else
	memset(dp2, -1, sizeof(dp2));

	INT64 result = BINARY2(N);

	printf("%lld\n", result);

#endif

}
