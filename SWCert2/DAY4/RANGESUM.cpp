/* 
 * ������: RMQ 
 --
  ù ��° �ٿ� ������ ���� N�� �־�����. (1 �� N �� 100, 000)

 �� ��° �ٿ� ������ ���� Q�� �־�����. (1 �� Q �� 200, 000)

 �� ��° �ٺ��� Q���� �ٿ� ���� ������ ������ �־�����.�� ���Ǵ� ���� ���·� �̷������.

 0 x y : x��° ���� y�� �����Ѵ�. (1 �� x �� N, -100, 000 �� y �� 100, 000)
 1 x y : x��° ������ y��° �������� ���� ���Ѵ�. (1 �� x �� y �� N)
 --
 <Ǯ��>
 �ε���Ʈ���� �����. 
 
 	- �ʱ�ȭ (�Է��� 4��)
	- �Է°����� �̿��Ͽ� ���� tree �����
	- update, search ��ɱ���
	 
 */

#define _SCL_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_N = 1000000;
typedef long long INT64;

class BIT {
	int N;
	int IdxSize;

	INT64 tree[MAX_N * 4];	/* �ִ� 4 �� */

public:
	BIT()
	{
		N = 0;
		memset(tree, 0, sizeof(tree));
	}

	void setup(int arr[], int arrsize)
	{
		N = arrsize;
		for (IdxSize = 1; IdxSize < N; IdxSize *= 2)
			;
		
		for (int i = 0; i < arrsize; ++i)
			tree[IdxSize + i] = (INT64)arr[i];

		(void) init(1);
	}

	void update(int idx, int value)
	{
		tree[IdxSize + idx] = (INT64) value;
		updateIndex((IdxSize + idx) >> 1);
	}

	INT64 query(int from, int to)
	{
		return queryInternal(from, to, 1, 0, IdxSize -1);
	}
private:
	INT64 init(int pos)
	{
		if (pos >= IdxSize) return tree[pos];
		return tree[pos] = sum(init(pos * 2), init(pos * 2 + 1));
	}

	void updateIndex(int pos)
	{
		if (pos > 0) {
			tree[pos] = sum(tree[pos * 2], tree[pos * 2 + 1]);
			updateIndex(pos >> 1);
		}
	}

	INT64 queryInternal(int left, int right, int IndexNode, int IndexLeft, int IndexRight)
	{
		if (right < IndexLeft || IndexRight < left)
			return 0ll;

		if (left <= IndexLeft && IndexRight <= right)
			return tree[IndexNode];

		int mid = (IndexLeft + IndexRight) / 2;
		return sum(queryInternal(left, right, IndexNode * 2, IndexLeft, mid), queryInternal(left, right, IndexNode * 2 + 1, mid + 1, IndexRight));
	}
	INT64 sum(INT64 a, INT64 b) { return a + b; }
};

int N, Q;

int A[MAX_N + 9];

BIT bit;

void RANGESUM(BIT& bit, int q, int a, int b)
{
	if (q == 0)
		bit.update(a-1, b);
	else if (q == 1)
	{
		printf("%lld\n", bit.query(a-1, b-1));
	}
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\rangesum.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d %d", &N, &Q);

	for (int i = 1; i <= N; ++i)
		A[i] = i;

	bit.setup(A+1, N);

	for (int i = 1; i <= Q; ++i) {
		int q, a, b;

		scanf("%d %d %d", &q, &a, &b);
		RANGESUM(bit, q, a, b);
	}
}
