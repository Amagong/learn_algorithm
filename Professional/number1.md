## 숫자판놀이

- N x M 크기의 숫자판에 정수가 적혀 있음.
- 맨 위에 있는 열에서 맨 아래의 열까지 지날 때 적힌 수의 합을 최대로 지나는 프로그램

| 1 | 6 | 5 | 2 | 10 |
| - | - | - | - | - |
| 4 | 1 | 4 | -8 | -9 |
| -7 | 2 | -9 | 3 | 5 |
| 3 | -6 | 1 | -12 | -2 |
| 9 | 8 | -2 | 5 | 5 |


-->

if (i == 1)
  dp(i,j+1) = max { dp(i-1,j), dp(i,j), dp(i+1,j) } + valueOf (i, j+1)
else
  dp(i,j+1) = max { dp(i-1,j), dp(i,j), dp(i+1,j) } + valueOf (i, j+1)
