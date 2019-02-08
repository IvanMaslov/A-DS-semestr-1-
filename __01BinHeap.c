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

//vert "class":
const int _BASE_LIST_CHILD_SIZE_ = 2;
struct vert {
	int index;
	int value;
	int list_child_size;
	struct vert** list_child;
	struct vert* pred;
};

//

//vert "constructors":

void initVert1(struct vert* arg) {
	assert(arg != 0);
	arg->index = 0;
	arg->value = 0;
	arg->pred = 0;
	arg->list_child_size = 0;
	arg->list_child = 0;
}

void initVert2(struct vert* arg, int _index) {
	assert(arg != 0);
	arg->index = _index;
	arg->value = 0;
	arg->pred = 0;
	arg->list_child_size = 0;
	arg->list_child = 0;
}

void initVert3(struct vert* arg, int _index, int _value) {
	assert(arg != 0);
	arg->index = _index;
	arg->value = _value;
	arg->pred = 0;
	arg->list_child_size = 0;
	arg->list_child = 0;
}

//

//vert "methods":

void rebuildVert(struct vert* arg) {
	assert(arg != 0);
	if (arg->list_child == 0) {
		arg->list_child = (struct vert**)malloc(_BASE_LIST_CHILD_SIZE_ * sizeof(struct vert*));
		arg->root_capacity = _BASE_LIST_CHILD_SIZE_;
		arg->root_size = 0;
		return;
	}
	if (arg->root_capacity == arg->root_size) {
		struct vert** new_root = (struct vert**)malloc(arg->root_capacity * 2 * sizeof(struct vert*));
		memcpy(new_root, arg->root, arg->root_size * sizeof(struct vert*));
		free(arg->root);
		arg->root = new_root;
		arg->root_capacity *= 2;
	}
}

struct vert* mergeVert(struct vert* lhs, struct vert* rhs) {
	assert(lhs != 0);
	assert(rhs != 0);

	if (lhs->value > rhs->value || lhs->value == rhs->value && lhs->index > rhs->index) {
		struct vert* ind = lhs;
		lhs = rhs;
		rhs = ind;
	}

	rhs->pred = lhs;
	lhs->list_child[lhs->list_child_size++] = rhs;

	return lhs;
}



//



//heaps "class"
const int _BASE_ROOT_SIZE_ = 10;
struct heaps {
	int root_size;
	int root_capacity;
	struct vert** root;
};

void rebuildHeaps(struct heaps*);
//

//heaps "constructors"

void initHeaps1(struct heaps* arg) {
	assert(arg != 0);
	rebuildHeaps(arg);
}

//

//heaps "methods"

void rebuildHeaps(struct heaps* arg) {
	assert(arg != 0);
	if (arg->root == 0) {
		arg->root = (struct vert**)malloc(_BASE_ROOT_SIZE_ * sizeof(struct vert*));
		arg->root_capacity = _BASE_ROOT_SIZE_;
		arg->root_size = 0;
		return;
	}
	if (arg->root_capacity == arg->root_size) {
		struct vert** new_root = (struct vert**)malloc(arg->root_capacity * 2 * sizeof(struct vert*));
		memcpy(new_root, arg->root, arg->root_size * sizeof(struct vert*));
		free(arg->root);
		arg->root = new_root;
		arg->root_capacity *= 2;
	}
}

//

struct vert* fnd_by_index[N];

void solve() {
	int n, m;
	scanf("%d%d", &n, &m);
		
}