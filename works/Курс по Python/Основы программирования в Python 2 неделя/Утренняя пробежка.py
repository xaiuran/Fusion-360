x = int(input())
mx = x
while x != 0:
    x = int(input())
    if x > mx and x != 0:
        mx = x
print(mx)
