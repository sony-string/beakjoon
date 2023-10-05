#include <bits/stdc++.h>
using namespace std;

typedef struct TrieNode {
	char ch;
	bool output;
	int depth;
	TrieNode* go[26];
	TrieNode* fail;
	TrieNode* postfixOutput;
	TrieNode(char c, int d) : ch(c), output(false), fail(NULL), depth(d), postfixOutput(NULL) {
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
				else
					cur = cur->go[str[i] - 'a'] = new Node(str[i], cur->depth + 1);
			}
			cur->output = true;
		}
	}

	void ahoCorasick(vector<char*>& strs, int n) {
		construct(strs, n);
		queue<Node*> q;
		for (int i = 0; i < 26; i++) {
			if (root->go[i]) {
				root->go[i]->fail = root;
				q.push(root->go[i]);
			}
		}
		while (!q.empty()) {
			Node* node = q.front();
			Node* next;
			Node* fail;
			q.pop();
			for (int i = 0; i < 26; i++) {
				if (!node->go[i])
					continue;
				next = node->go[i];
				q.push(next);
				fail = node->fail;
				while (fail) {
					if (fail->go[i]) {
						fail = fail->go[i];
						break;
					}
					else
						fail = fail->fail;
				}
				if (!fail)
					fail = root;
				next->fail = fail;
				if (next->fail->output)
					next->postfixOutput = fail;
				else
					next->postfixOutput = fail->postfixOutput;
			}
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

bool match(Trie& trie, char* str) {
	Node* node = trie.root;
	for (int i = 0; str[i]; i++) {
		while (node && !node->go[str[i] - 'a']) {
			node = node->fail;
		}
		if (node) {
			node = node->go[str[i] - 'a'];
			if (node->output || node->postfixOutput)
				return true;
		}
		else
			node = trie.root;
	}
	return false;
}

void solve(vector<char*>& strs) {
	Trie trie;
	trie.ahoCorasick(strs, strs.size());
	int Q;
	char* str = new char[10001];
	scanf("%d", &Q);

	for (int i = 0; i < Q; i++) {
		scanf("%s", str);
		if (match(trie, str))
			printf("YES\n");
		else
			printf("NO\n");
	}
}


int main() {
	int N;
	vector<char*> strs;
	scanf("%d", &N);
	strs.assign(N, 0);
	for (int i = 0; i < N; i++) {
		strs[i] = new char[101];
		scanf("%s", strs[i]);
	}
	solve(strs);
	
	return 0;
}