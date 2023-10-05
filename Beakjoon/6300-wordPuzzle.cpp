#include <bits/stdc++.h>
using namespace std;

typedef struct TrieNode {
	char ch;
	int output;
	int depth;
	TrieNode* go[26];
	TrieNode* fail;
	TrieNode* postfixOutput;
	TrieNode(char c, int d) : ch(c), output(-1), fail(NULL), depth(d), postfixOutput(NULL) {
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
				if (cur->go[str[i] - 'A'])
					cur = cur->go[str[i] - 'A'];
				else
					cur = cur->go[str[i] - 'A'] = new Node(str[i], cur->depth + 1);
			}
			cur->output = k;
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
				if (next->fail->output != -1)
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



void solve(int L, int C, int W, char** grid, vector<char*>& strs) {
	vector<tuple<int, int, char>> ans;
	vector<int> lens;
	ans.assign(W, {2000, 2000, 128});
	Trie trie;
	trie.ahoCorasick(strs, W);
	
	for (int i = 1; i <= L; i++) {
		Node* node = trie.root;
		Node* search;
		for (int c = 1; c <= C; c++) {
			while (node && !node->go[grid[i][c] - 'A'])
				node = node->fail;
			if (node) {
				node = node->go[grid[i][c] - 'A'];
				search = node;
				while (search && search->output != -1) {
					ans[search->output] = min({ i - 1, c - search->depth, 'C' }, ans[search->output]);
					search = search->postfixOutput;
				}
			}
			else
				node = trie.root;
		}
		node = trie.root;
		for (int c = C; c > 0; c--) {
			while (node && !node->go[grid[i][c] - 'A'])
				node = node->fail;
			if (node) {
				node = node->go[grid[i][c] - 'A'];
				search = node;
				while (search && search->output != -1) {
					ans[search->output] = min({ i - 1, c + search->depth - 2, 'G' }, ans[search->output]);
					search = search->postfixOutput;
				}
			}
			else
				node = trie.root;
		}
	}

	for (int j = 1; j <= C; j++) {
		Node* node = trie.root;
		Node* search;
		for (int l = 1; l <= L; l++) {
			while (node && !node->go[grid[l][j] - 'A'])
				node = node->fail;
			if (node) {
				node = node->go[grid[l][j] - 'A'];
				search = node;
				while (search && search->output != -1) {
					ans[search->output] = min({ l - search->depth, j - 1, 'E' }, ans[search->output]);
					search = search->postfixOutput;
				}
			}
			else
				node = trie.root;
		}
		node = trie.root;
		for (int l = L; l > 0; l--) {
			while (node && !node->go[grid[l][j] - 'A'])
				node = node->fail;
			if (node) {
				node = node->go[grid[l][j] - 'A'];
				search = node;
				while (search && search->output != -1) {
					ans[search->output] = min({ l + search->depth - 2, j - 1, 'A' }, ans[search->output]);
					search = search->postfixOutput;
				}
			}
			else
				node = trie.root;
		}
	}
	
	int i = 1, j = C;
	while (j >= 1) {
		int l = i, c = j--;
		Node* node = trie.root;
		Node* search;
		while (grid[l][c]) {
			while (node && !node->go[grid[l][c] - 'A'])
				node = node->fail;
			if (node) {
				node = node->go[grid[l][c] - 'A'];
				search = node;
				while (search && search->output != -1) {
					ans[search->output] = min({ l - search->depth, c - search->depth, 'D' }, ans[search->output]);
					search = search->postfixOutput;
				}
			}
			else
				node = trie.root;
			l++; c++;
		}
		l--; c--;
		node = trie.root;
		while (grid[l][c]) {
			while (node && !node->go[grid[l][c] - 'A'])
				node = node->fail;
			if (node) {
				node = node->go[grid[l][c] - 'A'];
				search = node;
				while (search && search->output != -1) {
					ans[search->output] = min({ l + search->depth - 2, c + search->depth - 2, 'H' }, ans[search->output]);
					search = search->postfixOutput;
				}
			}
			else
				node = trie.root;
			l--; c--;
		}
	}

	i = 2; j = 1;
	while (i <= L) {
		int l = i++, c = j;
		Node* node = trie.root;
		Node* search;
		while (grid[l][c]) {
			while (node && !node->go[grid[l][c] - 'A'])
				node = node->fail;
			if (node) {
				node = node->go[grid[l][c] - 'A'];
				search = node;
				while (search && search->output != -1) {
					ans[search->output] = min({ l - search->depth, c - search->depth, 'D' }, ans[search->output]);
					search = search->postfixOutput;
				}
			}
			else
				node = trie.root;
			l++; c++;
		}
		l--; c--;
		node = trie.root;
		while (grid[l][c]) {
			while (node && !node->go[grid[l][c] - 'A'])
				node = node->fail;
			if (node) {
				node = node->go[grid[l][c] - 'A'];
				search = node;
				while (search && search->output != -1) {
					ans[search->output] = min({ l + search->depth - 2, c + search->depth - 2, 'H' }, ans[search->output]);
					search = search->postfixOutput;
				}
			}
			else
				node = trie.root;
			l--; c--;
		}
		l++; c++;
		while (grid[l][c]) {
			while (node && !node->go[grid[l][c] - 'A'])
				node = node->fail;
			if (node) {
				node = node->go[grid[l][c] - 'A'];
				search = node;
				while (search && search->output != -1) {
					ans[search->output] = min({ l + search->depth - 2, c - search->depth, 'B' }, ans[search->output]);
					search = search->postfixOutput;
				}
			}
			else
				node = trie.root;
			l--; c++;
		}
		l++; c--;
		while (grid[l][c]) {
			while (node && !node->go[grid[l][c] - 'A'])
				node = node->fail;
			if (node) {
				node = node->go[grid[l][c] - 'A'];
				search = node;
				while (search && search->output != -1) {
					ans[search->output] = min({ l - search->depth, c + search->depth - 2, 'F' }, ans[search->output]);
					search = search->postfixOutput;
				}
			}
			else
				node = trie.root;
			l++; c--;
		}
	}

	i = L; j = 1;
	while (j <= C) {
		int l = i, c = j++;
		Node* node = trie.root;
		Node* search;
		while (grid[l][c]) {
			while (node && !node->go[grid[l][c] - 'A'])
				node = node->fail;
			if (node) {
				node = node->go[grid[l][c] - 'A'];
				search = node;
				while (search && search->output != -1) {
					ans[search->output] = min({ l + search->depth - 2, c - search->depth, 'B' }, ans[search->output]);
					search = search->postfixOutput;
				}
			}
			else
				node = trie.root;
			l--; c++;
		}
		l++; c--;
		while (grid[l][c]) {
			while (node && !node->go[grid[l][c] - 'A'])
				node = node->fail;
			if (node) {
				node = node->go[grid[l][c] - 'A'];
				search = node;
				while (search && search->output != -1) {
					ans[search->output] = min({ l - search->depth, c + search->depth - 2, 'F' }, ans[search->output]);
					search = search->postfixOutput;
				}
			}
			else
				node = trie.root;
			l++; c--;
		}
	}

	for (const auto& out : ans) {
		printf("%d %d %c\n", get<0>(out), get<1>(out), get<2>(out));
	}
}

int main() {
	int L, C, W;
	char** grid;
	vector<char*> strs;

	scanf("%d %d %d", &L, &C, &W);
	grid = new char* [L + 2];
	for (int i = 0; i < L + 2; i++) {
		grid[i] = new char[C + 2];
		memset(grid[i], 0, C + 2);
		if (0 < i && i <= L)
			scanf("%s", grid[i] + 1);
	}
	strs.assign(W, 0);
	for (int i = 0; i < W; i++) {
		strs[i] = new char[1001];
		scanf("%s", strs[i]);
	}
	solve(L, C, W, grid, strs);
	return 0;
}