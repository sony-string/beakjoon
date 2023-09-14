#include <bits/stdc++.h>
using namespace std;


struct SuffixArray {
	int len;
	char* str;
	int* RA, * tempRA;
	int* SA, * tempSA;
	int* cnt;
	int* lcp;
	
	void countingSort(int k) {
		int i, sum, maxi = max(300, len);
		memset(cnt, 0, sizeof(int) * max(300, len));
		for (i = 0; i < len; i++) {
			cnt[i + k < len ? RA[i + k] : 0]++;
		}
		sum = 0;
		for (i = 0; i < maxi; i++) {
			sum += cnt[i];
			cnt[i] = sum;
		}
		for (i = len - 1; i >= 0; i--) {
			tempSA[--cnt[SA[i] + k < len ? RA[SA[i] + k] : 0]] = SA[i];
		}
		memcpy(SA, tempSA, sizeof(int) * len);
	}

	void makelcp() {
		int r = 0;
		int* rvt = new int[len];
		lcp = new int[len];
		for (int i = 0; i < len; i++) {
			rvt[SA[i]] = i;
		}
		lcp[0] = -1;
		for (int i = 0; i < len - 1; i++) {
			while (str[i + r] == str[SA[rvt[i] - 1] + r]) {
				r++;
			}
			lcp[rvt[SA[i]]] = r;
			if (r) r--;
		}
	}

	void construct(char* str) {
		this->str = str;
		len = strlen(str);
		cnt = new int[max(300, len)];
		RA = new int[len];
		tempRA = new int[len];
		SA = new int[len];
		tempSA = new int[len];
		int r;
		for (int i = 0; i < len; i++) {
			RA[i] = str[i];
		}
		for (int i = 0; i < len; i++) {
			SA[i] = i;
		}
		for (int k = 1; k < len; k <<= 1) {
			countingSort(k);
			countingSort(0);
			r = 0;
			tempRA[SA[0]] = r;
			for (int i = 1; i < len; i++) {
				if (RA[SA[i]] != RA[SA[i - 1]] ||
					(SA[i] + k < len ? RA[SA[i] + k] : -1) != (SA[i - 1] + k < len ? RA[SA[i - 1] + k] : -1)) {
						r++;
				}
				tempRA[SA[i]] = r;
			}
			memcpy(RA, tempRA, sizeof(int) * len);
			if (RA[SA[len - 1]] == len - 1) {
				break;
			}
		}
		makelcp();
	}
};


int main() {
	SuffixArray sa;
	char* str;
	int N;
	scanf("%d", &N);
	str = new char[N + 2];
	scanf("%s", str);
	str[N] = '$'; str[N + 1] = 0;
	sa.construct(str);

	int ans = 0;
	for (int i = 0; i < N + 1; i++) {
		ans = max(ans, sa.lcp[i]);
	}
	printf("%d", ans);

	return 0;
}