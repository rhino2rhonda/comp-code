import random

n_tc = 10
print(n_tc)

for tc_id in range(n_tc):
	for _ in range(2):
		ln = random.randint(5, 10)
		seq = "".join([str(random.randint(0,9)) for l in range(ln)])
		print(seq)
