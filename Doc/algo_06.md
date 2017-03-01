## 06 : 무식하게 풀기

### 6.1 도입
    - 완전탐색 (exhausitive search)
        -> 입력값에 따라 완전탐색에 의한 간결한 코드가 훨씬 좋을 때가 있다.

### 6.2 재귀호출과 완전탐색
    - 재귀 호출는 완전탐색을 구현할 때 매우 유용한 도구
        -> 왠만한 반복문으로 재귀호출을 대체할 수는 없다. (생각하지 못하는 가지수가 너무 많다.)
    - 방법
        1) 문제의 분할
        2) 기저 사례 선택
        3) 나머지 부분은 분할하여 재귀호출
    - 문제점
        * 시간 복잡도가 매우 높다.
        * 시간 복잡도를 줄이기 위해 재계산을 회피하는 방법 --> 동적계획법

    - 완전탐색의 주의점
        * problem - subproblem
            -> subproblem: A라는 케이스를 고려한 것과 나머지 (A를 고려하지 않은 ) 케이스

        * 중복 Count를 유의한다. 이미, 고려한 것을 다시 고려하여 답이 중복카운트 되는 것을 주의해야 함
            -> 입력값을 정규화 또는 순위화 하여 중복 고려사례가 일어나지 않도록 한다.
            -> 고려하는 입력값에 순서를 매겨 방지

        * 피전홀
            -> 경우의 수가 특정개수를 넘어가는 경우에는 반드시 이전에 고려한 subproblem이 있다.
            -> 시계 스위치가 trigger시켜도 3시간씩 바뀐다면 4번 이후는 할 필요가 없다.

### 6.7 최적화 문제 [TODO]