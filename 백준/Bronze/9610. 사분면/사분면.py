t = int(input())
quadrant_axis = [0]*5
for _ in range(t):
    x,y = map(int, input().split())
    if (x>0 and y>0):quadrant_axis[0]+=1
    elif (x<0 and y>0):quadrant_axis[1]+=1
    elif (x<0 and y<0):quadrant_axis[2]+=1
    elif (x>0 and y<0):quadrant_axis[3]+=1
    else:quadrant_axis[4]+=1
    
for i in range(1,5):
    print(f"Q{i}: {quadrant_axis[i-1]}")
print("AXIS:",quadrant_axis[4])
