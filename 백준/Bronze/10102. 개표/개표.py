num = int(input())
str = input()
tie = 0
for _ in str:
    tie = tie + (-1 if _=='A' else 1)
if tie==0:print("Tie")
elif tie<0:print("A")
else: print("B")