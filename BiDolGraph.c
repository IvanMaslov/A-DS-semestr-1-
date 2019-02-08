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

int colors[N];
int x_color[N];
int cnt[N];
int rang[N];
int par[N];

int get_set(int v) {
	if (par[v] == v)return v;
	int u = par[v];
	while (par[u] != u) {
		x_color[v] ^= x_color[u];
		u = par[u];
	}
	return par[v] = u;
}

int get_color(int v) {
	get_set(v);
	int ans = colors[v] ^ x_color[v];
	if (par[v] == v)
		return ans;
	ans = ans ^ x_color[par[v]];
	return ans;
}


void unionset(int l, int r) {
	int change_color = get_color(l) == get_color(r);
	l = get_set(l);
	r = get_set(r);
	if (l == r)return l;
	if (rang[l] < rang[r]) {
		int u = r;
		r = l;
		l = u;
	}
	if (rang[l] == rang[r])++rang[l];
	par[r] = l;
	cnt[l] += cnt[r];
	x_color[r] = change_color;
}

void init(int n) {
	for (int i = 0; i <= n; ++i) {
		cnt[i] = rang[i] = 1;
		par[i] = i;
		x_color[i] = colors[i] = 0;
	}
}

int n, m;

void solve() {
	scanf("%d%d", &n, &m);
	init(n);
	int shifts = 0;
	for (int i = 0; i < m; ++i) {
		int ind;
		int x, y;
		scanf("%d%d%d", &ind, &x, &y);
		--x; --y;
		x = (x + shifts) % n;
		y = (y + shifts) % n;
		if (ind == 0) {
			unionset(x, y);
		}
		if (ind == 1) {
			int ans = get_color(x) == get_color(y);
			if (ans)printf("YES\n");
			if (!ans)printf("NO\n");
			shifts = (shifts + ans) % n;
		}
	}
}