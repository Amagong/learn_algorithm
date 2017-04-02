/*
 * �ִ������� 1�� �Ǵ� ��
 --
 � ���� S�� �־�����. ���� S���� �� �� �̻� ���Ҹ� �������� ��, 
 ������ �� Ȥ�� ������ �ִ������� 1�� �Ǵ� ���� ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
 
 <�Է�>
 ù ��° �ٿ� ������ ũ�� N�� �־�����. (1 �� N �� 100)
 �� ��° �ٺ��� N���� �ٿ� ���� ������ �� ���� Si�� �־�����. 
 � �� ���Ұ� ���� �� �ִ�. (1 �� Si �� 100,000) 
 --
 */ 
 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N         107
#define MAX_S      100007
#define MAX_MOD  10000003

using namespace std;

typedef long long INT64;
typedef pair<int, int> BOX;

int CASE; 
int N;
int A[MAX_N];

/*
 --
 D[i][x] = 1��° ������ i��° ������ ���� �������� ��, gcd�� x�� �Ǵ� ����� ��. 
          (i��° ���� �ݵ�� ����)

 D[0][0] = 1
 D[i][gcd(x,A[i])] <- D[j][x]	(j < i)

 --
 */
int d[MAX_N][MAX_S];
vector<int> cdList[MAX_S];

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a%b);
}

int GCD()
{
	int ans = 0;
	
	memset(d, 0, sizeof(d));
	
	/*
	 * !!
	 * ������ ��� ������� ���Ѵ�. 
	 * !!
	 */ 
	for (int i = 1; i < MAX_S; ++i) {
		for (int j = 1; j*j <= i; ++j)  {
			if ((i%j) == 0) {
				/*
				 * j*j�̳� ������ �˻��ϹǷ� i/j ���� �ѹ��� �־���� �Ѵ�. (j*j != i) 
				 */
				cdList[i].push_back(j);
				if (j*j != i)
					cdList[i].push_back(i/j);
			}
		}
	}
	
#ifdef DEBUG
	printf("A = \n");
	for (int i = 1; i <= N; ++i)
		printf("%3d", A[i]);
	printf("\n");
#endif	
	/* ����� ���� ���Ѵ�. */
	for (int i = 1; i <= N; ++i)  {
		d[i][A[i]] = 1;
		
		for (int j = 1; j < i; ++j) {
			/* ���ݲ� ���� ��������� Ȱ���Ͽ� ���� 1�� �������� ������� ���Ѵ�. */ 
			for (int k = 0; k < cdList[A[j]].size(); ++k) {
				int t = cdList[A[j]][k];
				int g = gcd(t, A[i]);
				
#ifdef DEBUG
				printf(" iter(%d,%d) gcd(t=%d, Ai=%d)\n", i, j, t, A[i]);
#endif				
				d[i][g] += d[j][t];
				d[i][g] %= MAX_MOD;
			}
		}
		
		ans += d[i][1];
		ans %= MAX_MOD;
	}
	
	return ans;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\gcd.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	

	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", A + i);
		
	int result = GCD();
	printf("%d\n", result);
	return 0;
}

