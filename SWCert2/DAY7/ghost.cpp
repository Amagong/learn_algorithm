/*
 * ���ɼ� 
 *
 --
ù ��°�ٿ� �� ���� W �� H�� ������ ���̿� �ΰ� �־�����. (2��W,H��1500)
�� ��° �ٺ��� H�ٿ� ���� �� �ٿ� W���� ���ڰ� �־�����.

�� ���ڴ� X, O, S, E �� �ϳ��� ��ü ���ڵ� �� S�� E�� ��Ȯ�� �ϳ����� ����ȴ�.

X�� ó������ �μ��� ���ڸ� ��Ÿ����.
O�� ���� ��� ������ �� ������, ���� ���� �μ����� ���ڸ� ��Ÿ����.
S�� ó�� ���� �� �ִ� ������ ��ġ�� ��Ÿ����.
E�� ���ɼ��� ����Ʈ ��ġ�� ��Ÿ����.
 --
 
�׷����� �����ؼ� BFS�� ����Ѵ�. 
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

const int MAX_N = 1500;

int H, W;

char board[MAX_N+9][MAX_N+9];
int  dist[MAX_N+9][MAX_N+9];

int GHOST()
{
	BOX s, e;
	
	/* find s,e & init dist */
	for (int i = 1; i <= H; ++i)
		for (int j = 1; j <= W; ++j) {
			dist[i][j] = -1;
			if (board[i][j] == 'S')
				s.first = i, s.second = j;
			else if (board[i][j] == 'E')
				e.first = i, e.second = j;
		}

#ifdef DEBUG
	printf(" H = %d, W = %d\n", H, W);
	printf(" found s = (%d, %d)\n", s.first, s.second);
	printf(" found e = (%d, %d)\n", e.first, e.second);
#endif
	/* find ways (BFS) */
	queue<BOX> q;
	
	dist[s.first][s.second] = 0;
	q.push(s);
	while (!q.empty()) {
		BOX top = q.front(); q.pop();
		vector<BOX> iter;
		
		iter.clear();
		if (top.first > 1) 
			iter.push_back(BOX(top.first-1, top.second));
		if (top.first < H)
			iter.push_back(BOX(top.first+1, top.second));
		if (top.second > 1)
			iter.push_back(BOX(top.first, top.second-1));
		if (top.second < W)
			iter.push_back(BOX(top.first, top.second+1));
			
		for (int i = 0; i < iter.size(); ++i) {
#ifdef DEBUG
			printf(" -- (%d, %d) )iteration : (%d, %d) state = '%c'\n", top.first, top.second, iter[i].first, iter[i].second, board[iter[i].first][iter[i].second]);
#endif			
			if (board[iter[i].first][iter[i].second] != 'X' && dist[iter[i].first][iter[i].second] == -1) {
				/* reachable, and not visited */
				dist[iter[i].first][iter[i].second] = 1 + dist[top.first][top.second];
				q.push(BOX(iter[i]));
			}
		}
	}
	
	return dist[e.first][e.second];
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\ghost.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	
	scanf("%d %d", &W, &H);

	for (int i = 1; i <= H; ++i) {
		scanf("%s\n", &board[i][1]);
	}
		
#ifdef DEBUG
	for (int i = 1; i <= H; ++i)
		printf("%s\n", &board[i][1]);
#endif	

	int result = GHOST();
	printf("%d\n", result);
	return 0;
}
