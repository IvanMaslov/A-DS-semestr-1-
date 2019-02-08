#define _CRT_SECURE_NO_WARNINGS

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <assert.h>
//that's all

void solve();

void assert(int v) {
	if (v == 0) {
		while (1);
	}
}

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


struct vert* fnd_by_index[N];


//vert "class":

struct vert {
	struct vert *pred, *child, *leftBro, *rightBro;
	int value;
	int index;
	size_t some_pointer;
};

//

//vert "constructors":

void initVert0(struct vert* arg) {
	assert(arg != 0);
	arg->pred = arg->child = 0;
	arg->leftBro = arg->rightBro = arg;
	arg->index = 0;
	arg->value = 0;
	arg->some_pointer = 0;
}

void initVert1(struct vert* arg, int _index) {
	initVert0(arg);
	arg->index = _index;
}

void initVert2(struct vert* arg, int _index, int _value) {
	initVert1(arg, _index);
	arg->value = _value;
}

//

//vert "methods":

struct vert* mergeVert(struct vert* lhs, struct vert* rhs) {
	if (lhs == 0)return rhs;
	if (rhs == 0)return lhs;

	if (lhs->value > rhs->value || lhs->value == rhs->value && lhs->index > rhs->index || rhs->index == -1) {
		struct vert* tmp = lhs;
		lhs = rhs;
		rhs = tmp;
	}

	rhs->pred = lhs;
	if (lhs->child == 0)
		lhs->child = rhs;
	else {
		struct vert* L = lhs->child->leftBro;
		struct vert* R = lhs->child;
		R->leftBro = rhs;
		L->rightBro = rhs;
		rhs->leftBro = L;
		rhs->rightBro = R;
	}
	return lhs;
}

void swps(struct vert* lhs, struct vert* rhs) {
	int tmp = lhs->value;
	lhs->value = rhs->value;
	rhs->value = tmp;

	tmp = lhs->index;
	lhs->index = rhs->index;
	rhs->index = tmp;
	assert(lhs->index >= 0);
	assert(rhs->index >= 0);
	fnd_by_index[lhs->index] = lhs;
	fnd_by_index[rhs->index] = rhs;
}

struct vert* sft(struct vert* arg) {
	while (1) {
		struct vert* p = arg->pred;
		if (p == 0)break;
		if (p->value > arg->value ||
			arg->value == p->value && p->index > arg->index ||
			arg->index == 0) {
			swps(arg, p);
			arg = p;
		}
		else break;
	}
	while (1) {
		struct vert* vt = arg->child;
		struct vert* iter = vt;
		struct vert* mn = arg;
		if (vt == 0)break;

		do {
			if (mn->value > iter->value ||
				mn->value == iter->value && iter->index < mn->index ||
				iter->index == 0)
				mn = iter;

			iter = iter->leftBro;
		} while (iter != vt);

		if (mn == arg)break;
		swps(arg, mn);
		arg = mn;
	}
	return arg;
}

//



//heaps "class"

const int size_ = 30;
struct heaps {
	struct vert* root[30];
};

//

//heaps "constructors"

void initHeaps0(struct heaps* arg) {
	assert(arg != 0);
	memset(arg->root, 0, sizeof(arg->root));
}

//

//heaps "methods"

struct heaps* mergeHeaps(struct heaps* lhs, struct heaps* rhs) {
	if (!lhs)return rhs;
	if (!rhs)return lhs;
	struct vert* perenos = 0;
	for (int i = 0; i < size_; ++i) {
		if (lhs->root[i] != 0 && rhs->root[i] != 0) {
			if (perenos != 0) {
				perenos = mergeVert(perenos, rhs->root[i]);
			}
			else {
				perenos = mergeVert(lhs->root[i], rhs->root[i]);
				lhs->root[i] = 0;
			}
		}
		else {
			lhs->root[i] = mergeVert(lhs->root[i], rhs->root[i]);
			if (perenos != 0) {
				if (lhs->root[i] == 0) {
					lhs->root[i] = perenos;
					perenos = 0;
				}
				else {
					perenos = mergeVert(perenos, lhs->root[i]);
					lhs->root[i] = 0;
				}
			}
		}
		if (lhs->root[i] != 0) {
			lhs->root[i]->some_pointer = lhs;
			lhs->root[i]->leftBro = lhs->root[i]->rightBro = lhs->root[i];
			lhs->root[i]->pred = 0;
		}
		rhs->root[i] = 0;
	}
	return lhs;
}

