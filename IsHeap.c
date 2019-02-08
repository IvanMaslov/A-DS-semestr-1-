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

int a[N];
int n;
void solve() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", a + i);
	for (int i = 0; i < n; ++i) {
		if (i * 2 + 1 < n && a[i] > a[i * 2 + 1] || i * 2 + 2 < n && a[i] > a[i * 2 + 2]) {
			printf("NO\n");
			return;
		}
	}
	printf("YES\n");
}