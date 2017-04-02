/*
 * ������ �ִ�� ���ϱ�  
 *
 --
 ��� ���� ���� ������ �ִ� N���� �ܾ簣 ���̿� ������ �ű�� ���� 
N?1���� �������� ��ġ�ߴ�. (2��N��50,000). ���Ǹ� ���� �� �ܾ簣�� 1...N�̶�� ����. 
�� �������� �� ���� �ܾ簣�� �����ϰ�, ��� �ܾ簣�� ��������� ���� ����Ǿ� �ִ�.

���� K���� �ܾ簣 ���̿��� ������ ������ �ְ�ް� �ִ� (1��K��100,000). 
i��° ���� �� �� �ܾ簣 si�� ti�� �־�����. �� ���� ���� ������ �� ������ ������. 
���� �� �ܾ簣���� ������ ������ ���� �������� �� �� ���� �����ȴ�. �ֳ��ϸ� � �ܾ簣�� ���� 
K����� ���İ��� ������ �� ���� �ֱ� �����̴�. � �ܾ簣�� �������� ���� ���� �ִ��� ���϶�. 

���� ������ si�� ti�� ����� ��� �����ٸ�, �ܾ簣 si�� ti, �׸��� 
�� ���� ����ϴ� ���� �ܾ簣�鿡 ������ ����Ѵٰ� �����ϸ� �ȴ�.
 -- 
 * 
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N         50007
#define MAX_Q		1000007

using namespace std;

typedef long long INT64;
typedef pair<int, int> PPI;

int CASE; 
int N, K; 

struct NODE  {
	int jobs;
	int milk;
	vector<int> edges;
};

struct QUERY {
	int s, t;	
};

NODE  nodes[MAX_N];
QUERY querys[MAX_Q];
int   VNODE_jobs;

int parent[MAX_N][20];
int depth[MAX_N];

/*
 * Build LCA Table
 *
 * input parameters : start node (s)
 *
 * output 
 *     parent[i] - i����� parent history maps 
 *     depth[i]  - i����� depth
 * 
 * �ð��������⵵ : O(n log n) 
 */
void buildLCATable(int s)
{
	memset(depth, -1, sizeof(depth));
	memset(parent, 0, sizeof(parent));

	/* build depth + first ancestor(direct parent) using BFS */
	queue<int> q;
	
	parent[s][0] = s;	/* �ڱ� �ڽ� */ 
	depth[s] = 0;		/* ���̴� 0���� ���� */ 
	q.push(s);
	while(!q.empty()) {
		int here = q.front(); q.pop();
		
		for (int i = 0; i < nodes[here].edges.size(); ++i) {
			int n = nodes[here].edges[i];
			
			if (depth[n] == -1)	{				/* not visited */
				depth[n] = 1 + depth[here];		/* here + 1 ���� */ 
				parent[n][0] = here;			/* ù��° ancestor�� parent */ 
				q.push(n);
			}
		}
	}
	
	/* build ancestors... */
	
	/*
	 * k = 0 : 2^0 = parent
	 * k = 1 : 2^1 = ancestor 2 upside 
	 * k = 2 : 2^2 = ancestor 4 upside
	 * k = 3 : 2^3 = ancestor 8 upside
	 *  :
	 * k = 20 : 2^20 = ancestor 2^20 upside
	 *
	 */
	for (int k = 1; k < 20; ++k)
		for (int i = 1; i <= N; ++i)
			parent[i][k] = parent[parent[i][k-1]][k-1];
			
#ifdef DEBUG
	printf("Depth:\n");
	for (int i = 1; i <= N; ++i) {
		printf("%3d ", depth[i]);
	}
	printf("\n");
	
	printf("Parent:\n");
	for (int i = 0; i <= 5; ++i) {
		printf("%d : ", i);
		for (int j = 1; j <= N; ++j) {
			printf("%3d ", parent[j][i]);
		}
		printf("\n");
	}
	printf("\n");
#endif			
}

/*
 * findLCA 
 *
 * input parameters
 *    a , b : ������ ���
 *
 * output
 *    a, b�� ������������ (����: a, b�� ������߿� ���� ���� ������ ����) 
 */
