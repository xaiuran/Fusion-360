print(*list(map(lambda xy: (xy[0] + xy[1]) % 2, zip(map(int, input().split()), map(int, input().split())))))

