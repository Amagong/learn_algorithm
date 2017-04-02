/* 
 * �����ڸ���(Rod Cutting)
 *
 --
 ���̰� N�� ����Ⱑ �ִ�. ����⸦ ���̰� �ڿ����� �ǵ��� ���� �������� �ڸ� �� �ִ�. 
 �� ���̿� ���� ����ġ�� ���� ��, ����ġ ���� �ִ밡 �ǵ��� ����⸦ �ڸ���.

���� ���, ���̰� 4�� ����Ⱑ �ְ� �� ���� �� ����ġ�� �Ʒ��� ���ٰ� ����.

|  length  | 1 | 2 | 3 | 4 |
|----------|---|---|---|---|
|   cost   | 1 | 5 | 8 | 9 |
�� ��, ���� 2�� ����Ⱑ �� ���� �ǵ��� ��ü ����⸦ �ڸ� ��� ��ü ����ġ�� 10�� �Ǿ� �ִ밡 �ȴ�.

<�Է�>
ù �ٿ� ������� ���� N�� �־�����. (1��N��3,000)

��° �ٿ� N���� �ڿ����� �������� ���еǾ� �־����µ�, i��°�� �־����� ���� ���̰� 
i�� ������� ����ġ�� �ǹ��Ѵ�. �� �� �־����� ���� 1,000�� ���� �ʴ´�. 
 --
 
<Ǯ��>

C[i] = ���̰� i�� ����� ������ ����ġ
D[i] = ���̰� i�� ����⸦ ���� �������� �߶��� ��, ��ü ����ġ�� �ִ밪

	- D[0] = 0
	- D[i] = max(D[j] + C[i-j]) (for all 0 �� j �� i-1)
	         �ֱٿ� �ڸ� ����� ������ ���̰� i-j�� ��
 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

// #define DEBUG

const int MAX_N = 3000;

int N; 
int A[MAX_N + 1];

int dp[MAX_N + 1];
int dph[MAX_N + 1];

int RC()
{
	dp[0] = 0;

	for (int n = 1; n <= N; ++n) {
		int q = -1;

		for (int cut = 1; cut <= n; ++cut) {
			int p = A[cut];
			int r = dp[n - cut];

			if (q < p + r) {
				q = p + r;
				dph[n] = cut;
			}
		}
		dp[n] = q;
	}
	return dp[N];
}

int RC_r(int n)
{
	int& ref = dp[n];

	if (ref != -1)
		return ref;

	if (n == 0)
		return ref = 0;

	ref = 0;
	int q = -1;
	for (int cut = 1; cut <= n; ++cut) {
		int p = A[cut];
		int r = RC_r(n - cut);

		if (q < p + r) {
			q = p + r;
			dph[n] = cut;
		}
	}

	return ref = q;
}

int main()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &A[i]);
	}

	memset(dp, -1, sizeof(dp));
	memset(dph, -1, sizeof(dph));

	int result = RC_r(N);
	printf("%d\n", result);

#ifdef DEBUG
	printf("\nEnter any number:...");
	int ch;
	
	scanf("%d", &ch);
#endif
	return 0;
}

#if 0

A[i] = ���̰� i�θ���� ������ ����ġ  (�Է����� �־���)
 
D[i] = ���̰� i�θ���⸦ ���� �������� �߶��� ��, ��ü ����ġ�� �ִ밪

D[0] = 0

D[i] = max(D[i-j] + A[j])   (for all 1<= j <= i)
	* �ֱٿ� �ڸ� ����� ������ ���̰� j �϶�

#endif
