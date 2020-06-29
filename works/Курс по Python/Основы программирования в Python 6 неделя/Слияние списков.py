def merge(a, b):
    if len(a) < len(b):
        a, b = b, a
    i = 0
    j = 0
    newList = []
    while i < len(a) and j < len(b):
        if a[i] < b[j]:
            newList.append(a[i])
            i += 1
        elif a[i] >= b[j]:
            newList.append(b[j])
            j += 1
    if i == len(a):
        while j < len(b):
            newList.append(b[j])
            j += 1
    else:
        while i < len(a):
            newList.append(a[i])
            i += 1
    print(*newList)

a = list(map(int, input().split()))
b = list(map(int, input().split()))
merge(a, b)
