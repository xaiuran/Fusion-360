a, b, c = int(input()), int(input()), int(input())
if a > b:
    if a > c:
        if b > c:
            a, b, c = c, b, a
        else:
            a, b, c = b, c, a
    else:
        a, b, c = b, a, c
elif b > c:
        if a > c:
            a, b, c = c, a, b
        else:
            a, b, c = a, c, b
print(a, b, c)
