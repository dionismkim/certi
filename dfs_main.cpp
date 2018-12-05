#include <stdio.h>
#define N 5
struct POS {
	int r;
	int c;
};

enum DIR{ UP, RIGHT, DOWN, LEFT };

POS shortPath[25];
int sdmsize = 30;

#if 0
int m[N][N];
int v[N][N];
#endif

int dc[4] = { 0, 1, 0, -1 };
int dr[4] = { -1, 0, 1, 0 };

bool isOK(int r, int c) {
	return ((r >= 0 && r < N) && (c >= 0 && c < N));
}

void getShortPath(POS from, POS to, int count, POS list[], int v[5][5]) {

	// escape then save path
	if (count > sdmsize)
		return;

	if (from.c == to.c && from.r == to.r) {
		if (sdmsize > count) {
			for (int i = 0; i < count; ++i)
				shortPath[i] = list[i];
			sdmsize = count;
		}
		return;
	}

	for (int dir = UP; dir <= LEFT; dir++) {
		POS next;
		next.r = from.r + dr[dir];
		next.c = from.c + dc[dir];
		if (isOK(next.r, next.c) && !v[next.r][next.c]) {
			v[next.r][next.c] = 1;
			list[count] = next;
			getShortPath(next, to, count + 1, list, v);
			v[next.r][next.c] = 0;
		}

	}
}

int main() {

	int m[5][5] = {
		{ 0, 0, 0, 0, 1 },
		{ 0, 1, 1, 0, 0 },
		{ 0, 0, 1, 0, 0 },
		{ 0, 0, 1, 0, 1 },
		{ 0, 0, 0, 0, 0 }
	};
	POS from, to;
	from.r = 0; from.c = 0;
	to.r = 4; to.c = 4;
	POS list[25];
	getShortPath(from, to, 0, list, m);

	for (int i = 0; i < sdmsize; i++)
		printf("[%d][%d]->", shortPath[i].r, shortPath[i].c);
	printf("\n");

}