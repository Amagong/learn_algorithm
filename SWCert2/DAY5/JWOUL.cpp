/* Ž�� */

/* 
ù° �ٿ� N�� K�� �־�����. (1 �� N, K �� 300,000)

���� N�� �ٿ��� �� ������ ���� Mi�� Vi�� �־�����. (1 �� Mi, Vi �� 1,000,000)

���� K�� �ٿ��� ���濡 ���� �� �ִ� �ִ� ���� Ci�� �־�����. (1 �� Ci �� 100,000,000)

��� ���ڴ� ���� �����̴�.

*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

#define DEBUG 

typedef long long INT64;
typedef pair<int, int> intpair;

const int MAX_N = 300000;

int N, K;

intpair A[MAX_N + 9];
int     C[MAX_N + 9];
int     choose[MAX_N + 9];
priority_queue<int > pq;

// bool cmp(const intpair& a, intpair& b) { return (a.first < b.first);  }

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\jwoul.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif

	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; ++i)
		scanf("%d %d", &A[i].first, &A[i].second);

	for (int i = 1; i <= K; ++i)
		scanf("%d", C + i);

	sort(A + 1, A + N + 1);
	sort(C + 1, C + K + 1);

	INT64 sum = 0;

	memset(choose, 0, sizeof(choose));
	for (int i = 1, j = 1; i <= K; ++i) {
		/* C[i] ���Ը� ���� �� �ִ� �������� priority_queue�� ���� �ִ´�... ���� ������ ���� (�̹� ��� Ư�� ���Ը� �ѱ� ������ ���ʿ�) */
		for (; j <= N && A[j].first <= C[i] ; j++)
			pq.push(A[j].second);

		if (!pq.empty())
		{
			int mv = pq.top(); pq.pop();
#ifdef DEBUG
			printf("%5d->[%d]\n", i, mv);
#endif
			sum += (INT64) mv;
		}
	}

	printf("%lld\n", sum);
	return 0;
}