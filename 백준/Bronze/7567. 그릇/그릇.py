inputs = input()
len = 10
preFace = inputs[0]
for _ in inputs[1:]:
    if preFace != _:
        len += 10
        preFace = _
    else:
        len += 5
print(len)