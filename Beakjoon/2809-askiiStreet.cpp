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
		memset(go, 0, sizeof(TrieNode*[26]));
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

vector<int> table;
void match(const Trie& trie, char* str) {
	int len = table.size();
	Node* cur = trie.root;
	for (int i = 0; i < len; i++) {
		while (cur && !cur->go[str[i] - 'a']) {
			cur = cur->fail;
		}
		if (cur) {
			cur = cur->go[str[i] - 'a'];
			if (cur->output)
				table[i - cur->depth + 1] = max(table[i - cur->depth + 1], cur->depth);
			else if (cur->postfixOutput)
				table[i - cur->postfixOutput->depth + 1] = 
				max(table[i - cur->postfixOutput->depth + 1], cur->postfixOutput->depth);

		}
		else
			cur = trie.root;
	}
}

int main() {
	//freopen("input.txt", "r", stdin);
	int N, M, cnt;
	char* str;
	vector<char*> strs;
	Trie* trie;
	strs.assign(500, 0);
	for (int i = 0; i < 500; i++) {
		strs[i] = new char[5001];
	}

	scanf("%d", &N);
	str = new char[N];
	table.assign(N, 0);
	scanf("%s", str);
	scanf("%d", &M);
	cnt = 0;
	for (int i = 0; i < M; i++) {
		scanf("%s", strs[cnt++]);
		if (cnt == 500) {
			trie = new Trie;
			trie->ahoCorasick(strs, cnt);
			match(*trie, str);
			cnt = 0;
			delete(trie);
		}
	}
	if (cnt) {
		trie = new Trie;
		trie->ahoCorasick(strs, cnt);
		match(*trie, str);
		cnt = 0;
	}

	cnt = 0;
	int maxlen = 0;
	for (int i = 0; i < N; i++) {
		maxlen = max(maxlen, table[i]);
		if (maxlen == 0)
			cnt++;
		maxlen--;
	}
	printf("%d", cnt);
	return 0;
}