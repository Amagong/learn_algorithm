/*
 * ��ũ��
 * 
 --
�ҵ��� ��ũ���� �� �����̴�! �� ���� K(1��K��100)������ �ҵ��� 
N(1��N��1000) ���� �������� �ϳ��� ���������� Ǯ�� ��� �ִ�. �� ���������� ������ 
1,2,?,N�̶�� �������.

�� ���������� M(1��M��10000) ���� �ܹ��� ��� ����Ǿ� �ִ�. (��� �浵 ������� �������� ���� �ʴ�.)

�ҵ��� �׵��� ��ũ�е��� ���� ���������� ���̱⸦ ���Ѵ�. ������ ����� �ҵ��� ��� �������� 
������ �� ���� ���ɼ��� �ִ�.(�ܹ��� �����̱� ������) �ҵ��� ���� �󸶳� ���� ���������� ��� 
�ҵ��� ���� �� �ִ��� ���������.
 --
 
 ���ް����� ���� ã�� ���� DFS�� ����Ѵ�. 
 ���� ��ġ���� DFS Ž���� �ϸ鼭 Ž���� ��忡 +1�� �߰��Ѵ�.
 ��� �ҵ��� Ž���� ���� �Ŀ� ����� ī��Ʈ���� �ҵ��� ������ŭ �ִ� ������ ���̴�. 
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG

using namespace std;

typedef long long INT64;
typedef pair<int, int> BOX;

const int MAX_K = 100;
const int MAX_N = 1000;
const int MAX_M = 10000;

struct TREE {
	int parent;
	vector<int> childen;
};

int K, N, M;

int KLOC[MAX_K+9];
TREE tree[MAX_N+9];
int visited[MAX_N+9];
int visit_count[MAX_N+9];

void dfs(int n)
{
	visited[n] = 1;
	for (int i = 0; i < tree[n].childen.size(); ++i) {
		if (! visited[tree[n].childen[i]]) 
			dfs(tree[n].childen[i]);
	}
	visit_count[n] ++;
}

vector<int> PICNIC()
{
	memset(visit_count, 0, sizeof(visit_count));
	
	for (int i = 1; i <= K; ++i) {
		memset(visited, 0, sizeof(visited));
		dfs(KLOC[i]);
		
#ifdef DEBUG
	printf("after %d : ", i);
	for (int i = 1; i <= N; ++i) 
		printf("%d ", visit_count[i]);
	printf("\n");
#endif		
	}
	
	vector<int> result;
	
	for (int i = 1; i <= N; ++i) {
		if (visit_count[i] == K) 
			result.push_back(i);
	}
	return result;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\picnic.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	
	scanf("%d %d %d", &K, &N, &M);

	for (int i = 1; i <= K; ++i) 
		scanf("%d\n", KLOC + i);
		
	for (int i = 1, a, b; i <= M; ++i) {
		scanf("%d %d", &a, &b);
		tree[a].childen.push_back(b);
	}
	
	vector<int> result = PICNIC();	
	printf("%d\n", result.size());
	return 0;
}
