a = list(map(int, input().split()))
b = list(map(int, input().split()))
c = list(set(a) & set(b))
print(*sorted(c))
