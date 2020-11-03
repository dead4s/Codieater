'''
source code from : acmicpc.net/source/21879412
this is just for Judge Server Testing 
'''

import sys

input = sys.stdin.readline
heights = [int(input()) for _ in range(int(input()))]
heights.append(0)
height = [0]
width = [0]
max_sq = 0
for i in range(len(heights)):
    if heights[i] >= height[-1]:
        height.append(heights[i])
        width.append(i)
    else:
        while True:
            sq = height.pop() * (i-width[-1])
            max_sq = max(sq, max_sq)
            if heights[i] >= height[-1]:
                break
            width.pop()
        height.append(heights[i])
print(max_sq)
