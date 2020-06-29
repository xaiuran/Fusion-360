l = input()
numbers = list(map(int, input().strip().split()))
x = int(input().strip())

res = numbers[0]
for i in numbers:
    if abs(i - x) < abs(res - x):
        res = i

print(res)
