/*
 * ������ 
 *
 --
 �Է����� �־��� ������ �� ���� ���� N�� �� ���簢��ĭ�� ��(0 �Ǵ� 1)�� �־��� �� �߸� ������ �� 
 0���� ĥ���� �������� ���� 1�� ĥ���� �������� ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
 
 <�Է�>
 ù° �ٿ��� ��ü ������ �� ���� ���� N�� �־��� �ִ�. 
 N�� 2,4,8,16,32,64,128 �� �ϳ��̴�. �������� �� �������� ���簢��ĭ���� ���� ���ٺ��� ���ʷ� 
 ��° �ٺ��� ������ �ٱ��� �־�����.

�� ���� ���̿��� ��ĭ�� �ϳ��� �ִ�.  
 --
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
typedef pair<int, int> INTPAIR;

#define MAX_N 509

int CASE; 
int N;
int A[MAX_N][MAX_N];

/*
 * 4�������� �����Ͽ� ����
 *
 * ��ü 0�� ������ 1�� ������ �����ϵ� All Zero/All One�� ���ؼ� 
 * ��ǥ�� �Ѱ��� ������. (�̶�, ���� ������ ���°� ����) 
 */
INTPAIR COUNT(int sx, int sy, int size)
{
	if (size == 1)	{
		return A[sx][sy] ? INTPAIR(0, 1) : INTPAIR(1, 0);
	}
	
	int halfN = size / 2;
	
#ifdef DEBUG
	printf(" -- COUNT (%d, %d, %d)\n", sx, sy, size);
	printf("    -- Q1 (%d, %d, %d)\n", sx, sy, halfN);
	printf("    -- Q2 (%d, %d, %d)\n", sx + halfN, sy, halfN);
	printf("    -- Q3 (%d, %d, %d)\n", sx, sy + halfN, halfN);
	printf("    -- Q4 (%d, %d, %d)\n", sx + halfN, sy + halfN, halfN);
#endif
	
	INTPAIR q1 = COUNT(sx, sy, halfN);
	INTPAIR q2 = COUNT(sx + halfN, sy, halfN);
	INTPAIR q3 = COUNT(sx, sy + halfN, halfN);
	INTPAIR q4 = COUNT(sx + halfN, sy + halfN, halfN);
	
	int zeros = q1.first + q2.first + q3.first + q4.first;
	int ones = q1.second + q2.second + q3.second + q4.second;

#ifdef DEBUG
	printf(" !! COUNT (%d, %d, %d) --> (%d, %d) size^2 = %d\n", sx, sy, size, zeros, ones, size*size);
#endif	

	if (zeros == 0)
		return INTPAIR(0, 1);
	else if (ones == 0)
		return INTPAIR(1, 0);
	else
		return INTPAIR(zeros, ones);
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\divide.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	

	scanf("%d", &N);
	
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j) 
			scanf("%d", &A[i][j]);
			
	INTPAIR result = COUNT(1, 1, N);
	printf("%d\n%d\n", result.first, result.second);
	return 0;
}

