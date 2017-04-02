/* 
 * ������׷����� ���� ū ���簢��
 * 
 * �ڷᱸ��: ������׷� 
 --
�Է��� ���� ���� �׽�Ʈ���̽��� �̷���� �ִ�. �� �׽�Ʈ���̽��� ù ������ ���簢���� ��N�� �ǹ��Ѵ�
( 1 �� N �� 100 , 000 ) (1��N��100,000). ���� N = 0 N=0�̸� �Է��� ���� �ǹ��Ѵ�.
���� �ٿ� N���� ������ ������ ���̿� �ΰ� �־�����. �̴� ������� ���簢��
N���� ���̸� ��Ÿ����. �־����� ���̴�1,000,000,000 ���� ũ�� �ʴ�.
 --
 <Ǯ��>
  
D[i]�� ������ �ִ� �簢������ ���̸� ����Ѵ�.
D[i]�� �տ� �ڱ⺸�� ���� �ּ� �簢�������� ����� �� �� �ִ� ��.
  �̸� ���� stack�� remaining_top�� �����Ѵ�. 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <functional>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_N = 100000;
const int MAX_H = 1000000000;
typedef long long INT64;

int N;

INT64 A[MAX_N + 9];

INT64 HISTOGRAM()
{
	INT64 ret = 0;

	stack<pair<INT64, INT64> > st;

	st.push(pair<INT64, INT64>(0, 0));

	for (int i = 1; i <= N; ++i) {
		while (!st.empty()) {
			pair<INT64, INT64>& top = st.top();

			if (A[i] <= top.second) {
				st.pop();
			}
			else 
			{
				ret = max(ret, A[i] * (i - top.first));
				st.push(pair<INT64, INT64>((INT64) i-1, A[i]));
				break;
			}
		}
	}
	return ret;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\histogram.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	for (;;)
	{
		scanf("%d", &N);

		if (N == 0)
			break;

		for (int i = 1; i <= N; ++i)
		{
			scanf("%lld", A + i);
		}

		INT64 result = HISTOGRAM();

		printf("%lld\n", result);

	}
	

}

