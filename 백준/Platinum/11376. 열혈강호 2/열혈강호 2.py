from collections import defaultdict

MAX = 1001

tasks = defaultdict(list)
whoWork = [0] * MAX
v = [False] * MAX

def dfs(employee):
    if v[employee]:
        return False
    v[employee] = True
    for n in tasks[employee]:
        if whoWork[n] == 0 or dfs(whoWork[n]):
            whoWork[n] = employee
            return True
    return False

def main():
    import sys
    input = sys.stdin.read
    data = input().splitlines()
    
    N, M = map(int, data[0].split())
    for i in range(1, N + 1):
        line = list(map(int, data[i].split()))
        c = line[0]
        jobs = line[1:]
        tasks[i].extend(jobs)
    
    cnt = 0
    for i in range(1, N + 1):
        for _ in range(2):
            global v
            v = [False] * (N + 1)
            if dfs(i):
                cnt += 1
    
    print(cnt)

if __name__ == "__main__":
    main()
