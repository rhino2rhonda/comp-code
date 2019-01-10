import random
import time

def normalize(arr):
	mn = arr[0]
	if mn <= 0:
		for i in range(len(arr)):
			arr[i] += -mn + 1
	return arr, mn

def denormalize(arr, mn):
	if mn <= 0:
		for i in range(len(arr)):
			arr[i] -= -mn + 1
	return arr

def normalized(func):
	def wrap(arr):
		res, mn = normalize(arr)
		return denormalize(func(res), mn)
	return wrap

def minmax_bf(arr):
	size = len(arr)
	temp_arr = arr[:]
	count = 0
	while True:
		dest = count*2 + 1
		if dest >= size:
			break
		arr[dest] = temp_arr[count]
		count += 1
	i = 0
	while count < size:
		dest = i*2
		arr[dest] = temp_arr[size-i-1]
		i += 1
		count += 1
	return arr

@normalized
def minmax_modq(arr):
	M = arr[-1] + 1
	size = len(arr)
	minp = 0
	maxp = size-1
	for i in range(size):
		if i%2 == 0:
			old = arr[maxp] % M
			maxp -= 1
		else:
			old = arr[minp] % M
			minp += 1
		arr[i] = old*M + arr[i]
	for i in range(size):
		arr[i] = int(arr[i] / M)
	return arr

@normalized
def minmax_juggle(arr):
	size = len(arr)
	for i in range(size):
		j = i
		temp = arr[j]
		while True:
			dest = j*2 +1 
			dest = dest if dest < size else (size-j-1)*2
			# print("dbg", i, j, dest, temp, arr)
			if arr[dest] <= 0:
				break
			temp, arr[dest] = arr[dest], -temp
			j = dest
	for i in range(size):
		arr[i] *= -1
	return arr

def generate_tests(t, size_min, size_max, num_min, num_max):
	tests = []
	for i in range(t):
		test = []
		size = random.randint(size_min, size_max)
		for j in range(size):
			test.append(random.randint(num_min, num_max))
		test.sort()
		tests.append(test)
	return tests

def run_tests():
	tests = generate_tests(100, 1000, 10000, -300000, 500000)
	for i, test in enumerate(tests):
		res1 = minmax_bf(test)
		res2 = minmax_modq(test)
		res3 = minmax_juggle(test)
		try:
			assert res1 == res2 == res3
			print('Test {} passed'.format(i+1))
		except:
			print('Test {} failed'.format(i+1))
			print(res1)
			print(res2)
			print(res3)

def profile_time():
	tests = generate_tests(1000, 1000, 10000, -300000, 500000)
	for name, func in [
		['juggle', minmax_juggle],
		['modulo quotient', minmax_modq],
		['brute force', minmax_bf]
	]:
		start = time.time()
		for i, test in enumerate(tests):
			func(test)
		end = time.time()
		print('Algo {} took {} seconds'.format(name, end-start))

profile_time()