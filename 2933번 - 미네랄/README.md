# 2933번: 미네랄 - <img src="https://static.solved.ac/tier_small/15.svg" style="height:20px" /> Gold I

<!-- performance -->
### 성능 요약
메모리: 2184 KB, 시간: 48 ms
<!-- end -->

## 문제

[문제 링크](https://boj.kr/2933)

<p>창영과 상근은 한 동굴을 놓고 소유권을 주장하고 있다. 두 사람은 막대기를 서로에게 던지는 방법을 이용해 누구의 소유인지를 결정하기로 했다. 싸움은 동굴에서 벌어진다. 동굴에는 미네랄이 저장되어 있으며, 던진 막대기가 미네랄을 파괴할 수도 있다.</p>

<p>동굴은 R행 C열로 나타낼 수 있으며, R×C칸으로 이루어져 있다. 각 칸은 비어있거나 미네랄을 포함하고 있으며, 네 방향 중 하나로 인접한 미네랄이 포함된 두 칸은 같은 클러스터이다.</p>

<p>창영은 동굴의 왼쪽에 서있고, 상근은 오른쪽에 서있다. 두 사람은 턴을 번갈아가며 막대기를 던진다. 막대를 던지기 전에 던질 높이를 정해야 한다. 막대는 땅과 수평을 이루며 날아간다.</p>

<p>막대가 날아가다가 미네랄을 만나면, 그 칸에 있는 미네랄은 모두 파괴되고 막대는 그 자리에서 이동을 멈춘다.</p>

<p>미네랄이 파괴된 이후에 남은 클러스터가 분리될 수도 있다. 새롭게 생성된 클러스터가 떠 있는 경우에는 중력에 의해서 바닥으로 떨어지게 된다. 떨어지는 동안 클러스터의 모양은 변하지 않는다. 클러스터는 다른 클러스터나 땅을 만나기 전까지 게속해서 떨어진다. 클러스터는 다른 클러스터 위에 떨어질 수 있고, 그 이후에는 합쳐지게 된다.</p>

<p>동굴에 있는 미네랄의 모양과 두 사람이 던진 막대의 높이가 주어진다. 모든 막대를 던지고 난 이후에 미네랄 모양을 구하는 프로그램을 작성하시오.</p>

## 입력

<p>첫째 줄에 동굴의 크기 R과 C가 주어진다. (1 ≤ R,C ≤ 100)</p>

<p>다음 R개 줄에는 C개의 문자가 주어지며, '.'는 빈 칸, 'x'는 미네랄을 나타낸다.</p>

<p>다음 줄에는 막대를 던진 횟수 N이 주어진다. (1 ≤ N ≤ 100)</p>

<p>마지막 줄에는 막대를 던진 높이가 주어지며, 공백으로 구분되어져 있다. 모든 높이는 1과 R사이이며, 높이 1은 행렬의 가장 바닥, R은 가장 위를 의미한다. 첫 번째 막대는 왼쪽에서 오른쪽으로 던졌으며, 두 번째는 오른쪽에서 왼쪽으로, 이와 같은 식으로 번갈아가며 던진다.</p>

<p>공중에 떠 있는 미네랄 클러스터는 없으며, 두 개 또는 그 이상의 클러스터가 동시에 떨어지는 경우도 없다. 클러스터가 떨어질 때,&nbsp;그 클러스터 각 열의 맨 아래 부분 중 하나가 바닥 또는 미네랄 위로 떨어지는 입력만 주어진다.</p>

## 출력

<p>입력 형식과 같은 형식으로 미네랄 모양을 출력한다.</p>

## 소스코드

[소스코드 보기](미네랄.cpp)

## 풀이

1. Break mineral.

2. Check if there is any mineral block that is floating.

    2.1. BFS all cells. If BFS starts at 'x' data, collect all connected 'x' data and check if it can be fallen.

3. Loop.

How to make mineral cluster fall?

1.  Identify and temporarily remove the cluster: Once a floating cluster is identified, save the coordinates of all its mineral blocks and change their cells on the board to empty ('.').

2.  Determine the maximum distance the cluster can fall. This is done by checking how many empty rows are below every block in the cluster before it hits the ground or another mineral.

3.  Move the cluster down by the calculated fall distance by updating the board with the cluster's new block positions.