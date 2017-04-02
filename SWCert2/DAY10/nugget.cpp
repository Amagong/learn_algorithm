/*
 * �ʰ�
 * 
 --
 �¾��̴� N���� �ʰ� ���ڸ� ������ �ִ�. i��° �ʰ� ���ڿ��� Ai���� �ʰ��� ����ִ�.

���� �¾��̿��� ��Ȯ�� x���� �ʰ��� �޶�� ��Ź�ϴµ�, �¾��̴� ������ �ִ� �ʰ� ���� �� 
�Ϻθ� ������ ��쿡�� �����Ѵ�.

�¾��̰� ������ �ִ� �ʰ� ���ڿ� �ִ� �ʰ� ������ ����, ��쿡�� ������ �� ���� �ʰ� ������ 
���� �� �ִ�. ���� ���, �¾��̰� ������ �ִ� �ʰ� ������ ������ 3����, �� ���ڿ� �ʰ��� 
1��, 2��, 5�� �ִٸ�, ��쿡�� 4���� �ʰ��� ������ ����� ����.

�ɼ����� ���� �¾��̸� ��Ȳ��Ű���� �Ѵ�. ��츦 ���� ������ �� ���� �ʰ� ���� �߿� 
���� ���� ���� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
 --
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N 100007

using namespace std;

typedef long long INT64;
typedef pair<int, int> PPI;

int CASE; 
int N;
INT64 A[MAX_N];
INT64 ASUM[MAX_N];
INT64 B[MAX_N];

/*
 * A[i] : ���ĵ� �Է� ���ڰ� 
 *
 * Mi   : ���ݲ� i-1��° ���ڱ��� Ȱ���Ͽ� 1..���� �����ؼ� ���� ũ�� ����� �ִ� �ִ� ���ڰ� 
 *
 * ���� ���ԵǴ� ���� A[i]�� ���ؼ� 
 *     A[i]�� ����ؼ� ����� �Ǵ� ���ο� ���ڴ� (A[i] + 1..Mi) �̰� ���⼭ �ּҰ��� A[i] + 1 
 *     A[i]�� ������� �ʰ� ����� �ִ� ���� ������ �ռ� ���� (1..Mi)
 *
 *     --> �ᱹ�� ���Ӱ� ǥ���� �� �ִ� ���� ������ (1 .. Mi) , (A[i]+1 .. A[i]+Mi)
 *     --> Mi+1 != A[i]+1 �� �ƴ϶��  (Mi+1 ~ A[i]-1) ������ ���� ǥ���� �� ����.
 * 
 */
INT64 NUGGET()
{
	INT64 Mi = 0ll; 
	
	for (int i = 1; i <= N; ++i) {
		if (A[i] > Mi+1) 
			break;
		Mi = Mi + A[i];
	}
	
	return Mi + 1;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\nugget.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	

	scanf("%d", &N);
	
	for (int i = 1; i <= N; ++i)
		scanf("%lld", A+i);
		
	sort(A+1, A+1+N);
	
#ifdef DEBUG
	printf(" A = ");
	for (int i = 1; i <= N; ++i) 
		printf("%3d", A[i]);
	printf("\n");
#endif	
	INT64 result = NUGGET();
	
	printf("%lld\n", result);
	return 0;
}

