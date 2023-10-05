#include <bits/stdc++.h>
using namespace std;

typedef struct TrieNode {
	char ch;
	bool output;
	int degree;
	int depth;
	TrieNode* go[26];
	TrieNode(char c, int d) : ch(c), output(false), degree(0), depth(d) {
		memset(go, 0, sizeof(TrieNode * [26]));
	}
} Node;


typedef struct Trie {
	Node* root;
	Trie() { root = new Node(0, 0); }
	void construct(vector<char*>& strs, int n) {
		for (int k = 0; k < n; k++) {
			const auto& str = strs[k];
			int len = strlen(str);
			Node* cur = root;
			for (int i = 0; i < len; i++) {
				if (cur->go[str[i] - 'a'])
					cur = cur->go[str[i] - 'a'];
				else {
					cur->degree++;
					cur = cur->go[str[i] - 'a'] = new Node(str[i], cur->depth + 1);
				}
			}
			cur->output = true;
		}
	}

	~Trie() {
		queue<Node*> q;
		q.push(root);
		Node* node;
		while (!q.empty()) {
			node = q.front();
			q.pop();
			for (int i = 0; i < 26; i++) {
				if (node->go[i])
					q.push(node->go[i]);
			}
			delete(node);
		}
	}
} Trie;

int solve(Trie& trie, vector<char*>& strs, int n) {
	trie.construct(strs, n);
	int cnt = 0;
	Node* cur;
	for (int i = 0; i < n; i++) {
		char* str = strs[i];
		int k = 0;
		cur = trie.root;
		while (str[k]) {
			cur = cur->go[str[k++] - 'a'];
			cnt++;
			while (cur->degree == 1 && !cur->output) {
				cur = cur->go[str[k++] - 'a'];
				if (!str[k])
					break;
			}
		}
	}
	return cnt;
}


int main() {
	int N;
	vector<char*> strs;
	Trie* trie;
	strs.assign(100'000, 0);
	for (int i = 0; i < 100'000; i++) {
		strs[i] = new char[81];
	}
	while (scanf("%d", &N) != EOF) {
		trie = new Trie;
		for (int i = 0; i < N; i++) {
			scanf("%s", strs[i]);
		}
		printf("%.2lf\n", round(100 * ((double)solve(*trie, strs, N) / N)) / 100);
		delete(trie);
	}
	return 0;
}
