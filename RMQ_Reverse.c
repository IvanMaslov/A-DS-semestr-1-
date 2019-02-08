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

int f[N];
int v[N];
int ind[N];
int n, m;


int cmpp(int l, int r) {
	return abs(f[l]) - abs(f[r]);
}

int b[N];
void mergeSort(int* l, int* r) {
	if (l + 1 >= r)return;
	int* m = l + (r - l) / 2;
	mergeSort(l, m);
	mergeSort(m, r);
	int* L = l;
	int* R = m;
	int* nxt = b;
	while (L != m || R != r) {
		if (L == m) *(nxt++) = *(R++);
		else if (R == r) *(nxt++) = *(L++);
		else if (cmpp(*L, *R) > 0) *(nxt++) = *(R++);
		else *(nxt++) = *(L++);
	}
	for (int i = 0; i < nxt - b; ++i)
		l[i] = b[i];
}


int heap_size = 0;
int nxt = 0;
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

ll cmp_heap(int i, int j) {
	return 1ll * val[h[j]] - val[h[i]];
}

void siftUp(int u) {
	while (u > 0) {
		if (cmp_heap(u, (u - 1) / 2) >= 0)break;
		swp(u, (u - 1) / 2);
		u--; u >>= 1;
	}
}
void siftDown(int u) {
	while (u * 2 + 1 < heap_size) {
		int l = 2 * u + 1;
		int r = 2 * u + 2;
		int v = l;
		if (r < heap_size && cmp_heap(l, r) > 0)
			v = r;
		if (cmp_heap(u, v) <= 0)
			break;
		swp(u, v);
		u = v;
	}
}

int push_heap(int vl) {
	++nxt;
	index[nxt] = heap_size;
	h[heap_size++] = nxt;
	val[nxt] = vl;
	siftUp(index[nxt]);
	return nxt;
}

int max_heap() {
	return val[h[0]];
}

void pop_heap(int indx) {
	int ni = index[indx];
	swp(index[indx], heap_size - 1);
	--heap_size;
	indx = h[ni];
	siftUp(index[indx]);
	siftDown(index[indx]);
}

int index_in_heap[N];
void solve() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; ++i) {
		scanf("%d%d%d", f + i * 2 + 1, f + i * 2 + 2, v + i * 2 + 1);
		f[i * 2 + 2]++;
		f[i * 2 + 2] = -f[i * 2 + 2];
		v[i * 2 + 2] = v[i * 2 + 1];
		ind[i * 2 + 1] = i * 2 + 1;
		ind[i * 2 + 2] = i * 2 + 2;
	}
	mergeSort(ind + 1, ind + m * 2 + 1);
	int u = 1;
	for (int c = 1; c <= n; ++c) {
		while (u <= m * 2 && abs(f[ind[u]]) == c) {
			if (f[ind[u]] < 0)
				pop_heap(index_in_heap[ind[u] - 1]);
			else
				index_in_heap[ind[u]] = push_heap(v[ind[u]]);
			++u;
		}
		printf("%d ", max_heap());
	}
}