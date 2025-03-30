points = []
for i in range(3):
    x, y = map(int, input().split())
    points.append((x, y))
x_coords = [point[0] for point in points]
y_coords = [point[1] for point in points]
x_fourth = [x for x in x_coords if x_coords.count(x) == 1][0]
y_fourth = [y for y in y_coords if y_coords.count(y) == 1][0]
print(f"{x_fourth} {y_fourth}")