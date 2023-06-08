#include <stdio.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include <set>
#include <vector>
using namespace std;


typedef pair<char, int> ii;


struct Comp {
	bool operator()(const ii& l, const ii& r) const {
		return l.first < r.first;
	}
};

typedef set<ii, Comp> Set;


struct Trie {
	bool isEnd;
	vector<Trie> postFix;
	Set keySet;

	Trie() {
		isEnd = false;
	}
};


Trie colorTrie;
unordered_map<string, int> nicknameTable;


void makeTrie(string str, Trie* root) {
	Trie* cur = root;
	Set::iterator next;
	int p = 0;
	int key;
	while (str[p] != '\0') {
		next = cur->keySet.find(make_pair(str[p], 0));
		if (next != cur->keySet.end()) {
			cur = &(cur->postFix[(*next).second]);
			p++;
			continue;
		}
		else {
			break;
		}
	}

	while (str[p] != '\0') {
		key = cur->postFix.size();
		cur->postFix.push_back(Trie());
		cur->keySet.insert(make_pair(str[p], key));
		cur = &(cur->postFix.back());
		p++;
	}
	cur->isEnd = true;
}


bool searchTrie(Trie*& cur, int& p, string str) {
	Set::iterator next;

	while (str[p] != '\0') {
		next = cur->keySet.find(make_pair(str[p], 0));
		if (next != cur->keySet.end()) {
			cur = &(cur->postFix[(*next).second]);
			p++;
			if (cur->isEnd) {
				return true;
			}
			continue;
		}
		else {
			return false;
		}
	}
	return false;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int C, N, Q;
	int p;
	string str;
	Trie* colorTriePtr;
	bool flag;

	cin >> C;
	cin >> N;

	for (int i = 0; i < C; i++) {
		cin >> str;
		makeTrie(str, &colorTrie);
	}

	for (int i = 0; i < N; i++) {
		cin >> str;
		nicknameTable.insert(make_pair(str, str.length()));
	}

	cin >> Q;
	for (int i = 0; i < Q; i++) {
		cin >> str;
		flag = false;
		colorTriePtr = &colorTrie;
		p = 0;
		while (searchTrie(colorTriePtr, p, str)) {
			if (nicknameTable.find(str.substr(p)) != nicknameTable.end()) {
				flag = true;
				break;
			}
		}

		if (flag) {
			cout << "Yes\n";
		}
		else {
			cout << "No\n";
		}
	}

	return 0;
}