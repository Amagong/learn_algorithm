/* 
 * LCS(Longest Common Subsequence)
 *
 --
 �ڿ� ������ ���ڰ� ������ ���ǰ� + 1, Ʋ���� ���� ���ڸ� �ϳ��� �� ���� �ٽ� LCS�� 
 --
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#define DEBUG 

const int MAX_L = 1000;

char AS[MAX_L+1];
char BS[MAX_L+1];

#define LEFT	  1
#define TOP		  2
#define DIAGONAL  3

int dp[MAX_L + 1][MAX_L+1];
int dph[MAX_L + 1][MAX_L + 1];

vector<char> LCS(char A[], int AN, char B[], int BN)
{
	/* �ʱ�ȭ */
	for (int i = 0; i <= AN; ++i)
		dp[i][0] = 0;
	for (int i = 0; i <= BN; ++i)
		dp[0][i] = 0;

	for (int i = 1; i <= AN; ++i) {
		for (int j = 1; j <= BN; ++j)
		{
			if (A[i] == B[j]) {
				/* �� ���ڰ� ����. */
				dp[i][j] = dp[i - 1][j - 1] + 1;
				dph[i][j] = DIAGONAL;
			}
			else 
			{
				/* �� ���ڰ� ���� ���� */
				int left = dp[i][j - 1];
				int top = dp[i - 1][j];

				dp[i][j] = max(left, top);
				dph[i][j] = (left > top) ? LEFT : TOP;
			}
		}
	}

#ifdef DEBUG
	for (int i = 0; i <= AN; ++i)
	{
		for (int j = 0; j <= BN; ++j)
			printf("%3d", dp[i][j]);
		printf("\n");
	}
#endif

	int idxA = AN;
	int idxB = BN;

	vector<char> result;

	while (idxA != 0 && idxB != 0)
	{
#ifdef DEBUG
		printf(" dph[%d][%d] = %d A->%c, B->%c\n", idxA, idxB, dph[idxA][idxB], A[idxA], B[idxB]);
#endif
		switch (dph[idxA][idxB]) {
			case LEFT:
				idxB--;
				break;
			case TOP:
				idxA--;
				break;
			case DIAGONAL:
				result.push_back(A[idxA]);
				idxA--;
				idxB--;
				break;
			default:
				printf("!ERROR\n");
				break;
		}
	}

	return result;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\lcs.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif

	scanf("%s\n", AS + 1); AS[0] = ' ';
	scanf("%s\n", BS + 1); BS[0] = ' ';

	vector<char> result = LCS(AS, strlen(AS)-1, BS, strlen(BS)-1);

	for (int i = result.size() - 1; i >= 0; --i)
		printf("%c", result[i]);
	printf("\n");
	return 0;
}

#if 0

A[i] = ���ڿ� A�� i ��° ����
B[j] = ���ڿ� B�� j ��° ����

D[i][j] = ���ڿ� A[1..i]�� ���ڿ� B[1..j]�� LCS ����

D[i][j] = max(D[i-1][j], D[i]][j-1], D[i-1][Dj-1]+1)
#endif
