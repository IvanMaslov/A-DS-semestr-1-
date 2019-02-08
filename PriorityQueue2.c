#define _CRT_SECURE_NO_WARNINGS

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//that's all

void solve();

int main() {
	solve();
	system("pause");
	return 0;
}

#define ll long long 
unsigned int A, B;
unsigned int cur = 0;
inline unsigned int nextRand24() {
	cur = cur * A + B;
	return cur >> 8;
}
inline unsigned int nextRand32() {
	unsigned int A = nextRand24(), B = nextRand24();
	return (A << 8) ^ B;
}

#define ll long long
#define N 3000001
#define min(x, y) ((x < y) ? (x) : (y))
#define max(x, y) ((x > y) ? (x) : (y))

int n;

int h[N];
int index[N];
int val[N];

void swp(int i, int j) {
	int tmp;

	tmp = h[i];
	h[i] = h[j];
	h[j] = tmp;

	index[h[i]] = i;
	index[h[j]] = j;
}

int cmp(int i, int j) {
	return val[h[i]] - val[h[j]];
}

void siftUp(int u) {
	while (u > 0) {
		if (cmp(u, (u - 1) / 2) >= 0)break;
		swp(u, (u - 1) / 2);
		u--; u >>= 1;
	}
}
void siftDown(int u) {
	while (u * 2 + 1 < n) {
		int l = 2 * u + 1;
		int r = 2 * u + 2;
		int v = l;
		if (r < n && cmp(l, r) > 0)
			v = r;
		if (cmp(u, v) <= 0)
			break;
		swp(u, v);
		u = v;
	}
}

void solve() {
	int nxt = 0;
	char* t = (char*)malloc(60 * sizeof(char));
	while (scanf("%s", t) != EOF) {
		++nxt;
		if (t[0] == 'p') {
			index[nxt] = n;
			h[n++] = nxt;
			scanf("%d", val + nxt);
			siftUp(index[nxt]);
		}
		if (t[0] == 'e') {
			if (n == 0) {
				printf("*\n");
				continue;
			}
			swp(0, n - 1);
			--n;
			siftDown(0);
			printf("%d %d\n", val[h[n]], h[n]);
		}
		if (t[0] == 'd') {
			int u, d;
			scanf("%d%d", &u, &d);
			val[u] = d;
			siftUp(index[u]);
			siftDown(index[u]);
		}
		
	}
}