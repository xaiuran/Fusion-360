str = list(map(int, input().split()))
if len(str) % 2 == 0:
    for i in range(0, len(str), 2):
        str[i], str[i+1] = str[i+1], str[i]
else:
    for i in range(0, len(str) - 1, 2):
        str[i], str[i+1] = str[i+1], str[i]
print(*str)
