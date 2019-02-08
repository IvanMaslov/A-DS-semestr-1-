#define _CRT_SECURE_NO_WARNINGS

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
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

int min_in_set[N];
int max_in_set[N];
int dlt_is_set[N];
int cnt[N];
int rang[N];
int par[N];

int get_set(int v) {
	if (par[v] == v)return v;
	int u = par[v];
	while (par[u] != u) {
		dlt_is_set[v] += dlt_is_set[u];
		u = par[u];
	}
	return par[v] = u;
}

void unionset(int l, int r) {
	l = get_set(l);
	r = get_set(r);
	if (l == r)return l;
	if (rang[l] > rang[r]) {
		int u = r;
		r = l;
		l = u;
	}
	if (rang[l] == rang[r])++rang[l];
	par[r] = l;
	min_in_set[l] = min(min_in_set[l], min_in_set[r]);
	max_in_set[l] = max(max_in_set[l], max_in_set[r]);
	dlt_is_set[r] += -dlt_is_set[l];
	cnt[l] += cnt[r];
}

void init(int n) {
	for (int i = 1; i <= n; ++i) {
		min_in_set[i] = max_in_set[i] = i;
		cnt[i] = rang[i] = 1;
		par[i] = i;
	}
}

int get_sum(int i) {
	int pred = get_set(i);
	int ans = dlt_is_set[i];
	if (pred != i)
		ans += dlt_is_set[pred];
	return ans;
}

const int p = 1000003;
int readed[N];
int n, q;
void solve() {
	scanf("%d%d", &n, &q);
	init(n);
	int zerg = 0;
	while (q--) {
		assert(zerg >= 0);
		int ind;
		scanf("%d", &ind);
		if (ind == 1) {
			int i;
			scanf("%d", &i);
			i = (i + zerg) % n;
			dlt_is_set[get_set(i)]++;
			zerg = (30 * zerg + 239) % p;
		}
		if (ind == 2) {
			int i, j;
			scanf("%d%d", &i, &j);
			i = (i + zerg) % n;
			j = (j + zerg) % n;
			if (get_set(i) == get_set(j))continue;
			unionset(i, j);
			zerg = (13 * zerg + 11) % p;
		}
		if (ind == 3) {
			int i;
			scanf("%d", &i);
			i = (i + zerg) % n;
			int q = get_sum(i) - readed[i];
			zerg = (100500ll * zerg + q) % p;
			printf("%d\n", q);
			readed[i] += q;
		}
	}
}