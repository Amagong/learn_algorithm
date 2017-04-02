/* 
 * �����̵� ������ 
 * 
 --
 ù �ٿ� �迭�� ũ�� N�� �κй迭�� ũ�� K�� �־�����. (1 �� K �� N �� 1,000,000)

 ��° �ٿ� �迭�� ������ ��Ÿ���� N���� �������� �������� ���еǾ� �־�����. 
 �־����� ���� ���밪�� 1,000,000,000 ���� ũ�� �ʴ�.
 --
 
 ���̰� N�� �κй迭�� ���� (�ִ�, �ּ�, ��)�� ����. 
 (ex. ���̰� ���Ƿ� �־����� Query�� �־����� Indexed Tree����ؾ� ��.)
 
 �ִ�/�ּҽ� out-of-range�� �͵��� ���� üũ�ϱ� ���� �˰��� �ʿ�. 
 
 �ִ�/�ּҸ� ���ϱ� ���ؼ��� deqeue�� ����Ѵ�.
 	������ �ֱ�: push_front, push_back
 	�յڿ��� ����: pop_front, pop_front
 	�� ����: front, back
  
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_N = 1000000;

int N, K;
int A[MAX_N + 9];

deque<pair<int, int> > minq;
deque<pair<int, int> > maxq;

struct RESULT {
	int mi, ma, sum;
} RESULTS[MAX_N + 9];

void SSUM(int idx, int value)
{
	if (idx <= K)
	{
		RESULTS[1].sum += value;
	}
	else
	{
		RESULTS[1 + idx - K].sum = RESULTS[idx - K].sum + value - A[idx - K];
	}
}

void SMIN(int idx, int value)
{
	if (!minq.empty())
	{
		pair<int, int> front = minq.front();

		if (front.first <= (idx - K))
			minq.pop_front();

		while (!minq.empty()) {
			pair<int, int> back = minq.back();

			if (value < back.second)
				minq.pop_back();
			else
				break;
		}
	}

	minq.push_back(pair<int, int>(idx, value));
	
	pair<int, int> current_front = minq.front();

	if (idx <= K)
	{
		RESULTS[1].mi = current_front.second;
	}
	else
	{
		RESULTS[1 + idx - K].mi = current_front.second;
	}
}

void SMAX(int idx, int value)
{
	if (!maxq.empty())
	{
		pair<int, int> front = maxq.front();

		if (front.first <= (idx - K))
			maxq.pop_front();

		while (!maxq.empty()) {
			pair<int, int> back = maxq.back();

			if (value > back.second)
				maxq.pop_back();
			else
				break;
		}
	}

	maxq.push_back(pair<int, int>(idx, value));

	pair<int, int> current_front = maxq.front();

	if (idx <= K)
	{
		RESULTS[1].ma = current_front.second;
	}
	else
	{
		RESULTS[1 + idx - K].ma = current_front.second;
	}
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\slidingwindow.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d %d", &N, &K);

	for (int i = 1; i <= N; i++) {
		scanf("%d", A + i);

		SSUM(i, A[i]);
		SMIN(i, A[i]);
		SMAX(i, A[i]);
	}

	for (int i = 1; i <= N - K + 1; ++i) {
		printf("%d %d %d\n", RESULTS[i].mi, RESULTS[i].ma, RESULTS[i].sum);
	}

	return 0;
}
