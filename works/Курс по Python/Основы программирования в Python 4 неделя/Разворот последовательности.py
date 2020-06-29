def printReverse():
    a = int(input())
    if a != 0:
        printReverse()
    print(a)
printReverse()
