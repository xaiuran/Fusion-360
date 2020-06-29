now = int(input())
nowMax = now
i = 1
while now != 0:
    if now > nowMax:
        nowMax = now
        i = 1
    now = int(input())
    if now == nowMax:
        i += 1
print(i)
