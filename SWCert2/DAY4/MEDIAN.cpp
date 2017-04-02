/* 
 * �ڷᱸ��: Heap --> Median 
 *
--
ù ��° �ٿ� �־����� ������ ���� N�� �־�����. (1 �� N �� 99,999, N�� Ȧ��)

�� ��° �ٺ��� N���� �ٿ� ���� �� �ٿ� �ϳ��� ������ �־�����. (1 �� �־����� ���� �� 1,000,000,000)
--
 
<Ǯ��> 
 �߾Ӱ��� �����ؼ� ���� ����. priority_queue�� ����Ѵ�.
 
 2���� priority_queue�� ���
    - max heap (���� ������ ���� �ִ븦 ����) 
	- min heap (ū �����߿� ���� �ּҸ� ����)
	
 �Է� ������ �Ϳ� ���� ������ max heap�� �ְ� ��Һ񱳸� ���� re-arrange�Ѵ�. 
  
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_N = 1000000;

#if 0
template <typename T>
class heap {
	heap() : size(0) {}
	void insert(<T> a) 
	{
		tree[++size] = a;
		
		for (int pos = size; (pos / 2) > 0 && tree[pos] < tree[pos / 2]; pos /= 2)
			swap(tree[pos / 2], tree[pos]);
	}
	<T> top() { return tree[1]; }
	<T> peek()
	{
		swap(tree[1], tree[size]);
		size--;

		for (int pos = 1; (pos * 2 <= size); pos *= 2)
		{

		}
	}
private: 
	int size;
	<T> tree;
};
#endif 

int N;

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\median.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif

	priority_queue<int, vector<int>, greater<int> > left_q;
	priority_queue<int, vector<int>, less<int> > right_q;

	scanf("%d", &N);
	for (int i = 1, a; i <= N; ++i) {
		int left_qsize = left_q.size();
		int right_qsize = right_q.size();
		
		scanf("%d", &a);

		if (left_qsize == right_qsize)
			left_q.push(a);
		else
			right_q.push(a);

		if (!left_q.empty() && !right_q.empty() && left_q.top() < right_q.top())
		{
			int left_top = left_q.top();  left_q.pop();
			int right_top = right_q.top(); right_q.pop();

			right_q.push(left_top);
			left_q.push(right_top);
		}

		if (i % 2)
			printf("%d\n", left_q.top());
	}
	return 0;
}
