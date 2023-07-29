#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <math.h>
#include <vector>
using namespace std;


typedef long long li;
typedef vector<int> vi;


struct Range {
	li goodNumIdx;
	li rightNumCount, leftNumCount;
	int size;
	int leftNum, rightNum;
	int leftBound, rightBound;
	bool isLeft;

	Range(int lbound, int rbound) {
		leftBound = lbound;
		rightBound = rbound;
		size = rbound - lbound - 1;
		isLeft = true;
		leftNumCount = 0;
		rightNumCount = size - 1;

		leftNum = lbound + 1;
		rightNum = rbound - 1;

		goodNumIdx = leftNumCount + rightNumCount + (leftNumCount * rightNumCount);
	}

	void pop() {
		if (isLeft) {
			isLeft = false;
			size--;
			leftNum++;
		}
		else {
			isLeft = true;
			rightNum--;
			size--;
			leftNumCount++;
			rightNumCount--;
			goodNumIdx = leftNumCount + rightNumCount + (leftNumCount * rightNumCount);
		}
	}

	int top() {
		if (isLeft) return leftNum;
		else return rightNum;
	}

	int compare(const Range& op) {
		if (size == 0) {
			return 1;
		}
		else if (op.size == 0) {
			return -1;
		}

		if (goodNumIdx < op.goodNumIdx) {
			return -1;
		}
		else if (goodNumIdx == op.goodNumIdx) {
			if (leftBound < op.leftBound) {
				return -1;
			}
			else {
				return 1;
			}
		}
		else {
			return 1;
		}
	}
};


int main() {

	Range** ranges;
	Range* topRange;
	vi zeroIdxArr;
	int L;
	int* arr;
	int N;
	int num;
	int printedNumCount;

	scanf("%d", &L);
	ranges = new Range * [L];
	arr = new int[L];
	for (int i = 0; i < L; i++) {
		scanf("%d", &num);
		arr[i] = num;
	}

	sort(arr, arr + L);
	ranges[0] = new Range(0, arr[0]);
	if (ranges[0]->goodNumIdx == 0 && ranges[0]->size > 0) {
		zeroIdxArr.push_back(ranges[0]->top());
		ranges[0]->pop();
	}
	zeroIdxArr.push_back(arr[0]);
	for (int i = 1; i < L; i++) {
		ranges[i] = new Range(arr[i - 1], arr[i]);
		if (ranges[i]->goodNumIdx == 0 && ranges[i]->size > 0) {
			zeroIdxArr.push_back(ranges[i]->top());
			ranges[i]->pop();
		}
		zeroIdxArr.push_back(arr[i]);
	}


	scanf("%d", &N);
	printedNumCount = 0;
	for (auto i : zeroIdxArr) {
		printf("%d ", i);
		printedNumCount++;
		if (printedNumCount == N) {
			break;
		}
	}

	for (; printedNumCount < N; printedNumCount++) {
		topRange = ranges[0];
		for (int i = 1; i < L; i++) {
			if (topRange->compare(*ranges[i]) == 1) {
				topRange = ranges[i];
			}
		}

		if (topRange->size == 0) {
			break;
		}
		else {
			printf("%d ", topRange->top());
			topRange->pop();
		}
	}

	num = arr[L - 1];
	for (; printedNumCount < N; printedNumCount++) {
		num++;
		printf("%d ", num);
	}

	return 0;
}