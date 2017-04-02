/* 
 * Ž��: N-Queen 
 *
 --
N-Queen������ ������ �����̴�. �̴� N �� N�� ü���� ���� N���� ���� ���� ������ �� ���� ���� �����̴�.

N�� �־����� ��, ���� ���� ����� ���� ���Ͻÿ�.
 --
 
<Ǯ��>
��Ʈ��ŷ: Ư��������� Ž���ϸ鼭 ����ġ��� ����� ���� �ٿ� �ð��� Ž��

- ��κ� DFS�� �̿��� ���ȣ��� ������.
- ����ġ�⸦ ���� ������ �����ϰ� check�ϴ� ���� ������ �Ѵ�. 

N-Queen : �밢�� �� ����/���ο� 1���� check�� �Ǹ� Ư�� (i, j)��ġ�� check�� 
O(1)�� �Ҽ� ����. 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

#define DEBUG

using namespace std;

typedef long long INT64;
const int MAX_Q = 12;
int N;

int answer = 0;

int col[MAX_Q + 9];
int d1[2 * MAX_Q + 9];
int d2[2 * MAX_Q + 9];

int dfs(int i)
{
	int answer = 0;

	if (i == N)
	{
		return 1;
	}

	for (int j = 0; j < N; ++j) 
	{
		if (col[j] || d1[i + j] || d2[i - j + N - 1])
			continue;

		col[j] = d1[i + j] = d2[i - j + N - 1] = 1;
		answer += dfs(i + 1);
		col[j] = d1[i + j] = d2[i - j + N - 1] = 0;
	}

	return answer;
}

int NQUEEN(int n)
{
	return dfs(0);
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\nqueen.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d", &N);

	int result = NQUEEN(1);
	printf("%lld\n", result);
}
