now = int(input())
c = maxc = 1
while now != 0:
    prev = now
    now = int(input())
    if now == prev:
        c += 1
        if maxc <= c:
            maxc = c
    else:
        c = 1
print(maxc)
