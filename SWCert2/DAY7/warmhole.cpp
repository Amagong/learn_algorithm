/*
 * ��Ȧ
 *
 --
 ���� ���� ������� Ž���ϴ���, ���� �� ���� ���� ��Ȧ�� �߰��ߴ�. ��Ȧ�� ���� ���忡�� 
 �ٸ� ���������� �̻��� �ܹ��� ��ην� ����� ���� �ð����� �����ð����� �ð��� �ǵ�����. 
 ���� ������ N���� ����� M���� ����� ����, W���� ��Ȧ�� �����Ǿ��ִ�. �׸��� �� ������ ���ǻ� 
 ����1, ����2, �� ,���� N�̶�� �̸��ٿ�����.

���� ���ڱ� ������ġ���� ����ؼ� ������ �ϴ� �ٽ� ������ġ�� ���ƿ��� �� �ð��� �ǵ��� �� �ִ� 
��찡 �ִ��� �ñ�������. ���� ���� �ð��� �ǵ����� ������ �������� ���ϴ� ���α׷��� �ۼ��Ͽ���
 -- 
 
 ���������� ���� ����Ŭ�� ����� ��츦 üũ�ϴ� ����.
 ������Ʈ�� ����Ͽ� ���Ѵ����� N+1�� �������� ������ �ʴ��� üũ. 
 
 1. ������ ��带 ����Ͽ� ��� �������� �Ÿ��� 0�� ����  �߰�
 2. ������ N���� ��忡 ���� N���� relaxation �õ�
 3. N+1���� ����ؼ� relaxation�� �Ǹ� ���������� ����. 
  
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

#define MAX_V 509
#define MAX_E 2509
#define MAX_W 200

int CASE; 
int V, E, W;

int A[MAX_V+9][MAX_V+9];
vector<BOX> nodes[MAX_V+9];

int D[MAX_V+9];

/* bellman Ford */

bool WARP()
{
	queue<int> q2[2], *q, *nq;
	
	q = &q2[0], nq = &q2[1];
	
	/* start from Virtual Node & dist zero !! */
	for (int i = 1; i <= V; ++i) {
		/* relax all to zero, immedately */
		D[i] = 0;
		q->push(i);
	}

	bool relaxed;
	for (int iter = 1; iter <= V; ++iter) {		
		relaxed = false;
#ifdef DEBUG
		printf(" iter(%d) ", iter);
		for (int k = 1; k <= V; ++k) {
			printf("%d ", D[k]);
		}
		printf("\n");
#endif
		while (!q->empty()) {
			int here = q->front(); q->pop();
			
#ifdef DEBUG
			printf(" iter(%d) pop : %d (cost = %d)\n", iter, here, D[here]);
#endif			
			for (int j = 0; j < nodes[here].size(); ++j) {
				BOX& there = nodes[here][j];
				int cost  = D[here] + there.second;
				
				if (cost < D[there.first]) {
					/* relaxed */
					relaxed = true;
					D[there.first] = cost;
					nq->push(there.first);
#ifdef DEBUG
					printf(" iter(%d) relaxed & push : %d (cost = %d)\n", iter, there.first, cost);
#endif	
				}
			}			
		}

		if (relaxed && iter == V) 
			return true;
		
		swap(q, nq);
	}
	
	return false;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\warmhole.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif

	scanf("%d", &CASE);
	for (int t = 1; t <= CASE; ++t) {
		scanf("%d %d %d", &V, &E, &W);	
		
		for (int i = 1; i <= V; ++i)
			for (int j = 1; j <= V; ++j)
				A[i][j] = 987654321;
		
		for (int i = 1, a, b, c; i <= E; ++i) {
			scanf("%d %d %d", &a, &b, &c);
			
			A[a][b] = min(A[a][b], c);
			A[b][a] = min(A[b][a], c);
		}		
		
		for (int i = 1, a, b, c; i <= W; ++i) {
			scanf("%d %d %d", &a, &b, &c);
			
			A[a][b] = min(A[a][b], -c);
		}		
		
		/* build graph */
		for (int i = 1; i <= V; ++i)
			for (int j = 1; j <= V; ++j) {
				if (A[i][j] != 987654321) {
					nodes[i].push_back(BOX(j, A[i][j]));
				}
			}

#ifdef DEBUG
		for (int i = 1; i <= V; ++i) {
			printf(" %d : ", i);
			for (int j = 0; j < nodes[i].size(); ++j) 
				printf("%d ", nodes[i][j]);
			printf("\n");
		}
#endif
		bool result = WARP();
		printf("%s\n", result ? "YES" : "NO");
			
	}
	
	return 0;
}
