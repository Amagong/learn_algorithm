/*
 * ������ ������ ���� 
--
ù ��° �ٿ� ���������� ����� �� N�� �־�����. (1 �� N �� 100,000)

�� ��° �ٿ� ������ �� Q�� �־�����. (1 �� Q �� 200,000)

�� ��° �ٺ��� Q���� �ٿ� ���� ���ǰ� �־�����. �� ���Ǵ� ������ ���� �� �ϳ��� �־�����. (1 �� a, b �� N)

0 a b : a�� ����� b�� ����� ���� ���踦 �ξ����� �ǹ��ϴ� �����̴�.
1 a b : a�� ����� b�� ����� ���� ���迡 �ִ��� ����� �����̴�.
--

  union-find set�� ����Ͽ� üũ 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_N = 100000;
const int MAX_Q = 200000;

int N, Q;

int UF[MAX_N + 9];

int ufind(int a)
{
	if (UF[a] == a)
		return a;
	else
		return UF[a] = ufind(UF[a]);
}

void ufset(int a, int b)
{
	a = ufind(a);
	b = ufind(b);
	if (a != b)
		UF[a] = b;
}

int ufederation(int a, int b)
{
	return (ufind(a) == ufind(b)) ? 1 : 0;
}

void QUERY(int q, int a, int b)
{
	if (q == 0) {
		/* set uf (a, b) */
		ufset(a, b);
	}
	else
	{
		printf("%d\n", ufederation(a, b));
	}
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\federation.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d %d", &N, &Q);

	for (int i = 1; i <= N; i++) {
		UF[i] = i;
	}

	for (int i = 1; i <= Q; ++i) {
		int q, a, b;

		scanf("%d %d %d", &q, &a, &b);

		QUERY(q, a, b);
	}
}
