str = list(map(int, input().split()))
min = 100000
for i in range(1, len(str)):
    if min > str[i] and str[i] > 0:
        min = str[i]
print(min)
