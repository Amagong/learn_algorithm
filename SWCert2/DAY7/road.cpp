/*
 * ��ӵ��� �Ǽ�
 *
 --
ù ��° �ٿ� ������ �� N�� �־�����. (2 �� N �� 50,000)
�� ��° �ٿ� ���� �ĺ��� �� M�� �־�����. (1 �� M �� 200,000)
�� ��° �ٺ��� M���� �ٿ� ���� �� ���� �ĺ��� ���� s, e, c�� �־�����. s�� e�� ���� �ĺ��� �մ� �� ������ ��ȣ�̰�, c�� �� ���θ� �Ǽ��ϴµ� ��� ����̴�. (1 �� s, e �� N, 1 �� c �� 10,000)
�׻� ��� ���ø� �մ� ��ӵ��θ� �Ǽ��� �� �ִ� �Է¸� �־�����.
 --
 
 ũ�罺Į �˰����� ����Ͽ� MST�� ���Ѵ�. 
 priority_queue�� union-find set�� ����Ѵ�.
 * 
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
const int MAX_V = 50000;
const int MAX_E = 200000;
const INT64 MAX_W = 1000000000000ll;

struct ST_NODE {
	int e, w;
	
	ST_NODE() { }
	void add_edge(int e_, int w_) {
		e = e_; w = w_;
	}
};

struct EDGEINFO {
	int from, to;
	int cost;
	
	EDGEINFO() {}
	void set(int a, int b, int c) { from = a, to = b, cost = c; }
};

struct UFSET {
	int  ufset[MAX_V+9];
	
	UFSET() { }
	void init(int n) {
		for (int i = 0; i <= n; ++i) 
			ufset[i] = i;
	}
	int find(int n) {
		if (n == ufset[n]) return n;
		return ufset[n] = find(ufset[n]);
	}
	bool isUnion(int a, int b)
	{
		return find(a) == find(b);
	}
	void makeUnion(int a, int b)
	{
		ufset[find(a)] = b;
	}
};

int V, E;
ST_NODE nodes[MAX_V+9];
EDGEINFO edges[MAX_E+9];
UFSET ufset;

void init_g(int v)
{
	for (int i = 1; i <= v; ++i) 
		nodes[i].add_edge(0, 0);		
	
	ufset.init(v);
}

struct compare_EDGEINFO {
	bool operator()(const EDGEINFO& lhs, const EDGEINFO& rhs) {
		return lhs.cost > rhs.cost;  /* Min-Heap */
	}	
};

int ROAD_COST()
{
	priority_queue<EDGEINFO, vector<EDGEINFO>, compare_EDGEINFO> pq;	
	for (int i = 1; i <= E; ++i)
		pq.push(edges[i]);
	
	int total_cost = 0;
	
	while (!pq.empty()) {
		EDGEINFO edge = pq.top(); pq.pop();
#ifdef DEBUG
		printf(" -- peek edge (%d, %d, %d)\n", edge.from, edge.to, edge.cost);
#endif		
		if (! ufset.isUnion(edge.from, edge.to)) {
			nodes[edge.from].add_edge(edge.to, edge.cost);
			total_cost += edge.cost;
			
			ufset.makeUnion(edge.from, edge.to);
		}
	}
	return total_cost;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\road.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	
	scanf("%d %d", &V, &E);
	
	init_g(V);
	
	for (int i = 1, a, b, c; i <= E; ++i) {
		scanf("%d %d %d", &a, &b, &c);
		edges[i].set(a, b, c);
	}
	
	int result = ROAD_COST();
	printf("%d\n", result);
	return 0;
}

