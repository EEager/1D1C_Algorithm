pos = 0
def inorder(n, depth) :
    global pos
    if n == -1:
        return 
    inorder(tree[n][0], depth+1)
    minDepthidx[depth] = min(minDepthidx[depth], pos)
    maxDepthidx[depth] = max(maxDepthidx[depth], pos)
    pos += 1
    inorder(tree[n][1], depth+1)

n = int(input())  
parentNode = [-1]*(n+1)
minDepthidx = [n+1] * (n+1)
maxDepthidx = [0] * (n+1)
tree = {}
root = 0
for _ in range(n):  
    v, left, right = map(int, input().split(' '))
    tree[v] = [left, right]
    if left != -1:
        parentNode[left] = v
    if right != -1:
        parentNode[right] = v

for i in range(1, n+1): 
    if parentNode[i] == -1:
        root = i
inorder(root, 1)

ans = [1,1]
for i in range(n):
    diff = maxDepthidx[i] - minDepthidx[i] + 1
    if diff > ans[1]:
        ans[0] = i
        ans[1] = diff

print(ans[0], ans[1])