def sum():
    n = int(input())
    if n != 0:
        return n + sum()
    return 0
print(sum())
