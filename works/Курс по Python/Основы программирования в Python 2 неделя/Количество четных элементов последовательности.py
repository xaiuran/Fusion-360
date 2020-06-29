x = int(input())
max1 = x
max2 = 0
while x != 0:
    x = int(input())
    if x >= max1:
        max2 = max1
        max1 = x
    if max1 > x >= max2:
        max2 = x
print(max2)
