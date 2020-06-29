from sys import stdin
wordList = list(stdin.read().strip().split())
wordDict = dict()
for word in wordList:
    if word not in wordDict:
        wordDict[word] = 0
    wordDict[word] += 1
print(*sorted(sorted(wordDict), key=lambda x: wordDict[x], reverse=True),
      sep="\n")
