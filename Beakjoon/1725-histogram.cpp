#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <string.h>
#include <math.h>
#include <functional>
using namespace std;

typedef long long li;
typedef pair<int, pair<int, int>> E;

E* st;
int* arr;

int makest(int idx, int l, int r) {
	int min, temp;
	int m = l + r;
	m /= 2;
	int ll = idx * 2;
	int rr = ll + 1;
	if (l != r) {
		min = makest(ll, l, m);
		temp = makest(rr, m + 1, r);
		if (arr[temp] < arr[min]) {
			min = temp;
		}
	}
	else {
		min = l;
	}

	st[idx].first = min;
	st[idx].second.first = l;
	st[idx].second.second = r;

	return min;
}


int find(int l, int r, int idx = 1) {
	int min = -1, temp = -1;
	int m = l + r;
	int mm = st[idx].second.first + st[idx].second.second;
	mm /= 2;
	m /= 2;
	if (st[idx].second.first < l || st[idx].second.second > r) {
		if (l > mm) {
			min = find(l, r, idx * 2 + 1);
		}
		else if (r <= mm) {
			min = find(l, r, idx * 2);
		}
		else {
			min = find(l, mm, idx * 2);
			temp = find(mm + 1, r, idx * 2 + 1);
			if (arr[temp] < arr[min]) {
				min = temp;
			}
		}
		return min;
	}
	else {
		return st[idx].first;
	}
}


li solve(int l, int r) {
	int min = find(l, r);
	li area = ((li)r - l + 1) * arr[min];
	li temp;
	if (l < min) {
		temp = solve(l, min - 1);
		if (temp > area) {
			area = temp;
		}
	}
	if (r > min) {
		temp = solve(min + 1, r);
		if (temp > area) {
			area = temp;
		}
	}
	return area;
}


int main() {
	int size;
	int lgsize;
	int min;
	li result;

	lgsize = log2(100000) + 2;
	arr = new int[100000];
	st = new E[(int)pow(2, lgsize)];

	scanf("%d", &size);

	for (int i = 0; i < size; i++) {
		scanf("%d", arr + i);
	}
	makest(1, 0, size - 1);
	min = st[1].first;

	result = solve(0, size - 1);
	printf("%lld\n", result);


	return 0;
}

