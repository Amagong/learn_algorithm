/////////////////////////////////////////////////////////
// SDS SW Certificate
// Problem : �׸��� (Professional)
// Author  : SW Competency Development TF
// Copyright(c) 2016 Samsung SDS Co. ltd.
// All rights reserved. / Confidential
// �� ������ SDS ������ �ƴ� �ܺ��ο��� �����ϰų�
// �ܺ� ����Ʈ �� ���߿� �Խ��ϴ� ������ ���� ���մϴ�.
/////////////////////////////////////////////////////////
#include <cstdio>

int Answer;
int M, N;
int S[20];
int P[24][20];
int C[24];

int List[20], nList; // ���� ����� ��ȣ ����

void backtrack(int pos, int val, int cost) {
	int totalCost = cost;

	if (val == 1) {
		totalCost += S[pos];
	}

	// ��� �����ڸ� �ݿ��� ���
	if (pos == N - 1) {
		// Ŀ���ϴ� �Ǳ��� ����
		int covered = 0;

		for (int i = 0; i < M; i++) {
			C[i] = 0;
		}

		for (int i = 0; i < nList; i++) {
			for (int j = 0; j < M; j++) {
				if (P[j][List[i]] == 1 && C[j] == 0) {
					covered++;
					C[j] = 1;
				}
			}
		}

		// �Ǳ� M���� ��� Ŀ���ϰ� ������ �� ���� �ּ��̸� ������.
		if (covered == M && totalCost < Answer) {
			Answer = totalCost;
		}

		return;
	}

	if (totalCost > Answer) {
		return;
	}

	for (int i = 0; i < 2; i++) {
		if (i == 1) {
			List[nList++] = pos + 1;
		}

		backtrack(pos + 1, i, totalCost);

		if (i == 1) {
			nList--;
		}
	}
}


int Main() {

	int test_case, T;

	freopen("sample_input.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case) {
		// �������� �� N, �Ǳ��� �� M
		scanf("%d %d", &N, &M);

		// �������� ����
		for (int i = 0; i < N; i++) {
			scanf("%d", &S[i]);
		}

		// �������� �Ǳ� ���� ����
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &P[i][j]);
			}
		}

		/*
		*
		* �̰��� �������� �ڵ带 �ۼ��մϴ�.
		* �׽�Ʈ ���̽� ���� T��ŭ ������ ����� Answer�� ���� ��� �˴ϴ�.
		*
		*/
		Answer = 99999999;
		nList = 0;

		for (int i = 0; i < 2; i++) {
			if (i == 1) {
				List[nList++] = 0;
			}

			backtrack(0, i, 0);

			if (i == 1) {
				nList--;
			}
		}


		/* ��� �� ��� */
		printf("#%d %d\n", test_case, Answer);
	}

	return 0;
}

