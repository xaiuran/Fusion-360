a = list(map(int, input().split()))
d = {}

for el in a:
    if el in d:
        print("YES")
    else:
        d[el] = 1
        print("NO")
