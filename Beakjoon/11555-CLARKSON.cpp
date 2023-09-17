#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

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
		for (int i = 0; i < len; i++) {
			if (rvt[i] - 1 < 0) {
				lcp[rvt[i]] = 0;
				r = 0;
				continue;
			}
			while (str[i + r] == str[SA[rvt[i] - 1] + r] && str[i + r] != '$') {
				r++;
			}
			lcp[rvt[i]] = r;
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

typedef struct Node {
	int left, value, right;
	Node() {}
	Node(int l, int v, int r) {
		left = l;
		value = v;
		right = r;
	}
} Node;


bool check(const vi& cs, int len) {
	set<int> clear;
	clear.insert(cs.size());
	for (int i = cs.size() - 1; i >= 0; i--) {
		auto lbound = clear.lower_bound(i + len);
		if (lbound != clear.end() && *lbound <= i + cs[i]) 
			clear.insert(i);
	}
	return *clear.begin() == 0;
}


int main() {
	//freopen("input.txt", "r", stdin);
	SuffixArray sa;
	char* str = new char[200003];
	int N, L;
	scanf("%s", str);
	N = strlen(str);
	str[N] = '$';
	scanf("%s", str + N + 1);
	L = strlen(str);
	str[L] = '$';
	str[++L] = 0;
	sa.construct(str);

	//for (int i = 0; i < L; i++) {
	//	printf("%3d : %s %d / %d \n", i, str + sa.SA[i], sa.SA[i], sa.lcp[i]);
	//}

	vi cs(N);
	int leftlen = -1, rightlen = -1;
	int befo = 0;
	for (int i = 2; i < L; i++) {
		if (befo == 0) {
			if (sa.SA[i] < N) {
				befo = i;
				leftlen = sa.lcp[i];
				cs[sa.SA[i]] = leftlen;
			}
		}
		else {
			leftlen = min(leftlen, sa.lcp[i]);
			if (sa.SA[i] < N) {
				cs[sa.SA[i]] = leftlen;
			}
			else {
				rightlen = sa.lcp[i];
				for (int index = i - 1; index >= befo; index--) {
					cs[sa.SA[index]] = max(cs[sa.SA[index]], rightlen);
					rightlen = min(sa.lcp[index], rightlen);
				}
				befo = 0;
			}
		}
	}

	//str[N] = 0;
	//printf("\n%s\n", str);
	//for (int i = 0; i < N; i++) {
	//	printf("%d", cs[i]);
	//}
	//printf("\n");
	
	int l = 1, r = N, m, ans = -1;
	bool pass = false;

	for (int i = 0; i < N; i++) {
		if (cs[i] == 0) {
			r = -1;
			break;
		}
	}

	while (l <= r) {
		m = (l + r)/2;
		pass = check(cs, m);
		if (pass) {
			ans = m;
			l = m + 1;
		}
		else {
			r = m - 1;
		}
	}

	printf("%d", ans);
	return 0;
}