#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <string.h>
#include <math.h>
using namespace std;


typedef long long li;
typedef vector<int> vi;


int main() {
	vi A, B, Aremain, Bremain;
	vi leftNums;
	int N, M, num, remainder; 
	int* deleteTime = new int[7];
	memset(deleteTime, -1, 7 * sizeof(int));
	int count = 0;
	int lastingRemainder = 0;
	int maxNum;
	li added = 0;

	scanf("%d %d", &N, &M);

	A.reserve(N);
	Aremain.reserve(N);
	B.reserve(M);
	Bremain.reserve(M);

	for (int i = 0; i < N; i++) {
		scanf("%d", &num);
		remainder = num % 7;
		A.push_back(num);
		Aremain.push_back(remainder);
		deleteTime[Aremain[i]] = 0;
	}

	for (int i = 0; i < M; i++) {
		scanf("%d", &num);
		remainder = num % 7;
		B.push_back(num);
		Bremain.push_back(remainder);
	}

	count = 0;
	bool endFlag = false;
	int underSeven[7] = { 0, 1, 2, 3, 4, 5, 6 };
	for (auto i : Bremain) {
		count++;
		endFlag = true;
		for (int k = 0; k < 7; k++) {
			if (deleteTime[k] != 0) {
				continue;
			}
			endFlag = false;
			underSeven[k] = (underSeven[k] + i) % 7;
			if (underSeven[k] == 0) {
				deleteTime[k] = count;
			}
		}
		if (endFlag) {
			break;
		}
	}

	endFlag = true;
	for (int k = 0; k < 7; k++) {
		if (deleteTime[k] == 0) {
			endFlag = false;
			break;
		}
	}

	if (endFlag) {
		maxNum = 0;
		for (int i = 0; i < 7; i++) {
			if (maxNum < deleteTime[i]) {
				maxNum = deleteTime[i];
				lastingRemainder = i;
			}
		}

		remainder = lastingRemainder;
		added = 0;
		for (int i = 0; i < M; i++) {
			if ((remainder + Bremain[i]) % 7 != 0) {
				remainder = (remainder + Bremain[i]) % 7;
				added += B[i];
				added %= 1000000007;
			}
		}

		for (int i = 0; i < N; i++) {
			if (Aremain[i] == lastingRemainder) {
				leftNums.push_back((A[i] + added) % 1000000007);
			}
		}
	}
	else {
		added = 0;
		for (auto i : B) {
			added += i;
			added %= 1000000007;
		}

		for (int i = 0; i < N; i++) {
			if (deleteTime[Aremain[i]] == 0) {
				leftNums.push_back((A[i] + added) % 1000000007);
			}
		}
	}

	

	printf("%d\n", leftNums.size());
	for (auto i : leftNums) {
		printf("%d ", i);
	}

	return 0;
}