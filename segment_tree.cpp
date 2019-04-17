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

