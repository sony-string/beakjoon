#include <bits/stdc++.h>
using namespace std;

typedef struct TrieNode {
	char ch;
	int depth;
	int output;
	TrieNode* go[2];
	TrieNode* fail;
	TrieNode(char c, int d) : ch(c), depth(d), output(-1), fail(NULL) { go[0] = NULL; go[1] = NULL; }
} Node;

vector<int> unionFind;
int unioncnt = 0;

typedef struct Trie {
	Node* root;
	void construct(vector<char*>& strs) {
		unionFind.assign(strs.size(), -1);
		root = new Node(0, 0);
		for (int k = 0; k < strs.size(); k++) {
			char* str = strs[k];
			Node* node = root;
			for (int i = 0; str[i]; i++) {
				int idx = str[i] == 'o' ? 1 : 0;
				if (node->go[idx])
					node = node->go[idx];
				else
					node = node->go[idx] = new Node(str[i], node->depth);
			}
			if (node->output == -1) {
				node->output = k;
				unionFind[k] = ++unioncnt;
			}
			else
				unionFind[k] = unionFind[node->output];
		}
	}

	void ahoCorasick(vector<char*>& strs) {
		construct(strs);
		queue<Node*> q;
		for (int i = 0; i < 2; i++) {
			if (root->go[i]) {
				root->go[i]->fail = root;
				q.push(root->go[i]);
			}
		}
		while (!q.empty()) {
			Node* node = q.front();
			Node* fail = root;
			q.pop();
			Node* next;
			for (int i = 0; i < 2; i++) {
				if (!node->go[i])
					continue;
				next = node->go[i];
				fail = node->fail;
				while (fail && !fail->go[i]) fail = fail->fail;
				if (!fail)
					fail = root;
				else
					fail = fail->go[i];
				next->fail = fail;
				q.push(next);
			}
		}
	}
} Trie;

vector<int> table;
void prekmp() {
	int len = unionFind.size();
	int j = -1;
	table.assign(len + 1, 0);
	table[0] = -1;
	for (int i = 0; i < len; i++) {
		while (j != -1 && unionFind[j] != unionFind[i]) j = table[j];
		j++;
		table[i + 1] = j;
	}
}

int countMatch(vector<int>& t) {
	int lent = t.size();
	int lenpat = table.size() - 1;
	int j = 0;
	int cnt = 0;
	for (int i = 0; i < lent; i++) {
		if (j + lenpat > lent)
			break;
		while (j != -1 && (t[i] == -1 || unionFind[j] != unionFind[t[i]])) j = table[j];
		j++;
		if (j == lenpat) {
			cnt++;
			j = table[j];
		}
	}
	return cnt;
}

void matchAhoCorasick(vector<int>* lineMatch, Trie& trie, char** grid, int hm, int wm) {
	Node* node = trie.root;
	for (int l = 0; l < hm; l++) {
		char* str = grid[l];
		node = trie.root;
		for (int i = 0; i < wm; i++) {
			int idx = str[i] == 'o' ? 1 : 0;
			while (node && !node->go[idx]) node = node->fail;
			if (node) {
				node = node->go[idx];
				if (node->output != -1) {
					lineMatch[i][l] = node->output;
					node = node->fail;
				}
			}
			else {
				node = trie.root;
			}
		}
	}
}


int main() {
	int hp, wp, hm, wm;
	scanf("%d %d %d %d", &hp, &wp, &hm, &wm);
	vector<char*> strs; 
	strs.assign(hp, 0);
	for (int i = 0; i < hp; i++) {
		strs[i] = new char[wp + 1];
		scanf("%s", strs[i]);
	}
	Trie trie;
	trie.ahoCorasick(strs);

	char** grid;
	grid = new char* [hm];
	for (int i = 0; i < hm; i++) {
		grid[i] = new char[wm + 1];
		scanf("%s", grid[i]);
	}

	vector<int>* lineMatch = new vector<int>[wm];
	for (int i = 0; i < wm; i++) {
		lineMatch[i].assign(hm, -1);
	}
	matchAhoCorasick(lineMatch, trie, grid, hm, wm);
	prekmp();
	int cnt = 0;
	for (int i = 0; i < wm; i++) {
		cnt += countMatch(lineMatch[i]);
	}
	printf("%d", cnt);
	return 0;
}