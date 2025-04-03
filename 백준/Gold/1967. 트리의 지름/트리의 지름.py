from collections import deque

def bfs(start, step, n, graph):
    dis = [0] * (n + 1)  
    visited = [False] * (n + 1)  
    q = deque([start])
    visited[start] = True

    while q:
        tmp = q.popleft()
        for adj, weight in graph[tmp]:
            if not visited[adj]:
                visited[adj] = True
                dis[adj] = dis[tmp] + weight
                q.append(adj)

    max_dist = 0
    farthest_node = start
    for i in range(1, n + 1):
        if dis[i] > max_dist:
            max_dist = dis[i]
            farthest_node = i

    return farthest_node if step == 1 else max_dist

n = int(input())
graph = [[] for _ in range(n + 1)]

for _ in range(n - 1):
    a, b, c = map(int, input().split())
    graph[a].append((b, c))
    graph[b].append((a, c))

next = bfs(1, 1, n, graph)  
ans = bfs(next, 2, n, graph)  
print(ans)