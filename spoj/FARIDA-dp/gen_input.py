import random

test_cases=10000
max_monsters=1000

print(test_cases)
for t in range(test_cases):
	m = random.randint(0, max_monsters)
	print(m)
	M = [str(random.randint(0, 1000000000)) for _ in range(m)]
	print(" ".join(M))