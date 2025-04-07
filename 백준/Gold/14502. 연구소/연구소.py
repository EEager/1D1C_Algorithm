import sys
from itertools import permutations
from collections import deque

dx = [0, 0, 1, -1]
dy = [1, -1, 0, 0]

N, M = map(int, sys.stdin.readline().split())
MAP = []
empty_spaces = []
virus = []

for i in range(N):
    MAP.append(list(map(int, sys.stdin.readline().split()))) 
    for j in range(M):
        if MAP[i][j] == 0:
            empty_spaces.append((i, j))
        elif MAP[i][j] == 2:
            virus.append((i, j))
            
def spread_virus(TMP):
    q = deque(virus)
    
    while q:
        x, y = q.popleft()
        for i in range(4):
            nx, ny = x + dx[i], y + dy[i]
            if 0 <= nx < N and 0 <= ny < M and TMP[nx][ny] == 0:
                TMP[nx][ny] = 2
                q.append((nx, ny))

def get_safe_zone(TMP):
    return sum(row.count(0) for row in TMP)

def solve():
    """ 모든 벽 배치 경우를 확인하여 최대 안전 영역 찾기 """
    max_safe_zone = 0

    for walls in permutations(empty_spaces, 3):
        TMP = [row[:] for row in MAP]

        for x, y in walls:
            TMP[x][y] = 1

        spread_virus(TMP)
        max_safe_zone = max(max_safe_zone, get_safe_zone(TMP))

    return max_safe_zone

print(solve())