/*
 * ���� ��ġ 
 * 
 --
 ������ ��鿡�� �� N���� �̷���� �ٰ����� �־�����.
 �׸��� ������� �� P1, P2�� �־������� �� P1, P2�� �ٰ����� �ܺο� �ִ���, 
 ���ο� �ִ��� �Ǻ��ϴ� ���α׷��� �ۼ��Ͻÿ�.

 �� P1, P2 �� �־��� �ٰ����� ���� ���� ���������� �ʴ´�.
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

struct POINT {
	INT64 x, y;
	
	POINT() { }
	POINT(INT64 a, INT64 b) : x(a), y(b) { }

	bool operator==(const POINT& other) {
		return (x == other.x && y == other.y);	
	}
	
	INT64 norm2() const {
		return x*x + y*y;
	}
	
	INT64 DP(const POINT& b) const {
		return (x * b.x + y * b.y);
	}	

	INT64 CP(const POINT& b) const {
		return (x * b.y - b.x * y);
	}	
	
	int CCW(const POINT& other) const {
		INT64 value = CP(other);
		
		if (value > 0ll)
			return 1;
		else if (value < 0ll)
			return -1;
		else
			return 0;
	}
};

int CCW(POINT a, POINT b, POINT c) {
	POINT ab(b.x - a.x, b.y - a.y);
	POINT ac(c.x - a.x, c.y - a.y);
	
	return ab.CCW(ac);	
}

int CASE; 
int N;
POINT points[MAX_N];

bool between(INT64 a, INT64 b, INT64 c)
{
	if (a > b) swap(a, b);
	return (a <= c && c <= b);
}

/*
 * a, b, c �� ���� �� ������ �ִ�.  
 */
bool on_the_line(const POINT& a, const POINT& b, const POINT& c)
{
	/* ������ ������ ��� */
	if (CCW(a, b, c) == 0) {
		int ccw1 = c.CCW(a);
		int ccw2 = c.CCW(b);

		/* c���� ���� a, b ������ CCW�� ���� ������ �� */ 
		return (ccw1 * ccw2 < 0);
	}
	return false;
}

/*
 * a,b ���ΰ� c,d������ �����Ѵ�. 
 *
 * 1) a, b ���ο� ���� c, d �� ��� �ٸ� ����(������ CCW�̸� �ٸ� ������ CW)
 * 2) c, d ���ο� ���� a, b ���� ��� �ٸ� ���� 
 *
 * �� ������ �����ϸ� �����ϰų� �����ϴ� ��츦 �����ϰ�� ��� �����Ѵ�. 
 */
bool intersect_TowLines(const POINT&a, const POINT& b, const POINT& c, const POINT& d)
{
	int ccw_ab = CCW(a, b, c) * CCW(a, b, d);
	int ccw_cd = CCW(c, d, a) * CCW(c, d, b);
	
	if (ccw_ab == 0 && ccw_cd == 0) {
		/* ab ���ΰ� cd ������ ������ */
		return false; 
	}
	return (ccw_ab <= 0 && ccw_cd <= 0);
}

int InOrOut(POINT t)
{
#ifdef DEBUG
	printf(" -- Input t = (%lld, %lld)\n", t.x, t.y);
#endif

	/* virtually add first on to Last position */
	points[N+1].x = points[1].x, points[N+1].y = points[1].y;
	
	/* ������ ���� ( 1000000007ll, t.y + 1 )�� �ϸ� 
	   1) � ������ ��ġ���� �ʴ´�. 
	   2) � ���а��� ��ġ���� �ʴ´�.
	*/ 
	POINT MaxT(1000000007ll, t.y + 1);
	int cross_points = 0;
	
	for (int i = 1; i < N; ++i) {
#ifdef DEBUG
			printf(" !! Tested with points i = (%lld, %lld) j = (%lld, %lld)\n", points[i].x, points[i].y, points[i+1].x, points[i+1].y);
#endif			
		
		/* ���� ��ġ�ϴ�  ��� */
		if (points[i] == t || points[i+1] == t) {
#ifdef DEBUG
			printf(" !! Matched with points i = (%lld, %lld) j = (%lld, %lld)\n", points[i].x, points[i].y, points[i+1].x, points[i+1].y);
#endif			
			return 1;
		}
		
		/* 
		 * ��(t)�� ����(points[i],points[i+1])���� �ִ� ��� 
		 * 
		 * 1. ���δٸ� �� 3���� �̷���� 2���� ������ �����ϴٸ� ������ �߰��� ����.
		 * 2. ��(t)�� �������� ���� points[i], points[i+1]�� CCW�� ���ߴµ� ������ �ݴ��̸� t�� �߰��� �ִ�. 
		 */

		if (on_the_line(points[i], points[i+1], t)) {
#ifdef DEBUG
			printf(" !! Matched On The Line i = (%lld, %lld) j = (%lld, %lld)\n", points[i].x, points[i].y, points[i+1].x, points[i+1].y);
#endif						
			return 1;
		}
				 
		/* ��(t)���� ���� �ִ밪������ ����(T)�� ���� ���� y���� ������ ���̰��� �ִ� ��쿡 ���� üũ */ 
		if (between(points[i].y, points[i+1].y, t.y)) 
		{
			bool pti = on_the_line(t, MaxT, points[i]);
			bool ptj = on_the_line(t, MaxT, points[i+1]);
			
			/* ����(T)��    ������ ��� ������ ��� : ���������� ī��Ʈ���� ����. */
			if (pti && ptj) 
				continue;		
			
			/* ����(T)��    ������ ������ ��� : ���������� ī��Ʈ���� ����. */	
			if (pti || ptj)
				continue;
			
			/* ����(T)��    ���� �����ϴ� ��� */
			if (intersect_TowLines(t, MaxT, points[i], points[i+1])) {				
#ifdef DEBUG
				printf(" !! Check Intersec Line 1 (%lld, %lld, %lld, %lld) Test = (%lld, %lld, %lld, %lld)\n", points[i].x, points[i].y, points[i+1].x, points[i+1].y, t.x, t.y, MaxT.x, MaxT.y);
#endif
				cross_points ++;	
			}
			
			/* ����(T)��    ���� �������� �ʴ� ��� */ 
		}
	}
	
	/* �������� Ȧ���̸� �ȿ� ���� */ 
	return (cross_points % 2);
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\inner.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	

	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		POINT& v = points[i];
		scanf("%lld %lld", &v.x, &v.y);
	}
	
	for (int i = 1; i <= 2; ++i) {
		POINT test;
		scanf("%lld %lld", &test.x, &test.y);
		
		int result = InOrOut(test);
		printf("%s\n", result ? "in" : "out");		
	}
	
	return 0;
}

