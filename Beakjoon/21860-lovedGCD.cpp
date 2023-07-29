#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
using namespace std;

struct Segnode {
	int l, r;
	int gcd;
};

int uclidGCD(int a, int b) {
	if (b == 0)
		return a;
	else 
		return uclidGCD(b, a % b);
}

struct Segtree {
	int size;
	Segnode* segtree;

	void init(int size) {
		segtree = new Segnode[(int)pow(2, (int)log2(size) + 2) + 1];
		this->size = size;
	}

	void makeSegtree(int* arr, int cur, int lbound, int rbound);
	int getRangeGCD(int cur, int lbound, int rbound);
};


void Segtree::makeSegtree(int* arr, int cur, int lbound, int rbound) {
	int l = cur * 2;
	int r = l + 1;
	int mbound = lbound + rbound;
	if (mbound % 2 == 1) {
		mbound /= 2;
		mbound += 1;
	}
	else {
		mbound /= 2;
	}
	segtree[cur].l = lbound;
	segtree[cur].r = rbound;

	if (lbound == rbound) {
		segtree[cur].gcd = arr[lbound];
	}
	else {
		makeSegtree(arr, l, lbound, mbound - 1);
		makeSegtree(arr, r, mbound, rbound);
		segtree[cur].gcd = uclidGCD(segtree[l].gcd, segtree[r].gcd);
	}
}

int Segtree::getRangeGCD(int cur, int lbound, int rbound) {
	int mbound = segtree[cur].l + segtree[cur].r;
	if (mbound % 2 == 1) {
		mbound /= 2;
		mbound += 1;
	}
	else {
		mbound /= 2;
	}
	int l = cur * 2;
	int r = l + 1;

	if (segtree[cur].l == lbound && segtree[cur].r == rbound) {
		return segtree[cur].gcd;
	}
	else if (rbound < mbound) {
		return getRangeGCD(l, lbound, rbound);
	}
	else if (lbound >= mbound) {
		return getRangeGCD(r, lbound, rbound);
	}
	else {
		return uclidGCD(getRangeGCD(l, lbound, mbound - 1), getRangeGCD(r, mbound, rbound));
	}
}

Segtree sT;

int solve(int* arr, int l, int r, int sum) {
	int m = l + r;
	if (m % 2 == 1) {
		m /= 2;
		m += 1;
	}
	else {
		m /= 2;
	}

	if (l == r) {
		return sum + arr[l];
	}
	else {
		return max(solve(arr, l, m - 1, sum + sT.getRangeGCD(1, m, r)),
			solve(arr, m, r, sum + sT.getRangeGCD(1, l, m - 1)));
	}
}


int main() {
	int* arr;
	int arrSize;
	int result;

	scanf("%d", &arrSize);
	sT.init(arrSize);
	arr = new int[arrSize];

	for (int i = 0; i < arrSize; i++) {
		scanf("%d", arr + i);
	}
	sT.makeSegtree(arr, 1, 0, arrSize - 1);
	result = solve(arr, 0, arrSize - 1, 0);

	printf("%d", result);
	return 0;
}