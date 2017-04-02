/*
 * ����� ����
 *
 --
 ������ ���� ������ �־����� ��, �Ÿ��� ���� �� �� ���� ������ �Ÿ��� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
 
 <�Է�>
  �Է��� ù �ٿ� ������ �� N�� �־�����. (1 �� N �� 300) �׸��� ���� N���� �ٿ� ������ ������ 
  ��Ÿ���� ���� �ƴ� ���� N���� �������� ���еǾ� �־�����. i+1��° �ٿ��� j��°�� �־����� 
  ���� i�� ���ÿ��� j�� ���÷� ���� ������ ���̸� �ǹ��ϸ�, �� ���� 1,000,000 ���� ũ�� �ʴ�. 
  i+1��° �ٿ��� i��° ���� �׻� 0�̴�.
 -- 
 
 ��� �������� �Ÿ��� ���� �� �ִ� Floyd-Warshall �˰����� ����Ѵ�.
 
	for (int k = 1; k <= V; ++k) 
		for (int i = 1; i <= V; ++i) 
			for (int j = 1; j <= V; ++j) 
	 			D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
  
  
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
const int MAX_V = 300;
const INT64 MAX_C = 1000000000000ll;

int V;
INT64 edges[MAX_V+9][MAX_V+9];

/* Floyd Warshall
 *
 * [i]lj]
 * 
 * [k] ����
 * i ~ j : i���� j���� ���� �Ÿ��߿� �ּ� 
 */ 
INT64 D[MAX_V+9][MAX_V+9];

INT64 LONG_CITY()
{
	memset(D, -1, sizeof(D));
	
	/* init value */
	for (int i = 1;  i <= V; ++i)
		for (int j = 1; j <= V; ++j) {
			D[i][j] = edges[i][j];
		}

	/* run Floyd Warshall */
	for (int k = 1; k <= V; ++k) {
		for (int i = 1; i <= V; ++i) 
			for (int j = 1; j <= V; ++j) {
				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
#ifdef DEBUG
				printf("iteration: %d %d %d\n", k, i, j);
				for (int ii = 1; ii <= V; ++ii) {
					for (int jj = 1; jj <= V; ++jj) {
						printf("%d ", D[ii][jj]);
					}
					printf("\n");
				}
#endif
			}
	}
	
	INT64 result = 0;
	for (int i = 1; i <= V; ++i) 
		for (int j = 1; j <= V; ++j) 
			result = max(result, D[i][j]);
			
	return result;

}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\longcity.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	
	scanf("%d", &V);	
	
	for (int i = 1; i <= V; ++i) {
		for (int j = 1; j <= V; ++j) {
			scanf("%lld", &edges[i][j]);
		}
	}
	
	INT64 result = LONG_CITY();
	printf("%lld\n", result);
	return 0;
}
