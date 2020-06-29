n = int(input(''))
l1 = '+___ '
l3 = '|__\ '
l4 = '|    '
print(l1 * n)
for i in range(1, n + 1):
    l2 = f'|{i} / '
    print(l2, end='')
print(end='\n')
print(l3 * n)
print(l4 * n)
