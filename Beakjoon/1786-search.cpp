#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <algorithm>
#include <iostream>
using namespace std;

typedef vector<int> vi;

vi result;


void makeKMPtable(vi& table, char* pat) {
	int len = strlen(pat);
	int p, c;
	p = 0;
	c = -1;
	table[0] = -1;
	
	while (p < len) {
		while (pat[c] != pat[p] && c >= 0) {
			c = table[c];
		}
		p++; c++;
		table[p] = c;
	}
}

void searchKMP(vi& table, char* str, char* pat) {
	int ls = strlen(str);
	int lp = strlen(pat);

	int p = 0, c = 0;

	while (p < ls) {
		while (pat[c] != str[p] && c >= 0) {
			c = table[c];
		}
		p++; c++;
		if (c == lp) {
			result.push_back(p - c + 1);
			c = table[c];
		}
	}
}


int main() {
	char* str = new char[1000001];
	char* pat = new char[1000001];

	cin.getline(str, 1000001);
	cin.getline(pat, 1000001);

	vi jtable;
	jtable.assign(strlen(pat) + 1, -1);

	makeKMPtable(jtable, pat);
	searchKMP(jtable, str, pat);

	printf("%d\n", result.size());
	for (vi::iterator i = result.begin(); i != result.end(); i++) {
		printf("%d ", *i);
	}
	return 0;
}