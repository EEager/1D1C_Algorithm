import math

DP = [[-1] * 100 for _ in range(1 << 15)]
N = 0
K = 0
V = []
MOD = [0] * 15
p = [0] * 51
len_v = [0] * 15

def dfs(bm, mod):
    if bm == (1 << N) - 1:
        return 1 if mod == 0 else 0
    if DP[bm][mod] != -1:
        return DP[bm][mod]
    
    ret = 0
    for i in range(N):
        if bm & (1 << i):
            continue
        t = mod * p[len_v[i]] + MOD[i]
        t %= K
        ret += dfs(bm | (1 << i), t)
    DP[bm][mod] = ret
    return ret

def fac(n):
    ret = 1
    for i in range(1, n + 1):
        ret *= i
    return ret

def str_to_mod(s):
    l = len(s)
    ret = 0
    for i in range(l):
        ret = (ret * 10 + int(s[i])) % K
    return ret

def get_gcd(a, b):
    return math.gcd(a, b)

def main():
    global N, K, V, MOD, p, len_v
    N = int(input())
    V = []
    for _ in range(N):
        v = input()
        V.append(v)
        len_v[len(V) - 1] = len(v)
    K = int(input())
    p[0] = 1 % K
    for i in range(1, 51):
        p[i] = p[i - 1] * 10 % K
    for i in range(N):
        MOD[i] = str_to_mod(V[i])
    
    for i in range(1 << 15):
        for j in range(100):
            DP[i][j] = -1
    
    Child = dfs(0, 0)
    if Child == 0:
        print("0/1")
    else:
        Parent = fac(N)
        g = get_gcd(Child, Parent)
        a = Child // g
        b = Parent // g
        print(f"{a}/{b}")

if __name__ == "__main__":
    main()
