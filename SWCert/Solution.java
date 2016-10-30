/////////////////////////////////////////////////////////
// SDS SW Certificate
// Problem : �׸��� (Professional)
// Author  : SW Competency Development TF
// Copyright(c) 2016 Samsung SDS Co. ltd.
// All rights reserved. / Confidential
// �� ������ SDS ������ �ƴ� �ܺ��ο��� �����ϰų�
// �ܺ� ����Ʈ �� ���߿� �Խ��ϴ� ������ ���� ���մϴ�.
/////////////////////////////////////////////////////////

import java.io.FileInputStream;
import java.util.LinkedList;
import java.util.Scanner;

public class Solution {
	static int Answer;
	static int M, N;
	
	// �������� ����
	static int[] S = new int[20];
	
	// �������� �Ǳ� ���� ����
	static int[][] P = new int[24][20];
	
	// �Ǳ⺰ ���ְ����� �����ڰ� �ִ��� ����
	static int[] C = new int[24];
	
	// �ַ�� ���� ����Ʈ
	static LinkedList<Integer> list = new LinkedList<Integer>();
	
	
	public static void main(String[] args) throws Exception {
		
		/*
		 * �Ʒ��� �޼ҵ� ȣ���� ������ ǥ�� �Է�(Ű����) ��� input.txt ���Ϸκ��� �о���ڴٴ� �ǹ��� �ڵ��Դϴ�. ��������
		 * �ۼ��� �ڵ带 �׽�Ʈ �� ��, ���Ǹ� ���ؼ� input.txt�� �Է��� ������ ��, �� �ڵ带 ���α׷��� ó�� �κп�
		 * �߰��ϸ� ���� �Է��� ������ �� ǥ�� �Է� ��� ���Ϸκ��� �Է��� �޾ƿ� �� �ֽ��ϴ�. ���� �׽�Ʈ�� ������ ������ �Ʒ�
		 * �ּ��� ����� �� �޼ҵ带 ����ϼŵ� �����ϴ�. ��, ä���� ���� �ڵ带 �����Ͻ� ������ �ݵ�� �� �޼ҵ带 ����ų� �ּ�
		 * ó�� �ϼž� �մϴ�.
		 */
		System.setIn(new FileInputStream("sample_input.txt"));

		/*
		 * ǥ���Է� System.in ���κ��� ��ĳ�ʸ� ����� �����͸� �о�ɴϴ�.
		 */
		Scanner sc = new Scanner(System.in);

		/*
		 * �׽�Ʈ ���̽��� ���� �Է� �޽��ϴ�.
		 */
		int T = sc.nextInt();
		
		/*
		 * T ���� �׽�Ʈ ���̽��� �־����Ƿ�, ������ ó���մϴ�.
		 */
		for(int test_case = 1; test_case <= T; ++test_case) {
			// �������� ��
			N = sc.nextInt();
			
			// �Ǳ��� ��
			M = sc.nextInt();
			
			// �������� ����
			for(int i = 0; i < N; i++) {
				S[i] = sc.nextInt();
			}
			
			// �������� �Ǳ� ���� ����
			for(int i = 0; i < M; i++) {
				for(int j = 0; j < N; j++) {
					P[i][j] = sc.nextInt();
				}
			}
			
			/*
			* 
			* �̰��� �������� �ڵ带 �ۼ��մϴ�.
			* �׽�Ʈ ���̽� ���� T��ŭ ������ ����� Answer�� ���� ��� �˴ϴ�.
			* 
			*/
			Answer = Integer.MAX_VALUE;
			list.clear();
			
			for(int i = 0; i < 2; i++) {
				if(i == 1) {
					list.add(0);
				}
				
				backtrack(0, i, 0);
				
				if(i == 1) {
					list.removeLast();
				}
			}
			
			
			/* ��� �� ��� */
			System.out.println("#" + test_case + " " + Answer);
		}
	}
	
	// pos : ������ ��ȣ, val : ä�뿩��, cost : ������� ���� �ڽ�Ʈ
	public static void backtrack(int pos, int val, int cost) {
		int totalCost = cost;
		
		if(val == 1) {
			totalCost += S[pos];
		}
		
		if(pos == N - 1) {
			int covered = 0;
			
			for(int i = 0; i < M; i++) {
				C[i] = 0;
			}
			
			// ��� �Ǳ⿡ ���ؼ� ������ �����ڰ� �� �� �̻������� �Ǵ�
			// ����Ʈ�� ������� ����� ������ ������ ������
			for(int i : list) {
				
				for(int j = 0; j < M; j++) {
					// i �����ڰ� j �Ǳ⸦ ������ �� �ִ� ���
					if(P[j][i] == 1 && C[j] == 0) {
						covered ++;
						C[j] = 1;
					}
				}
			}
			
			// ��� �Ǳ⿡ ���� ������ �����ڰ� �� �� �̻��̰�
			// ���� ����� ������� ã�Ƴ� �غ��� ���� ��� ����
			if(covered == M && totalCost < Answer) {
				Answer = totalCost;
			}
			
			return;
		}
		
		// ���� ����� ������� ã�� �����غ��� Ŭ ��� �� �̻� ������ ���� Ž������ �ʾƵ� �ȴ�. 
		if(totalCost > Answer) {
			return;
		}
		
		// ä��/ä�� ���� ���� �� ������ ��찡 �ִ�.
		for(int i = 0; i < 2; i++) {
			// ä���� ��� ������ ��ȣ�� ����Ʈ�� ����
			if(i == 1) {
				list.add(pos + 1);
			}
			
			// ���� �����ڷ� ���ȣ��
			backtrack(pos + 1, i, totalCost);
			
			// �տ��� ����� ������ ��ȣ�� ����Ʈ���� ����
			if(i == 1) {
				list.removeLast();
			}
		}
	}
}
