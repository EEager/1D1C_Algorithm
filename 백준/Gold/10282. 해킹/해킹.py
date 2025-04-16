import sys
import heapq

INF = int(1e9)

def dijkstra(start, n, graph):
    dist = [INF] * (n + 1)
    dist[start] = 0
    pq = [(0, start)]  
    
    while pq:
        time, node = heapq.heappop(pq)
        
        if time > dist[node]:
            continue
        
        for next_node, next_time in graph[node]:
            if dist[next_node] > time + next_time:
                dist[next_node] = time + next_time
                heapq.heappush(pq, (dist[next_node], next_node))

    infected = sum(1 for d in dist if d != INF)
    max_time = max((d for d in dist if d != INF), default=0)
    
    print(infected, max_time)

def main():
    input = sys.stdin.read
    data = input().splitlines()
    
    t = int(data[0])
    index = 1
    
    for _ in range(t):
        n, d, c = map(int, data[index].split())
        index += 1
        graph = [[] for _ in range(n + 1)]
        for _ in range(d):
            a, b, s = map(int, data[index].split())
            graph[b].append((a, s))
            index += 1
        
        dijkstra(c, n, graph)

if __name__ == "__main__":
    main()