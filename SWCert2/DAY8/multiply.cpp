/*
 * �ŵ����� ���ϱ� 
 *
 --
 ���� a�� m�� �־� ������, a�� m �ŵ�����(am)�� 1,000,000,007 �� ���� �������� ����ϴ� �����̴�.
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
typedef pair<int, int> BOX;

#define MAX_N 509

int CASE; 
INT64 A, N;

/*
 * ���ҽ� Overlapping subproblem�� ���� ����� ���ؼ�
 * ¦���� �����ϰ� Ȧ���� �ѹ� �� ���Ѵ�. 
 */
INT64 MULTI(INT64 a, INT64 n)
{
	if (n == 0)
		return 1ll;
	if (n == 1)
		return a;
	
	INT64 result = MULTI(a, n/2);
	
	result = ( result * result ) % 1000000007ll;
	
	if (n%2) {
		result = a * result %  1000000007ll;
	}
	return result;
}

INT64 MULTI2(INT64 a, INT64 n)
{
	INT64 result;
	
	for (; n; n >> 1) {
		if (n & 0x1) {
			result *= a;
			result %= 1000000007ll;
		}
		a = ( a * a ) % 1000000007ll;
	}

	return result;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\multiply.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	

	scanf("%lld %lld", &A, &N);
	INT64 result = MULTI2(A, N);
	
	printf("%lld\n", result);
	return 0;
}

