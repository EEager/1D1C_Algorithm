import heapq

t = int(input())

for _ in range(t):
    n = int(input())
    a = []
    for i in range((n-1)//10 +1):
        a.extend(list(map(int, input().split())))
    
    l = n//2 + n%2
    print(l)
    maxHeap = [] 
    minHeap = [] 
    for i in range(n):
        heapq.heappush(maxHeap, -a[i])
        heapq.heappush(minHeap, -heapq.heappop(maxHeap))
        if len(maxHeap) < len(minHeap):
            heapq.heappush(maxHeap, -heapq.heappop(minHeap))
        if i%2==0:
            if i!=0 and i%18==0:
                print (-maxHeap[0])
            else:
                print (-maxHeap[0], end=' ')
    print()
    