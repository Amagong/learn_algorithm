/* 
 * �����̰� ������ 
 *    Ž��/����: �Ͽ콺 
 --
 --
 ������ �ִ�/�ּ� pointer�� Ȱ���Ͽ�  ������ �յ��� �����ذ��鼭 ã�´�. 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG

using namespace std;

typedef long long INT64;

const int MAX_N = 10000000;

INT64 X;
int N; 

INT64 A[MAX_N + 9];

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\house.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%lld %d", &X, &N);

	X *= 10000000ll;

	for (int i = 0; i < N; ++i) {
		scanf("%lld", A+i);
	}

	sort(A, A + N);

	int low = 0;
	int high = N-1;
	
	while (low < high) 
	{
		INT64 SUM = A[low] + A[high];

		if (X < SUM) {
			high--;	/* ������ */
		}
		else if (X > SUM) {
			low++;	/* �ø��� */
		}
		else {
			printf("yes %lld %lld\n", A[low], A[high]);
			return 0;
		}
	}
	printf("danger\n");
	return 0;
}
