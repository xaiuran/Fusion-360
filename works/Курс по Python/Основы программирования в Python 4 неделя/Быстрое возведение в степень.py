def rec(a, n):
    if a % 2 == 0:
        return (a ** 2) ** (n / 2)
    return a * rec(a, n - 1)
a = float(input())
n = int(input())
print(rec(a, n))
