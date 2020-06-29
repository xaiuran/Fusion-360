def IsPrime(n):
    i = 2
    if n <= 3:
        return True
    while i <= n ** (1 / 2):
        if n % i == 0:
            return False
        i = i + 1
    return True
n = int(input())
if IsPrime(n):
    print('YES')
else:
    print("NO")
