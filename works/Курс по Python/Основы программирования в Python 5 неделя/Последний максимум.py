str = list(map(int, input().split()))

n = str[0]
index = 0

for i in range(0, len(str)):
    if str[i] >= n:
        n = str[i]
        index = i

print(n, index)
