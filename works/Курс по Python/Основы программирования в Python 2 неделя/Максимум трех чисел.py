a = int(input())
if (a % 4) != 0:
    print('NO')
elif a % 400 == 0:
    print('YES')
elif a % 100 == 0:
    print('NO')
else:
    print('YES')