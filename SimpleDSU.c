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

int min_in_set[N];
int max_in_set[N];
int cnt[N];
int rang[N];
int par[N];

int get_set(int v) {
	if (par[v] == v)return v;
	return par[v] = get_set(par[v]);
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
	cnt[l] += cnt[r];
}

int n;
void solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		min_in_set[i] = max_in_set[i] = i;
		cnt[i] = rang[i] = 1;
		par[i] = i;
	}
	char* t = (char*)malloc(6 * sizeof(char));
	while (scanf("%s", t) != EOF) {
		int a, b;
		if (t[0] == 'g') {
			scanf("%d", &a);
			int v = get_set(a);
			printf("%d %d %d\n", min_in_set[v], max_in_set[v], cnt[v]);
		}
		if (t[0] == 'u') {
			scanf("%d", &a);
			scanf("%d", &b);
			unionset(a, b);
		}
	}
}