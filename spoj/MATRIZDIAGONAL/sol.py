# AC solution in C

import sys

order = int(input())
m = []
for i in range(order):
	m.append([int(x.strip()) for x in input().split()])

for i in range(order):
	for j in range(order):
		if i == j: continue
		if m[i][j] != 0:
			print('Falso')
			sys.exit(0)
			
print('Verdadero')
