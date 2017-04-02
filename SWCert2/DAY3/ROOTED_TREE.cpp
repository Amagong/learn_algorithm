/* 
 * ����Ȯ�νý��� (Ž��: ROOTED TREE)
 *
 --
 --
 �ܼ��ϰ� ������踸�� �ľ��ϱ� ���ؼ��� DFS�� ����Ͽ� traversal order�� ����Ͽ�
 ancestor ����� x�� enter time ~ leave time���� y�� enter ~ leave time�� ���
 ���ԵǴ����� Ȯ���Ѵ�. 
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
const int MAX_N = 100000;
const int MAX_Q = 10000000;

int CASE, N, ROOT, QUERY;

int A[MAX_N + 9];

struct node {
	int parent;
	int enter, leave;
	vector<int> children;
};

node nodes[MAX_N + 9];

/* dfs */
int tick_count;

void make_time_travel(int root)
{
	nodes[root].enter = tick_count++;

	for (int i = 0; i < nodes[root].children.size(); ++i)
	{
		make_time_travel(nodes[root].children[i]);
	}
	nodes[root].leave = tick_count++;
}

bool ancestor(int a, int b)
{
	return (nodes[a].enter <= nodes[b].enter) && (nodes[b].leave <= nodes[a].leave);
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\rooted_tree.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d %d %d", &N, &ROOT, &QUERY);
	for (int i = 1; i <= N; ++i)
	{
		scanf("%d", A + i);

		nodes[i].enter = 0; 
		nodes[i].leave = 0;
		if (i != ROOT) {
			nodes[i].parent = A[i];
			nodes[A[i]].children.push_back(i);
		}
	}

	tick_count = 1;
	make_time_travel(ROOT);

	for (int i = 0; i < QUERY; ++i)
	{
		int x, y;

		scanf("%d %d", &x, &y);
		if (ancestor(x, y))
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
