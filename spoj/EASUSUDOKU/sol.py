import pprint

def get_grid(i, j):
	return i // 3, j // 3

# for i in range(9):
# 	print(list(map(lambda j: get_grid(i,j), [x for x in range(9)])))

class Sudoku:

	def __init__(self, board):
		self.trials = 0
		self.board = board
		self.pending = set()
		self.row_elems = [set() for _ in range(9)]
		self.col_elems = [set() for _ in range(9)]
		self.grid_elems = [[set() for _ in range(3)] for _ in range(3)]
		for i in range(9):
			for j in range(9):
				if board[i][j] == 0:
					self.pending.add((i, j))
				else:
					self.row_elems[i].add(board[i][j])
					self.col_elems[j].add(board[i][j])
					a, b = get_grid(i, j)
					self.grid_elems[a][b].add(board[i][j])

def get_sorted_moves(sudoku):
	def _get_moves(a, b):
		ga, gb = get_grid(a, b)
		moves = set([x + 1 for x in range(9)])
		return moves - sudoku.row_elems[a] - sudoku.col_elems[b] - sudoku.grid_elems[ga][gb]
	pending = list(sudoku.pending)
	moves = list(map(lambda x: _get_moves(x[0], x[1]), pending))
	pending_moves = list(sorted(zip(pending, moves), key=lambda x: len(x[1])))
	return pending_moves

def solve(sudoku):
	if len(sudoku.pending) == 0:
		return True
	sudoku.trials += 1
	# if sudoku.trials > 50:
	# 	5/0
	# print()
	# print('Trial', sudoku.trials)
	# pprint.pprint(sudoku.board)
	# print('Num Pending', len(sudoku.pending))
	pending_moves = get_sorted_moves(sudoku)
	for (a, b), moves in pending_moves:
		ga, gb = get_grid(a, b)
		# print('Cell chosen', a, b)
		sudoku.pending.remove((a, b))
		# print('Possible moves', moves)
		for move in moves:
			sudoku.board[a][b] = move
			sudoku.row_elems[a].add(move)
			sudoku.col_elems[b].add(move)
			sudoku.grid_elems[ga][gb].add(move)
			if solve(sudoku):
				return True
			sudoku.board[a][b] = 0
			sudoku.row_elems[a].remove(move)
			sudoku.col_elems[b].remove(move)
			sudoku.grid_elems[ga][gb].remove(move)
		sudoku.pending.add((a, b))
		# print('No solution in this path')
	return False

def run():
	t = int(input())

	for _ in range(t):
		board = []
		for _ in range(9):
			board.append([int(x) for x in input().split()])
		sudoku = Sudoku(board)
		# pprint.pprint(sudoku.grid_elems)
		solved = solve(sudoku)
		if solved:
			pprint.pprint(sudoku.board)
		else:
			print("No solution")
		print('Trials', sudoku.trials)

run()