fin = open('input.txt', encoding='utf8')
candidateDict = {}
votes = 0
for line in fin:
    candidate = line.strip()
    candidateDict[candidate] = candidateDict.get(candidate, 0) + 1
    votes += 1
first = max(candidateDict, key=candidateDict.get)
fout = open('output.txt', 'w', encoding='utf8')
if 2 * candidateDict[first] > votes:
    print(first, file=fout)
else:
    print(first, file=fout)
    print(sorted(candidateDict, key=candidateDict.get, reverse=True)[1],
          file=fout)
