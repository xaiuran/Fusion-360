def IsPointInCircle(x, y, xc, yc, r):
    return r**2 >= (xc - x)**2 + (yc - y)**2
x, y, xc, yc = (float(input()), float(input()), float(input()), float(input()))
r = float(input())
if IsPointInCircle(x, y, xc, yc, r):
    print('YES')
else:
    print("NO")
