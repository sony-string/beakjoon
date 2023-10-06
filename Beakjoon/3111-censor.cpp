#include <bits/stdc++.h>
using namespace std;

vector<int> fail;
vector<int> rfail;
vector<int> table;
vector<int> rtable;

char* prekmp(char* str) {
	int len = strlen(str);
	fail.assign(len + 1, 0);
	fail[0] = -1;
	int j = -1;
	for (int i = 0; i < len; i++) {
		while (j != -1 && str[j] != str[i]) j = fail[j];
		j++;
		fail[i + 1] = j;
	}

	char* rstr = new char[len + 1];
	for (int i = 0; i < len; i++) {
		rstr[i] = str[len - 1 - i];
	}
	rstr[len] = 0;
	rfail.assign(len + 1, 0);
	rfail[0] = -1;
	j = -1;
	for (int i = 0; i < len; i++) {
		while (j != -1 && rstr[j] != rstr[i]) j = rfail[j];
		j++;
		rfail[i + 1] = j;
	}
	return rstr;
}

void solve(char* t, char* pat, char* rpat) {
	int len = strlen(t);
	int end = fail.size() - 1;
	table.assign(len + 1, 0);
	rtable.assign(len + 1, 0);

	list<pair<char, int>> tl;
	for (int i = 0; i < len; i++) {
		tl.emplace_back(t[i], i);
	}
	auto l = tl.begin(), r = tl.end();
	r--;
	int j = 0;
	
	bool go = false;
	bool prefixMatch;
	bool exist;
	while (!go && l != tl.end()) {
		go = false;
		exist = false;
		for (; l != tl.end();) {
			if (l == r) go = true;
			j = table[(*l).second];
			while (j != -1 && (*l).first != pat[j]) j = fail[j];
			j++;
			if (j == end) {
				auto until = l;
				exist = true;
				prefixMatch = false;
				for (int i = 0; i < end; i++) {
					if (i == end - 1) {
						j = table[(*until).second];
					}
					if (until != tl.begin()) {
						l = --until;
						tl.erase(++until);
						until = l;
					}
					else {
						prefixMatch = true;
						tl.erase(until);
						l = tl.begin();
					}
				}
			}
			if (exist) {
				if (!prefixMatch) l++;
				if (l == tl.end()) break;
			}
			else if (++l == tl.end()) break;
			table[(*l).second] = j;
			if (exist && !go) break;
		}

		if (!exist || go) break;
		exist = false;
		for (;;) {
			if (r == l) go = true;
			j = rtable[(*r).second];
			while (j != -1 && (*r).first != rpat[j]) j = rfail[j];
			j++;
			if (j == end) {
				auto until = r;
				exist = true;
				for (int i = 0; i < end; i++) {
					if (i == end - 1) {
						j = rtable[(*until).second];
					}
					r++;
					tl.erase(until);
					until = r;
				}
			}
			if (r == tl.begin()) break;
			r--;
			rtable[(*r).second] = j;
			if (exist && !go) break;
		}
	}

	for (auto& c : tl) {
		printf("%c", c.first);
	}
}


int main() {
	char* pat, * rpat;
	pat = new char[26];
	char* t = new char[300'001];
	scanf("%s %s", pat, t);
	rpat = prekmp(pat);
	solve(t, pat, rpat);
	return 0;
}