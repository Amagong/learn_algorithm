/*
 * �������� 
 --
 ������ �־��� �� �̿� ���� ���� ���� �� �������� ����Ͽ� ���� ������ �Ʒ� 
 �������� �׻� ��������θ� �̵��ϴ� ����� ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

 ����� ���� ���� ������ ��ü ��츦 1234567�� ���� �������� ����Ѵ�.

<�Է�> 
ù° �ٿ��� ������ ������ ũ�� M�� ������ ũ�� N�� ��ĭ�� ���̿� �ΰ� �־�����. 
�̾� ���� M�� �ٿ� ���� �� �ٿ� N���� ���������� ���ʷ� �� ������ ���̰� �� ĭ�� 
���̿� �ΰ� �־�����. M�� N�� ���� 500������ �ڿ����̰�, �� ������ ���̴� 
1,000,000������ �ڿ����̴�
 --
 
 �Է��� ũ���� ���ǿ� ��������� �־� �׻� ���� �����ǿ����� ���� �׼Ǹ� ���Ҽ�
 �־� �޸������̼��� �̿��ϸ� �ð��� Ǯ��. 
 DFS�� ����Ͽ� Ž��. 
 
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N 507

using namespace std;

typedef long long INT64;
typedef pair<int, int> INTPAIR;

int CASE; 
int H, W;
int A[MAX_N][MAX_N];
int D[MAX_N][MAX_N];

int df[4][2] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };

int X[4]= { 1, -1, 0, 0 };
int Y[4] = { 0, 0, 1, -1 };

int dfs(int sy, int sx)
{
	if (sy == H && sx == W)
		return 1;
		
	int& possible = D[sy][sx];

	if (possible != -1)
		return possible;
	
	possible = 0;
		
	int here = A[sy][sx];	
	for (int i = 0; i < 4; ++i) {
		int dy = sy + df[i][0];
		int dx = sx + df[i][1];
		
		if (dy >= 1 && dy <= H && dx >= 1 && dx <= W) {
			int there = A[dy][dx];
			
			if (there < here) {
				possible = ( possible + dfs(dy, dx) ) % 1234567;
			}
		}
	}
	return possible % 1234567;
}

int DOWN(int sx, int sy)
{
	memset(D, -1, sizeof(D));
	
	return dfs(sx, sy);
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\down.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	

	scanf("%d %d", &H, &W);
	for (int i = 1; i <= H; ++i)
		for (int j = 1; j <= W; ++j)
			scanf("%d", &A[i][j]);
	
#ifdef DEBUG
	printf("%d %d\n", H, W);
	for (int i = 1; i <= H; ++i) {
		for (int j = 1; j <= W; ++j)
			printf("%3d", A[i][j]);
		printf("\n");		
	}
#endif
	int result = DOWN(1,1);
	
	printf("%d\n", result);
	return 0;
}

