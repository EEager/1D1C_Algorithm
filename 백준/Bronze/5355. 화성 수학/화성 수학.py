def f(result, op):
    return result * 3 if op == "@" else result + 5 if op == "%" else result - 7 if op == "#" else result

if __name__ == "__main__":
    for _ in range(int(input())):
        inputs = input().split()
        result = float(inputs[0])
        for op in inputs[1:]:
            result = f(result, op)
        print(f"{result:.2f}")