void insert_in_heaps(struct heaps* arg, struct vert* v) {
	assert(arg != 0);
	assert(v != 0);
	struct heaps* t = malloc(sizeof(struct heaps));
	initHeaps0(t);
	t->root[0] = v;
	arg = mergeHeaps(arg, t);
	free(t);
}

struct vert* get_min_heaps(struct heaps* arg) {
	assert(arg != 0);
	int ans = -1;
	for (int i = 0; i < size_; ++i)
		if (arg->root[i] != 0 && (ans == -1 || arg->root[ans]->value > arg->root[i]->value))
			ans = i;
	assert(ans >= 0);
	return arg->root[ans];
}

void delete_vert(struct vert* v) {
	assert(v != 0);

	v->index = 0;
	v = sft(v);

	struct heaps* arg = v->some_pointer;

	int ans = -1;
	for (int i = 0; i < size_; ++i)
		if (arg->root[i] != 0 && arg->root[i]->index == 0)
			ans = i;

	struct heaps* t = malloc(sizeof(struct heaps));
	initHeaps0(t);

	struct vert* vt = arg->root[ans]->child;
	struct vert* iter = vt;
	if (vt == 0) {
		free(arg->root[ans]);
		arg->root[ans] = 0;
		return ans;
	}

	int iterInt = 0;
	do {
		t->root[iterInt++] = iter;
		iter = iter->leftBro;
	} while (iter != vt);

	for (int j = 0; j < iterInt; ++j) {
		t->root[j]->leftBro = t->root[j]->rightBro = t->root[j];
		t->root[j]->pred = 0;
		t->root[j]->some_pointer = t;
	}

	free(arg->root[ans]);
	arg->root[ans] = 0;

	arg = mergeHeaps(arg, t);
	free(t);
}


void extract_min_heaps(struct heaps* arg) {
	assert(arg != 0);
	delete_vert(get_min_heaps(arg));
}


//

struct heaps* h[1001];
void solve() {
	int n, m;
	int addcnt = 0;
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; ++i) {
		h[i] = malloc(sizeof(struct heaps));
		initHeaps0(h[i]);
	}
	for (int i = 1; i <= m; ++i) {
		int ind = 0;
		scanf("%d", &ind);
		if (ind == 0) {
			int v, a;
			++addcnt;
			scanf("%d%d", &v, &a);
			struct vert *t = malloc(sizeof(struct vert));
			initVert2(t, addcnt, a);
			fnd_by_index[addcnt] = t;
			insert_in_heaps(h[v], t);
		}
		if (ind == 1) {
			int a, b;
			scanf("%d%d", &a, &b);
			h[b] = mergeHeaps(h[b], h[a]);
			initHeaps0(h[a]);
		}
		if (ind == 2) {
			int a;
			scanf("%d", &a);
			delete_vert(fnd_by_index[a]);
		}
		if (ind == 3) {
			int a, v;
			scanf("%d%d", &a, &v);
			fnd_by_index[a]->value = v;
			fnd_by_index[a] = sft(fnd_by_index[a]);
		}
		if (ind == 4) {
			int a;
			scanf("%d", &a);
			printf("%d\n", get_min_heaps(h[a])->value);
		}
		if (ind == 5) {
			int a;
			scanf("%d", &a);
			extract_min_heaps(h[a]);
		}
	}
}
