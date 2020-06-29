str = list(map(int, input().split()))

for i in range(1, len(str)):
    if str[i] > str[i - 1]:
        print(str[i], end=' ')
