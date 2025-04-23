import math

def find_planet(n, datasets):
    results = []
    for data in datasets:
        m, arr = data
        ship = None
        planets = []

        for i in range(m):
            for j in range(m):
                if arr[i][j] == 's':
                    ship = (i, j)
                elif arr[i][j] == 'p':
                    planets.append((i, j))

        closest_planet = None
        min_distance = float('inf')
        for planet in planets:
            dist = math.sqrt((ship[0] - planet[0])**2 + (ship[1] - planet[1])**2)
            if dist < min_distance:
                min_distance = dist
                closest_planet = planet

        results.append(f"({ship[0]},{ship[1]}):({closest_planet[0]},{closest_planet[1]}):{min_distance:.2f}")
    
    return results

# 입력 처리
n = int(input())
datasets = []
for _ in range(n):
    m = int(input())
    arr = [input().strip() for _ in range(m)]
    datasets.append((m, arr))

results = find_planet(n, datasets)
for result in results:
    print(result)