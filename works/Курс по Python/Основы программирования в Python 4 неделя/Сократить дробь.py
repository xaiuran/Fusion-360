def ReduceFraction(n, m):
    global p, q
    if m == 0:
        p = p // n
        q = q // n
        return p, q
    ReduceFraction(m, n % m)
    return p, q
n, m = (int(input()), int(input()))
p = n
q = m
print(*ReduceFraction(n, m))
