/*
 * ���� 
 *
 ---
 ������ �ǹ��� ������ �⺻���� �ǹ��̴�. ������ ���Կ� ����Ͽ� ������ ��Ģ�� ���� ���Ǳ� ������,
 ��Ģ�� ���� ��Ȯ�� ������ ����ϴ� ���� �߿��ϴ�. 
 �������� ���� ���Ը� ����, �� N �� ���� ������ �Ͽ���. 
 ������ �ǹ��� �����ϰ� �����ϱ� ���Ͽ� �� �����ϸ��� ����(���� �Ǵ� ����)�� ����Ͽ� �������� 
 �Ű��Ͽ���. ������ �ű�µ� ������ �Ǵ� ������ ���� ��Ģ�� ���ؼ� ���ȴ�.

"1�Ϻ��� N�� ������ � ���ӵ� �Ⱓ�� ���Ͽ� �� �Ⱓ ���� ������ ������ ���Ѵ�. 
��, �Ϸ� �̻��� �Ⱓ�� ����Ѵ�. ����, ��ü ������ ��� �Ⱓ�� ���Ͽ� ���� ������ ���յ� �� 
K��°�� ū ���� ������ �ȴ�. ��, ���յ��� ������������ �������� �� K��° ���̴�."

���� ���, �� 3�ϰ� ������ �Ͽ��ٸ� 1��, 1��~2��, 1��~3��, 2��, 2��~3��, 3�� �� 6���� 
�Ⱓ�� ���Ͽ� �� �Ⱓ���� ������ ������ ���ϰ�, �� �� K��° ū ���� ������ ������ �ȴ�.
 ---
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N           1000007
#define MAX_K                57
#define MIN_COST 	-1000000007

using namespace std;

typedef long long INT64;
typedef pair<int, int> PPI;

int CASE; 
int N, K; 
INT64 A[MAX_N];
INT64 LocalTopK[MAX_K];
INT64 GlobalTopK[2][MAX_K];
INT64 *global_top, *global_tmp;

/*
 * LocalTopK[i][20]   : ���� iteration���� �������� i��° ���ڸ� ������ �κ��� �������߿� 
                        �������� �������� �� 1~k��° �������� ���� 
                        --> ���⼭ [i]�� �ʹ� ũ�� ������ ���� 
                        
 * GlobalTopK[i]      : ��� LocalTopK �鿡 ���ؼ� ���� �ִ밪���� ���� 
 */
 
template <typename T>
int BSEARCH(T arr[], int arrsize, T x)
{
	int low = 0, high = arrsize - 1;
	
	while (low <= high)	 {
		int mid = (low + high) >> 1;
		
		if (arr[mid] < x)
			low = mid + 1;
		else if (arr[mid] > x)
			high = mid - 1;
		else
			return mid;
	}
	
	return high;
}

template <typename T>
int BSEARCH_r(T arr[], int arrsize, T x)
{
	int low = arrsize-1, high = 0;
	
	while (low <= high)	 {
		int mid = (low + high) >> 1;
		
		if (arr[mid] < x)
			low = mid + 1;
		else if (arr[mid] > x)
			high = mid - 1;
		else
			return mid;
	}
	
	return low;
}

INT64 TAX()
{
	/* �ʱ�ȭ: K��° ������ ��� �ּҰ����� ä��� */ 
	for (int i = 1; i <= K; ++i) {
		LocalTopK[i] = MIN_COST;
		GlobalTopK[0][i] = MIN_COST;
	}
		
	global_top = GlobalTopK[0];
	global_tmp = GlobalTopK[1];
	
#ifdef DEBUG
		printf("inital iteration(%d) local = ", 0);
		for (int j = 1; j <= K; ++j) {
			if (LocalTopK[j] != MIN_COST)
				printf("%5d", LocalTopK[j]);
		}
		printf("\n");
#endif	
#ifdef DEBUG
		printf("initial iteration(%d) global = ", 0);
		for (int j = 1; j <= K; ++j) {
			if (global_top[j] != MIN_COST)
				printf("%5d", global_top[j]);
		}
		printf("\n");
#endif

	for (int i = 1; i <= N; ++i) {
		/* i�� ������ �Ϳ� ���ؼ� LocalTopK ���  */	
		for (int j = 1; j <= K; ++j) if (LocalTopK[j] != MIN_COST)
			LocalTopK[j] += A[i];
		
		/* A[i]�� ���Ͽ� ��ġ���� �� (K��° �����̹Ƿ� �׳� for loop) --> ũ�� Binary Search */

		int found = 1;
		for ( ; found <= K; ++found) if (LocalTopK[found] < A[i])
			break;

		int found2 = BSEARCH_r(LocalTopK + 1, K, A[i]);
		
#ifdef DEBUG
		printf("%d == BSERACH_r(LocalTopK, %lld) = %d\n", found, A[i], found2);
#endif
		if (found <= K)
		{
			LocalTopK[K] = A[i]; /* �Ǹ����� ��ſ� A[i]�� ��ü */ 
			
			/* lb ��ġ���� ��� ��ü */ 
			for (int up = K; up != found; --up) {
				swap(LocalTopK[up], LocalTopK[up-1]);
			}
		}

#ifdef DEBUG
		printf("iteration(%d) local = ", i);
		for (int j = 1; j <= K; ++j) {
			if (LocalTopK[j] != MIN_COST)
				printf("%5d", LocalTopK[j]);
		}
		printf("\n");
#endif
	
		/* LocalTopK���� GlobalTopK ���� ���� �͵��� ������ GlobalTopK�� �ݿ��� �� */
		/*
		 * Merge GlobalTopK + LocalTopK --> next GlobalTopK 
		 */
		int j = 1, k = 1, n = 1;
		
		while (n <= K && (j <= K || k <= K))  {
			if (j == K+1 || global_top[j] < LocalTopK[k])
				global_tmp[n++] = LocalTopK[k++];
			else if (k == K+1 || global_top[j] >= LocalTopK[k])
				global_tmp[n++] = global_top[j++];
		}
		
		swap(global_tmp, global_top);
#ifdef DEBUG
		printf("iteration(%d) global = ", i);
		for (int j = 1; j <= K; ++j) {
			if (global_top[j] != MIN_COST)
				printf("%5d", global_top[j]);
		}
		printf("\n");
#endif
	}

	return global_top[K];
}

int main()
{
#ifdef DEBUG
	freopen("input\\tax.txt", "r", stdin);
	freopen("output\\result.txt", "w", stdout);
#endif	

	scanf("%d %d", &N, &K);
	
	for (int i = 1; i <= N; ++i)
		scanf("%lld", A+i);
		
	INT64 result = TAX();
	
	printf("%lld\n", result);
	return 0;
}

