n = int(input())
new = []
for i in range(n):
    tmp = set()
    k = int(input())
    for l in range(k):
        tmp |= set(map(str, input().split()))
    new += [tmp]
a = new[0]
b = new[0]
for i in range(len(new)):
    a = a & new[i]
    b = b | new[i]
print(len(a))
print(*a, sep='\n')
print(len(b))
print(*b, sep='\n')
