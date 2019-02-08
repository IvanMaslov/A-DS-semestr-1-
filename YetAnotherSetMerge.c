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

void init(int n) {
	for (int i = 1; i <= n; ++i) {
		min_in_set[i] = max_in_set[i] = i;
		cnt[i] = rang[i] = 1;
		par[i] = i;
	}
}


int min_in_set_subarray[N];
int max_in_set_subarray[N];
int cnt_subarray[N];
int rang_subarray[N];
int par_subarray[N];

int get_set_subarray(int v) {
	if (par_subarray[v] == v)return v;
	return par_subarray[v] = get_set_subarray(par_subarray[v]);
}

void unionset_subarray(int l, int r) {
	l = get_set_subarray(l);
	r = get_set_subarray(r);
	if (l == r)return l;
	if (rang_subarray[l] > rang_subarray[r]) {
		int u = r;
		r = l;
		l = u;
	}
	if (rang_subarray[l] == rang_subarray[r])++rang_subarray[l];
	par_subarray[r] = l;
	min_in_set_subarray[l] = min(min_in_set_subarray[l], min_in_set_subarray[r]);
	max_in_set_subarray[l] = max(max_in_set_subarray[l], max_in_set_subarray[r]);
	cnt_subarray[l] += cnt_subarray[r];
}

void init_subarray(int n) {
	for (int i = 1; i <= n; ++i) {
		min_in_set_subarray[i] = max_in_set_subarray[i] = i;
		cnt_subarray[i] = rang_subarray[i] = 1;
		par_subarray[i] = i;
	}
}

int near(int l, int r) {
	l = get_set_subarray(l);
	r = get_set_subarray(r);
	if (min_in_set_subarray[l] == 1 + max_in_set_subarray[r] || min_in_set_subarray[r] == 1 + max_in_set_subarray[l])
		return 1;
	return 0;
}


int n, q;
void solve() {
	scanf("%d%d", &n, &q);
	init(n);
	init_subarray(n);
	while (q--) {
		int ind, a, b;
		scanf("%d%d%d", &ind, &a, &b);
		if (ind == 1) {
			int A = get_set_subarray(a);
			int B = get_set_subarray(b);
			if (near(A, B)) {
				unionset_subarray(A, B);
			}
			unionset(A, B);
		}
		if (ind == 2) {
			int A = get_set_subarray(a);
			while (1) {
				int aa = max_in_set_subarray[get_set_subarray(a)] + 1;
				if (aa > b)break;
				unionset(A, get_set_subarray(aa));
				unionset_subarray(a, aa);
				a = aa;
			}
		}
		if (ind == 3) {
			if (get_set(get_set_subarray(a)) == get_set(get_set_subarray(b)))
				printf("YES\n");
			else
				printf("NO\n");
		}
	}
}