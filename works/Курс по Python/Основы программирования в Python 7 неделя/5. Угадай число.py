n = int(input())
yes_set = set([i for i in range(1, n + 1)])
no_set = set()
while True:
    guess_set = input()
    if guess_set == 'HELP':
        yes_set -= no_set
        break
    answer = input()
    guess_set = set(map(int, guess_set.split()))
    if answer == 'YES':
        yes_set &= guess_set
    elif answer == 'NO':
        no_set |= guess_set
print(*sorted(yes_set))
