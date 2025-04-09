min_value = "9999999999"
max_value = "0000000000"

def bt(index, num_list, visited, signs):
    global min_value, max_value
    
    if index == len(signs) + 1:
        current_value = "".join(map(str, num_list))
        min_value = min(min_value, current_value)
        max_value = max(max_value, current_value)
        return

    for i in range(10):
        if not visited[i]:
            if index == 0 or (signs[index - 1] == '<' and num_list[-1] < i) or (signs[index - 1] == '>' and num_list[-1] > i):
                visited[i] = True
                num_list.append(i)
                bt(index + 1, num_list, visited, signs)
                num_list.pop()
                visited[i] = False

def solve(signs):
    global min_value, max_value
    visited = [False] * 10

    bt(0, [], visited, signs)
    
    return max_value, min_value

#main
n = int(input())
signs = list(input().split())
max_result, min_result = solve(signs)
print(max_result)
print(min_result)