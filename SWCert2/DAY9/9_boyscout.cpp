/*
 * ���̽�ī��Ʈ
 *
 --
�� �ױ۷����� ���� ��ī��Ʈ ��ü�� �ų� ��ī��Ʈ �ø����� �����Ѵ�. 
�� ��ī��Ʈ ������ �ӹ��� �����ϰ� �Ϸ� ������ ���� ���ڸ� ������. 
��ȸ�� ������ ������ ��� ���ڸ� ���� ��� ��Ÿ�� ġ�� ��ī��Ʈ �뷡�� �θ���.

���ش� Maine�� �ִ� �Ƹ��ٿ� ������ �ø����� �����ߴ�. �̹��� �� ������ �־��� 
�ӹ��� �ſ� ��ƴ�. �� ���� �� �ȿ� �ִ� ���� �ϳ��� ���ؼ� ���������� ��´�. 
�׸��� �ٸ� ������ ���ؼ� �����ϰ�, ���� ������ �����ϸ� �� �ٸ� ������ ���ؼ� �����Ѵ�. 
���� ���� ������� ���� ���̸� �̵��� �� ���� ���� ������ ������ ��ģ ���� �¸��ϰ� �ȴ�. 
��, ���� ������ �̵��� ���� �ݽð� �������� ���ƾ߸� �Ѵ�. ��, ������ �������� ���� 
���� ������ ���� ���ؼ��� �������� 180�� �̸����� ȸ���� �� �ִٴ� ���̴�. ����, �� ���� 
�������� ó�� ������ ���ƿ;� �ϴµ�, �� �� �ڽ��� �ι�°�� �鷶�� ������ ������ �������� 
180�� �̸����� ȸ���ؼ� �� �� �־�� �Ѵ�. �߰��� ������ ��θ� �׷��� �� �ܼ� �ٰ����� 
�����ؾ� �Ѵ�.

��ī��Ʈ ������ �ø��ȿ� ��Ʈ���� ������ �ʾұ� ������ �¸��ϱ� ���ؼ� � ��η� 
���� �¸��� �� �ִ� �� ����� �� ����. �׷��� ��ſ��� �¸��ϱ� ���ؼ� �̵��� �� �ִ� 
�ִ� ���� ������ ���ش޶�� ��û�ߴ�.

Maine�� �Ƹ��ٿ� ���� �ִ� ���� ���� N�� �� ������ ��ġ�� 2���� ��ǥ�� �־����� ��, 
�׻� �������� ȸ���ϸ� �̵��� �� ���� �� �ִ� ���� ������ �ִ밪�� ���Ͽ���.

<�Է�>
 ù ��° �ٿ��� ������ ���� N(3��N��100)�� �־�����. ���� 
 N���� �ٿ� ���ļ� �� ������ ��ǥ x,y(?106��x,y��106)�� �־�����. 
 �� ��ǥ�� �Ҽ��� ���� �ִ� 2�ڸ����� �־�����. ��� �� ������ �� ���� ���� �������� ������ ����ȴ�.

<��Ʈ>
 N�� �۴�. O(N^3) ���� �˰����� ������ �ȴ�. (DP)
 DP�� ����ϵ�, ���������� CCW �������θ� �� ���� ��(����)���� �����ؾ� �Ѵ�.
  
 --
 */ 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N 107

using namespace std;

typedef long long INT64;

struct POINT {
	INT64 x, y;
	
	POINT() { }
	POINT(INT64 a, INT64 b) : x(a), y(b) { }

	INT64 norm2() const {
		return x*x + y*y;
	}
	
	INT64 DP(const POINT& b) const {
		return (x * b.x + y * b.y);
	}	

	INT64 CP(const POINT& b) const {
		return (x * b.y - b.x * y);
	}	
};

int CCW(POINT a, POINT b, POINT c) {
	POINT ab(b.x - a.x, b.y - a.y);
	POINT ac(c.x - a.x, c.y - a.y);
	
	INT64 value = ab.CP(ac);
	
	if (value > 0ll)
		return 1;
	else if (value < 0ll)
		return -1;
	else
		return 0;
}

int CASE; 
int N;

POINT A[MAX_N];

bool cmp_Theta(const POINT& lhs, const POINT& rhs) {
	int ccw = CCW(A[1], lhs, rhs);
	
	if (ccw > 0) return true;
	if (ccw == 0) {
		POINT l(lhs.x - A[1].x, lhs.y - A[1].y);
		POINT r(rhs.x - A[1].x, rhs.y - A[1].y);
		
		return (l.norm2() < r.norm2());
	}

	return false;
}

void MAKE_CCW()
{
	sort(A + 2, A + N + 1, cmp_Theta);
	
#ifdef DEBUG	
#define PI 3.141592

	for (int i = 1; i <= N; ++i) {
		POINT p(A[i].x - A[1].x, A[i].y - A[1].y);
		
		printf(" (%lld, %lld) - (%lld, %lld) : ", A[1].x, A[1].y, A[i].x, A[i].y);
		printf(" (%3lld, %3lld) = %.5f\n", p.x, p.y, atan2((double)p.y, (double)p.x) * 180/PI);
	}
	printf("\n");
#endif
}

/*
 * D[i][j] : ���������� �����Ͽ� i�� ��带 ��� j�� ������ �� ������ ������ �ִ� ����
 * 
 */
int D[MAX_N][MAX_N];

int BOYSCOUT()
{
	MAKE_CCW();
		
	memset(D, 0, sizeof(D));

    for (int i = 2; i <= N; ++i) 
		D[1][i] = 2;
    
    for (int i = 1; i < N; ++i) 
		for (int j = i+1; j <= N; ++j) 
			if (D[i][j] > 0) {  
		        for (int k = j+1; k <= N; ++k) {
				 	if (CCW(A[i],A[j],A[k]) >= 0)
        		    	D[j][k] = max(D[j][k], D[i][j]+1);		        	
				}
    		}	
    		
    int result = 0;
    for (int i = 2; i < N; ++i) 
		for (int j = i+1; j <= N; ++j) 
			if (CCW(A[i], A[j], A[1]) >= 0)
        		result = max(result, D[i][j]);
        		
    return result;	
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\boyscout.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	

	scanf("%d", &N);

	int idx = 1;	
	for (int i = 1; i <= N; ++i) {
		double a, b;
		POINT& p = A[i];
		
		scanf("%lf %lf", &a, &b);
		p.x = (INT64) (a * 100);
		p.y = (INT64) (b * 100);
		
		if (p.y < A[idx].y) {
			idx = i;
		} else if (p.y == A[idx].y && p.x > A[idx].x) {
			idx = i;
		}
	}

	if (idx != 1)
		swap(A[idx], A[1]);

#ifdef DEBUG
	printf(" Base Point Set to A[1] = (%lld, %lld)\n", A[1].x, A[1].y);
#endif

	int result = BOYSCOUT();
	printf("%d\n", result);
	return 0;
}