int findLCA(int a, int b)
{
#ifdef DEBUG11
    printf("+ findLca(%d, %d)\n", a, b);
	printf("  - depth[%d] = %d, depth[%d] = %d\n", a, depth[a], b, depth[b]);
	printf("  - parent[%d] = %d, parent[%d] = %d\n", a, parent[a][0], b, parent[b][0]);
#endif
	/* 
	 * step1: depth�� �����ϰ� �����.
	 */ 	 
	if (depth[a] < depth[b]) swap(a, b);   /* a�� �� ũ���� �����. */ 

	/* a�� depth�� ���������� a�� ancestor���� ���� �ø���. */ 
	for (int i = 0; i < 20; ++i)
		if (((1 << i) & (depth[a] - depth[b])) != 0) {
			a = parent[a][i];
		}
	
	/* ������ depth���� a = b�� �� parent�� ���ٸ� �̹� ã�� ���� 
	 * �׿ܿ� ��쿡 ���ؼ� ã�´�. 
	 */ 
	if (a != b) {
		/*
		 * step2: �� �������� �ּ� ����������� �����´�.  
		 */
		for (int i = 19; i >= 0; --i) 
			if (parent[a][i] != parent[b][i]) {
				a = parent[a][i];
				b = parent[b][i];
			}		
			
		a = parent[a][0]; 
	}
	
#ifdef DEBUG11
	printf(" -> %d\n", a);
#endif
	return a;
}

int visited[MAX_N];

int milk_update(int s)
{
	visited[s] = 1;
	
	nodes[s].milk = nodes[s].jobs;
	
	for (int i = 0; i < nodes[s].edges.size(); ++i) {
		if (! visited[nodes[s].edges[i]]) {
			nodes[s].milk += milk_update(nodes[s].edges[i]);
		}
	}
	
	return nodes[s].milk;
}

int MILK()
{
	buildLCATable(1);
	
	for (int i = 1; i <= K; ++i ) { 
		int s = querys[i].s;
		int t = querys[i].t;
		int lca = findLCA(s, t);
		
		if (lca == s) {
			/* t���� s(lca)�� parent���� +1, -1�� �߰��Ѵ�. */
			nodes[t].jobs ++;
			nodes[(lca == 1) ? 0 : parent[lca][0]].jobs --;	
		} else if (lca == t) {
			nodes[s].jobs ++;
			nodes[(lca == 1) ? 0 : parent[lca][0]].jobs --;	
		} else {
			/* s, lca(s,t)�� Parent �� +1, -1�� �߰��Ѵ�. */ 
			nodes[s].jobs ++;
			nodes[(lca == 1) ? 0 : parent[lca][0]].jobs --;
			
			/* t, lca(s,t)�� +1, -1�� �߰��Ѵ�. */ 
			nodes[t].jobs ++;
			nodes[lca].jobs --;			
		}

#ifdef DEBUG
	printf("Job Status: add (%d, %d) = lca(%d)\n", querys[i].s, querys[i].t, lca);
	for (int i = 0; i <= N; ++i) printf("%3d", i);
	printf("\n");
	for (int i = 0; i <= N; ++i) printf("%3d", nodes[i].jobs);
	printf("\n");
#endif
		
	}
	
	memset(visited, 0, sizeof(visited));	
	int milk = milk_update(1);
	
#ifdef DEBUG
	printf("Milk n");
	for (int i = 0; i <= N; ++i) printf("%3d", i);
	printf("\n");
	for (int i = 0; i <= N; ++i) printf("%3d", nodes[i].milk);
	printf("\n");
#endif
	for (int i = 0; i <= N; ++i) milk = max(milk, nodes[i].milk);
	return milk;
}

int main()
{
#ifdef DEBUG
	freopen("input\\milk.txt", "r", stdin);
	freopen("input\\result.txt", "w", stdout);
#endif	

	scanf("%d %d", &N, &K);
	
	for (int i = 1, a, b; i <= N-1; ++i ){		
		scanf("%d %d", &a, &b);
		nodes[a].edges.push_back(b);
		nodes[b].edges.push_back(a);
	}
		
	for (int i = 1, a, b; i <= K; ++i) {
		scanf("%d %d", &a, &b);
		querys[i].s = a;
		querys[i].t = b;
	}

	int result = MILK();
	
	printf("%d\n", result);
	return 0;
}

