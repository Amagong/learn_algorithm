/* 
 * ž 
 *    ����: Ÿ���� ������ 
--
ù ��° �ٿ� ž�� �� N�� �־�����. (1 �� N �� 500,000)

�� ��° �ٿ� N���� ž���� ���̰� ������ ���� ������� �ϳ��� ��ĭ�� ���̿� �ΰ� ���� �־�����. 
(1 �� ž�� ���� �� 100,000,000)
--

 ������ �̿��Ͽ� (�����) �ʿ䰡 ������ �͵��� ���ÿ��� �����ϸ鼭 Ȯ��
  
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_N = 500000;
const int MAX_H = 10000000;

int N;
int A[MAX_H+9];
int B[MAX_H + 9];

void TOWER()
{
	stack< pair<int, int> > st;

	for (int i = 1; i <= N; ++i) {
		while (! st.empty())
		{
			pair<int, int> top = st.top();

			if (top.first >= A[i]) {
				B[i] = top.second;
				st.push(pair<int, int>(A[i], i));
				break;
			}
			else {
				st.pop();
			}
		}

		if (st.empty()) {
			st.push(pair<int, int>(A[i], i));
			B[i] = 0;
		}
	}
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\tower.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d", &N);

	for (int i = 1; i <= N; i++) {
		scanf("%d", A + i);
	}

	memset(B, 0, sizeof(B));

	TOWER();

	for (int i = 1; i <= N; ++i)
		printf("%d ", B[i]);
	printf("\n");
}
