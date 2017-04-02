/*
 * ���簢�� 
 *
 --
 1�θ� �̷���� ���簢���� 1-���簢���̶�� �Ѵ�.
 0�� 1�� �̷���� N*N �簢���� �־��� ��, ũ�� 2*2 �̻��� 1-���簢���� ã�� ������ �������.
 
 MAX_N = 3000 
 O (N^2)
 --
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N           3007

using namespace std;

typedef long long INT64;
typedef pair<int, int> PPI;

int CASE; 
int N, K; 
int A[MAX_N][MAX_N];
INT64 D[MAX_N][MAX_N];

/*
 * D[i][j] --> 0 .. k 
 * 
 * ����: (i, j) ��ǥ�� �������� �ϴ� ���簢���� ���� ��� 1�� ä���� ���� 
 *     D[i][j] = 0 : A[i][j]������ 1�� �ƴϴ�. 
 *     D[i][j] = 1 : A[i][j]�� 1�̴�.
 *     D[i][j] = 2 : A[i-1][j-1]��ǥ���� A[i][j]���� ��� 1�̴�. (k�� ���簢���� ũ��) 
 *     D[i][j] = k : A[i-k+1][j-k+1]��ǥ���� A[i][j]���� ��� 1�̴�. (k�� ���簢���� ũ��) 
 */

INT64 min3(INT64 a, INT64 b, INT64 c) 
{
	return min(a, min(b, c));
}

INT64 SQUARE2()
{
	/* �ʱ�ȭ : �� ���ʰ� �� ������ ���� ����. D[i][j]�� k���� 1�� ����  */ 
	for (int i = 1; i <= N; ++i) {
		D[i][1] = (INT64) A[i][1];
		D[1][i] = (INT64) A[1][i];
	}

	/* 2..N���� D[i][j]�� ���Ѵ�. */
	INT64 result = 0ll;
	
	for (int i = 2; i <= N; ++i)	
		for (int j = 2; j <= N; ++j) {
			if (A[i][j] == 0) 
				D[i][j] = 0ll;
			else {
				D[i][j] = min3(D[i-1][j], D[i-1][j-1], D[i][j-1]) + 1ll;
				if (D[i][j] > 1ll)
					result += (D[i][j] - 1ll);
			}
		}	
		
#ifdef DEBUG
	printf("D = \n");
	for (int i = 1; i <= N; ++i, printf("\n"))	for (int j = 1; j <= N; ++j) {
		printf("%5lld", D[i][j]);
	}
#endif
	return result;
}

int main()
{
#ifdef DEBUG
	freopen("input\\square1.txt", "r", stdin);
	freopen("output\\result.txt", "w", stdout);
#endif	

	scanf("%d", &N);
	
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			scanf("%d", &A[i][j]);
		
#ifdef DEBUG
	printf("A = \n");
	for (int i = 1; i < N; ++i, printf("\n"))	for (int j = 1; j < N; ++j) {
		printf("%5d", A[i][j]);
	}	
#endif
	INT64 result = SQUARE2();
	
	printf("%lld\n", result);
	return 0;
}

