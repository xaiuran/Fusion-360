n = int(input())
m = int(input())

if n < m:
    for i in range(n, m + 1):
        print(i, end=' ')
else:
    for i in range(n, m - 1, -1):
        print(i, end=' ')
