def f(num):
    s = 0
    ret = []
    for i in range(1, int(num**0.5) + 1):
        if num % i == 0: 
            s+=i
            ret.append(i)
            if i != 1 and i != num // i: 
                s += num // i
                ret.append(num // i)
    ret.sort()  
    if (s==num):
        print(f"{num} = ", end='')
        for _ in ret[:-1]:
            print(f"{_} + ", end='')
        print(ret[-1])
    else:
        print(f"{num} is NOT perfect.")

while True:
    n = int(input())
    if n==-1:break
    f(n)
    
