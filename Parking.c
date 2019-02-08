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

int max_in_set[N];
int min_in_set[N];
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
	max_in_set[l] = max(max_in_set[l], max_in_set[r]);
	min_in_set[l] = min(min_in_set[l], min_in_set[r]);
	cnt[l] += cnt[r];
}

int n;
int empt[N];
void solve() {
	scanf("%d", &n);
	for (int i = 0; i <= n; ++i) {
		max_in_set[i] = i;
		min_in_set[i] = i;
		cnt[i] = rang[i] = 1;
		par[i] = i;
	}
	for (int i = 0; i < n; ++i) {
		int u;
		scanf("%d", &u); --u;
		if (empt[u] == 0) {
			empt[u] = 1;
			unionset(u, u + 1);	
			printf("%d\n", u + 1);
		}
		else {
			int v = max_in_set[get_set(u)];
			if (v == n) {
				v = max_in_set[get_set(0)];
				empt[v] = 1;
				unionset(v, v + 1);
				printf("%d\n", v + 1);
			}
			else {
				empt[v] = 1;
				unionset(v, v + 1);
				printf("%d\n", v + 1);
			}
		}
	}
}