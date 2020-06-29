str = list(map(int, input().split()))
min = str.index(min(str))
max = str.index(max(str))
str[min], str[max] = str[max], str[min]

print(*str, sep=' ')
