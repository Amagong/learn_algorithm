## 08 : 동적계획법 (dynamic programming)

### 8.1 도입
    - 고안자: Richard E. Bellman
    - 최적화 문제를 연구하는 수학 이론에서 나왔지만, 프로그래밍하고는 관련 없음
    - 중복되는 부분 문제를 해결하는 것
        -> 두번 이상 계산되는 부분문제를 overlapping subproblem이라고 부름
        -> 이러한 문제를 cache에 저장하여 중복계산을 회피

    - 메모이제이션 구조
        int cache[30][30];
        int bino(int n, int r) {
            if (r == 0 || n == r) return 1;
            int& ref = cache[n][r];

            if (ref != -1) return ref;
            return ref = bino(n-1, r-1) * bino(n-1, r);
        }

    - 메모이제이션의 시간복잡도 [TODO]
        -> (존재하는 부분문제수) * (한 부분문제를 풀때 필요한 반목분 수행 회수)
        -> cache 개수를 고려할 때 O(1) * O(n^2)

    - 메모이제이션
        -> subproblem에 대해 어떻게 적용하느냐가 관건
            : 재귀호출의 input parameter 개수가 자연수이면 심플
            : sequence면 이에 해당하는 대표값으로 변환

### 8.2 와일드카드 문제 [TODO]

### 8.4 전통적 최적화 문제들
    - 이론적 배경: 최적 부분 구조 (optimal substructure)가 존재함
        -> 각 부분 문제의 최적해만 있으면 전체 최적해를 구할 수 있는 경우
        -> ! 더 작은 문제의 최적해만으로는 전체 최적해를 구할 수 없는 경우 -> DP로 풀수 없다

    - LIS(최대 증가 부분 수열: Longest Increasing Sub-sequence)
        -> A[-1]에 가상으로 -INF룰 넣고 나서 전체 LIS 구함
        -> 지금까지의 Increasing sequence + 나머지 부분의 Increasing sequence구함
           * 나머지 부분의 경우 현재 순열의 최대값보다 큰 index로 찾아 그 나머지 부분의 LIS 구함
           * 전체 해는 현재 순열 + 부분문제의 LIS
        -> 메모이제이션 대상 선정
            * 입력 값들(S[])이 정해져 있으므로 [index, 마지막)으로 정의하여 cache[index]로 설정
            * LIS(start) : S[start]에서 시작하는 최대 증가 부분수열의 길이값

    - LIS를 O(nlogn)에 찾는 방법 [TODO]

    - 최적화 문제 동적계획법 레시피

        1. 모든 답을 만들어 보고 최적해의 점수를 반환하는 완전탐색알고리즘을 설계
        2. 전체 답이 아니라, 앞으로 남은 선택들에 해당하는 점수를 반환하는 부분문제 정의
        3. 재귀호출의 입력에 이전의 선택에 관련가 정보가 있으면 필요한 것만 남기고 줄인다.
           가능한 중복되는 문제를 많이 만든다... <-- 줄여야 하니까.
        4. 입력이 배열/문자열이면 적절한 변환을 통해 메모이제이션할 수 있도록 한다.
        5. 메모이제이션을 적용한다.
