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

https://swprog.tistory.com/entry/Backtracking-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-Sudoku-Part-1?category=610940

// median value form pq
#include <stdio.h>
#define MAX_SIZE 100
int minheap[MAX_SIZE];
int minCnt = 0;

int maxheap[MAX_SIZE];
int maxCnt = 0;
int mid;
int minpush(int value) {
	minheap[minCnt] = value;
	int cur = minCnt;
	while (cur > 0 && minheap[cur] < minheap[(cur - 1) / 2]){
		int temp = minheap[(cur - 1) / 2];
		minheap[(cur - 1) / 2] = minheap[cur];
		minheap[cur] = temp;
		cur = (cur - 1) / 2;
	}
	minCnt++;
	return 1;
}

int minpop() {
	int rtn = minheap[0];
	minCnt--;
	minheap[0] = minheap[minCnt];

	int cur = 0;
	while (cur * 2 + 1 < minCnt)
	{
		int child;
		if (cur * 2 + 2 == minCnt)
		{
			child = cur * 2 + 1;
		}
		else
		{
			child = minheap[cur * 2 + 1] < minheap[cur * 2 + 2] ? cur * 2 + 1 : cur * 2 + 2;
		}

		if (minheap[cur] < minheap[child])
		{
			break;
		}

		int temp = minheap[cur];
		minheap[cur] = minheap[child];
		minheap[child] = temp;

		cur = child;
	}
	return rtn;
}

int maxpush(int value) {
	maxheap[maxCnt] = value;
	int cur = maxCnt;
	while (cur > 0 && maxheap[cur] > maxheap[(cur - 1) / 2]) {
		int temp = maxheap[(cur - 1) / 2];
		maxheap[(cur - 1) / 2] = maxheap[cur];
		maxheap[cur] = temp;
		cur = (cur - 1) / 2;
	}
	maxCnt++;
	return 1;
}

int maxpop() {
	int rtn = maxheap[0];
	maxCnt--;
	maxheap[0] = maxheap[maxCnt];

	int cur = 0;
	while (cur * 2 + 1 < maxCnt)
	{
		int child;
		if (cur * 2 + 2 == maxCnt)
		{
			child = cur * 2 + 1;
		}
		else
		{
			child = maxheap[cur * 2 + 1] > maxheap[cur * 2 + 2] ? cur * 2 + 1 : cur * 2 + 2;
		}

		if (maxheap[cur] > maxheap[child])
		{
			break;
		}

		int temp = maxheap[cur];
		maxheap[cur] = maxheap[child];
		maxheap[child] = temp;

		cur = child;
	}
	return rtn;
}



void print_pq() {
	printf("[ ");
	for (int i = 0; i < minCnt; i++) {
		printf("%d ", minheap[i]);
	}
	printf("]");
	printf("\n");
	
	printf("\t[ ");
	for (int i = 0; i < maxCnt; i++) {
		printf("%d ", maxheap[i]);
	}
	printf("]");
	printf("\n");
}

bool check(int max, int min) {
	if (max == min || max == min + 1) return true;
	return false;
}

void makebal() {
	if (check(maxCnt, minCnt)) return;
	else {
		while (!check(maxCnt, minCnt)) {
			if (maxCnt > minCnt) {
				mid = maxpop();

				minpush(mid);
			}
			else {
				mid = minpop();
				maxpush(mid);
			}
		}
	}
}

int mx[MAX_SIZE];
int mxCnt;

int mn[MAX_SIZE];
int mnCnt;

void max_sort() {
	int temp;
	int i;
	int j;

	for (i = 1; i < mxCnt+1; i++)	{
		temp = mx[i];
		j = i - 1;

		while ((temp > mx[j]) && (j >= 0))	{
			mx[j + 1] = mx[j];
			j = j - 1;
		}
		mx[j + 1] = temp;
	}
}

void min_sort() {
	int temp;
	int i;
	int j;

	for (i = 1; i < mnCnt+1; i++) {
		temp = mn[i];
		j = i - 1;

		while ((temp < mn[j]) && (j >= 0)) {
			mn[j + 1] = mn[j];
			j = j - 1;
		}
		mn[j + 1] = temp;
	}
}

void movetomax() {
	mx[mxCnt] = mn[0];
	mn[0] = 0;
	mxCnt++;
	mnCnt--;
}

void movetomin() {
	mn[mnCnt] = mx[0];
	mx[0] = 0;
	mnCnt++;
	mxCnt--;
}

void balance() {
	if (check(mnCnt, mxCnt)) return;
	else {
		min_sort();
		max_sort();
		while (!check(mnCnt, mxCnt)) {
			if (mxCnt > mnCnt) {
				movetomin();
			}
			else {
				movetomax();
			}
			min_sort();
			max_sort();
		}
	}
}

void print_sort() {
	printf("[ ");
	for (int i = 0; i < mxCnt; i++) {
		printf("%d ", mx[i]);
	}
	printf("]");
	printf("\n");

	printf("\t[ ");
	for (int i = 0; i < mnCnt; i++) {
		printf("%d ", mn[i]);
	}
	printf("]");
	printf("\n");
}

void init() {
	for (register int i = 0; i < MAX_SIZE; i++) {
		mx[i] = 0;
		mn[i] = 0xffffff;
	}
}

int main() {
	mnCnt = mxCnt = 0;
	init();
	for (int i = 1; i < 20; i++) {
		mx[i] =i;
		mxCnt++;
	}
	balance();
	print_sort();
	print_sort();


#if 0
	minCnt = 0;
	maxCnt = 0;
	for (int i = 1; i < 10; i++) {
		maxpush(i);		
	}
	print_pq();
	makebal();
	mid = maxheap[0];
	print_pq();
	
	// removoe mid
	maxpop();
	maxpop();
	makebal();
	print_pq();
#endif
	return 0;
}

