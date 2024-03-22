#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1100000;
int winner[MAXN], loser[MAXN];
int wincnt[MAXN];
bool defeated[MAXN];
int op[MAXN][22];

int main() {
	int N, ncnt = 0;
	bool hasConflict = false;
	// ī��Ʈ ä���
	// �¸���� �ٽ� ���鼭 ��� �¸���� ����� ã�� => ����� ������ �ش� ĭ ����� �� + ��� ��� ���
	// ����� ������ٸ�, ����������� �¸� Ƚ���� N-1�� ����. ������� ���� ���.
	// �׷��� �ʴٸ� ����� �ִ��� üũ, ����� ���� �й� ����� ������ ����� ��Ī�Ǿ��� �� �浹�� ������ üũ
	// ����� ���ٸ� N-1�� + �й谡 ���� ����� �¸������ �������. (�����)

	scanf("%d", &N);
	ncnt = pow(2, N);
	for (int i = 0; i < ncnt - 2; i++) {
		int w, d;
		scanf("%d %d", &w, &d);
		winner[i] = w; loser[i] = d;
		wincnt[w]++;
		defeated[d] = true;
	}
	vector<int> nolose, conflict;	
	nolose.reserve(2);
	conflict.reserve(2);
	for (int i = 0; i < ncnt - 2; i++) {
		int w = winner[i], d = loser[i];
		if (op[w][wincnt[d]]) {
			conflict.push_back(op[w][wincnt[d]]);
			conflict.push_back(d);
			hasConflict = true;
		}
		if (op[d][wincnt[w]]) {
			conflict.push_back(op[d][wincnt[w]]);
			conflict.push_back(w);
			hasConflict = true;
		}
		op[w][wincnt[d]] = d;
		op[d][wincnt[w]] = w;
	}
	for (int i = 1; i <= ncnt; i++) {
		if (!defeated[i]) nolose.push_back(i);
	}
	
	if (wincnt[nolose[0]] == N - 1 && wincnt[nolose[1]] == N - 1) {
		int w = nolose[0], d = nolose[1];
		if (w > d) swap(w, d);
		printf("%d %d\n%d %d", w, d, d, w);
		return 0;
	}
	
    int ansd = -1;
	vector<int> answ;
	answ.reserve(2);
	ansd = wincnt[nolose[0]] < N - 1 ? nolose[0] : nolose[1];
	if (hasConflict) {
		for (const int& p : conflict) {
			if (!op[p][wincnt[ansd]]) answ.push_back(p);
		}
	}
	else {
		answ.push_back(nolose[0] != ansd ? nolose[0] : nolose[1]);
	}
	assert(!answ.empty());
	sort(answ.begin(), answ.end());
	for (auto& i : answ) {
		printf("%d %d\n", i, ansd);
	}
	return 0;
}