/*
 *
 * �ѷ��ڽ���
 *
 --
 �ҵ��� �ѷ��ڽ��͸� �����ִ�! �ҵ��� �ڽŵ��� ������ �ִ� ���� Ȱ���ؼ� �ִ��� ��մ� �ѷ��ڽ��͸� ����� �;��Ѵ�.

�ѷ��ڽ��ʹ� ����������, ���̰� L�̴�. �ҵ��� �ѷ��ڽ��͸� ���� ��, �ѷ��ڽ��ʹ� 
N���� ��ü ������ ��ǰ���� �Ϻη� �����Ǿ�� �Ѵ�.

�� ��ǰ i�� ������ ���� Wi�� ������ �ִ�. �׸��� �پ��� ������ ���� ������, i��° ��ǰ�� ���� 
Xi�� ��ġ�� ���������θ� ���� �� �ִ�.

�ҵ��� �پ��� �ѷ��ڽ��͸� 0���� L���� ��ƴ���� ä��� �;��Ѵ�. ���� �߰��� ��ĭ�� ������ �ѷ��ڽ��͸� 
������ �� ����. ����, �� ��ǰ���� ���ļ� �ѷ��ڽ��͸� �Ǽ��ϴ� ��쵵 ����.

�� i��° ��ǰ�� "��̵�" Fi�� ���µ� ��� ��� Ci�� �ִ�. �� ����� �ѷ��ڽ��͸� �����ϴ� ��ǰ���� 
����� ������ ���ȴ�. ���������� �� ��̵��� ���� �ѷ��ڽ��͸� �����ϴ� ��ǰ���� ��̵��� ������ ���ȴ�.

�ҵ��� �� ������ B�̴�. �ҵ��� ���� ���곻���� ���� ū ��̵��� ���� �ѷ��ڽ��͸� ���� �� �ֵ��� ��������!
 --
 
 Ǯ��
 
 ��ȭ��
 
0 ~ x���� �����鼭, ��̵��� f��ŭ ���, ����� c��ŭ �� �� �ִ°�? D[x][f][c]  (true or false)
������ ū ������ ������ ���� �̵�! (f ����: 100��, c ����: 1000)
0 ~ x ���� �����鼭, ����� c��ŭ ���� �� ���� �� �ִ� ��̵�D[x][c]


 D[x][c] = max(D[x ? W[i]][c ? C[i]] + F[i]) where X[i] + W[i] = x
           ������ ��: ��� i�� ���ؼ� �����ϸ� �ȵǰ�, X[i] + W[i] = x�� i�� ��󳻾� �Ѵ�.
           
 
 */ 

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_N = 10000;
const int MAX_L = 1000;
const int MAX_B = 1000;

typedef long long INT64;
struct part {
	int x, w, f, c;
};

bool compare_x(const part& a, const part& b)
{
	return a.x < b.x;
}

int L, N, B;
part A[MAX_N + 9];

int dp[MAX_L + 9][MAX_B+9];
multimap<int, int> starts;

int lowerbound(part B[], int BN, int x)
{
	int low = 1, high = BN+1;

	while (low <= high) {
		int mid = (low + high) / 2;
		if (x < B[mid].x)
			high = mid - 1;
		else if (x > B[mid].x)
			low = mid + 1;
		else
			return mid;
	}
	return low;
}

int ROLLERCOAST(int start, int budget)
{
	static int isfirst = true;

#ifdef DEBUG
	printf("Enter (%d, %d)\n", start, budget);
#endif
	int& ref = dp[start][budget];

	if (ref != -1)
		return ref;

	if (start > L || budget < 0)
		return ref =  -10000000;

	if (start == L)
		return ref = 0;

	if (isfirst)
	{
		isfirst = false;
		sort(A + 1, A + N + 1, compare_x);
	}
	
	int idx = lowerbound(A, N, start);

#ifdef DEBUG
	printf("lb(%d) --> %d (%d)\n", start, idx, A[idx]);
#endif

	if (idx == (N + 1))
		return ref = 0;

	ref = 0;
	for (int i = idx; i <= N; ++i)
	{
		if (A[i].x != start)
			break;

		/* Use This Part */
		int used = A[i].f + ROLLERCOAST(start + A[i].w, budget - A[i].c);

		if (used > 0)
			ref = max(ref, used);
	}

	return ref;
}

int ROLLERCOAST_map(int start, int budget)
{
	static int isfirst = true;

#ifdef DEBUG
	printf("Enter (%d, %d)\n", start, budget);
#endif
	int& ref = dp[start][budget];

	if (ref != -1)
		return ref;

	if (start == L)
		return ref = 0;

	ref = -100000000;

	pair<multimap<int, int>::iterator, multimap<int, int>::iterator> iterPair = starts.equal_range(start);

	for (multimap<int, int>::iterator iter = iterPair.first; iter != iterPair.second; ++iter)
	{
		int& selected = iter->second;

#ifdef DEBUG
		printf("![%d][%d] -- map.equal_range(%d) --> %d\n", start, budget, start, selected);
#endif
		/* Possible: Use This Part */
		if (A[selected].c <= budget && (start + A[selected].w <= L))
		{
			int subproblem = ROLLERCOAST_map(start + A[selected].w, budget - A[selected].c);

			if (subproblem >= 0 && (A[selected].f + subproblem > ref))
			{
				ref = A[selected].f + subproblem;
#ifdef DEBUG
				printf("![%d][%d] -- new updated = %d\n", start, budget, ref);
#endif 
			}
		}
	}

#ifdef DEBUG
	if (ref < 0)
	{
		printf("![%d][%d] --- not found...\n", start, budget);
	}
#endif
	return ref;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\rollercoast.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif

	starts.clear();
	scanf("%d %d %d", &L, &N, &B);
	for (int i = 1; i <= N; ++i) {
		part& p = A[i];
		scanf("%d %d %d %d", &p.x, &p.w, &p.f, &p.c);
		starts.insert(pair<int, int>(p.x, i));
	}
	
	memset(dp, -1, sizeof(dp));

	int result = ROLLERCOAST_map(0, B);
	int max_result = -1;

#ifdef DEBUG
	for (int i = 1; i <= B; ++i)
		printf("%5d", dp[0][i]);
	printf("\n");
#endif
	for (int i = 1; i <= B; ++i)
		max_result = max(max_result, dp[0][i]);

	if (max_result != 0)
		printf("%d\n", max_result);
	else
		printf("-1\n");
}
