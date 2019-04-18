#include <stdio.h>
#define MAX_N  10
static const int INFINITE = 9999999;
int tree[MAX_N << 2];
int arr[11] = { 0,1,2,3,4,5,6,7,8,9,10 };

int init(int n, int s, int e) {
	if (s == e)
		return tree[n] = arr[s];
	int m = (s + e) / 2;
	tree[n] = init(n * 2, s, m) + init(n * 2 + 1, m + 1, e);
	return tree[n];
}

void update(int n, int s, int e, int t, int diff) {
	if (s <= t && t <= e)
		tree[n] += diff;
	else
		return;
	if (s == e)
		return;
	int m = (s + e) / 2;
	update(n * 2, s, m, t, diff);
	update(n * 2 + 1, m + 1, e, t, diff);
}

int  sum(int l, int r, int n, int s, int e) {
	if (l <= s && e <= r) return tree[n];
	if (r < s || e < l) return 0;
	int m = (s + e) / 2;
	return sum(l, r, n * 2, s, m) + sum(l, r, n * 2 + 1, m+1, e);
		
}

int _min(int a, int b) {
	if (a > b) return b;
	else       return a;
}

int _max(int a, int b) {
	if (a > b) return a;
	else       return b;
}
int initmin(int n, int s, int e) {
	if (s == e)
		return tree[n] = arr[s];
	int m = (s + e) / 2;
	tree[n] = _min(initmin(n * 2, s, m) , initmin(n * 2 + 1, m + 1, e));
	return tree[n];
}

int initmax(int n, int s, int e) {
	if (s == e)
		return tree[n] = arr[s];
	int m = (s + e) / 2;
	tree[n] = _max(initmax(n * 2, s, m), initmax(n * 2 + 1, m + 1, e));
	return tree[n];
}
int getmin(int l, int r, int n, int s, int e) {
	if (l <= s && e <= r) return tree[n];
	if (r < s || e < l) return INFINITE;
	int m = (s + e) / 2;
	int left = getmin(l, r, n * 2, s, m);
	int right = getmin(l, r, n * 2 + 1, m + 1, e);
	return _min(left, right);
}

int getmax(int l, int r, int n, int s, int e) {
	if (l <= s && e <= r) return tree[n];
	if (r < s || e < l) return 0;
	int m = (s + e) / 2;
	int left = getmax(l, r, n * 2, s, m);
	int right = getmax(l, r, n * 2 + 1, m + 1, e);
	return _max(left, right);
}

int main() {
	int s;
	init(1, 1, 10);
	s= sum(2, 5, 1, 1, 10);
	printf("%d\n", s);
	int c = 10;
	int diff = c - arr[3];
	arr[3] = c;
	update(1, 1, 10, 3, diff);
	s = sum(2, 5, 1, 1, 10);
	printf("%d\n", s);
	s = getmin(2, 5, 1, 1, 10);
	printf("%d\n", s);
	s = getmax(2, 5, 1, 1, 10);
	printf("%d\n", s);
	return 1;
}
/// sudoku
#include <stdio.h>
#include <string.h>
#define SZ 9
void solveSudoku(int r, int c);
int sudoku[SZ][SZ] = {
	4,0,7,5,0,0,0,0,8,
	0,5,0,7,0,0,4,0,9,
	0,0,6,0,0,4,0,7,0,
	9,0,0,6,0,0,2,4,3,
	0,4,0,9,0,3,0,8,0,
	7,3,1,0,0,2,0,0,5,
	0,2,0,8,0,0,7,0,0,
	3,0,9,0,0,6,0,5,0,
	5,0,0,0,0,7,3,0,4
};

int readOnlySudoku[SZ][SZ];
int solutionCnt = 0;
void initReadOnlySudoku(void) {
	memcpy(readOnlySudoku, sudoku, sizeof(sudoku));
}

int isOK(int r, int c, int v) {
	for (int i = 0; i < SZ; i++) {
		if (sudoku[i][c] == v && i != r) {
			return 0;
		}
	}
	for (int i = 0; i < SZ; i++) {
		if (sudoku[r][i] == v && i != c) {
			return 0;
		}
	}
	int region_r = r / 3;
	int region_c = c / 3;
	for (int i = region_r * 3; i <= region_r * 3 + 2; i++) {
		for (int j = region_c * 3; j <= region_c * 3 + 2; j++) {
			if (sudoku[i][j] == v && i != r && j != c) {
				return 0;
			}
		}
	}
	return 1;
}
void printSolution() {
	solutionCnt++;
	printf("=================== Solution # %d =============\n", solutionCnt);
	for (int i = 0; i < SZ; i++) {
		for (int j = 0; j < SZ; j++) {
			printf("%d ", sudoku[i][j]);
		}
		printf("\n");
	}
}
void checkNext(int r, int c) {
	if (r == (SZ - 1) && c == (SZ - 1)) {
		printSolution();
		return;
	}
	c++;
	if (c == SZ) {
		c = 0;
		r++;
	}
	solveSudoku(r, c);
}

void solveSudoku(int r, int c) {
	if (sudoku[r][c] > 0) {
		checkNext(r, c);
	}
	else {
		for (int i = 0; i < 9; i++) {
			memcpy(&sudoku[r][c], &readOnlySudoku[r][c], sizeof(int)*SZ*SZ-sizeof(int)*(r+SZ+c));
			if (isOK(r, c, i) == 1) {
				sudoku[r][c] = i;
				checkNext(r, c);
			}
		}
	}
}

int main() {

	initReadOnlySudoku();
	solveSudoku(0, 0);
	return 0;
}

