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
	// 카운트 채우고
	// 승리기록 다시 보면서 상대 승리기록 모순점 찾고 => 모순점 있으면 해당 칸 비워도 됨 + 대결 상대 기록
	// 결승이 사라졌다면, 안진사람들의 승리 횟수는 N-1로 같다. 안진사람 둘이 결승.
	// 그렇지 않다면 모순이 있는지 체크, 모순된 둘이 패배 기록이 삭제된 사람과 매칭되었을 때 충돌이 없는지 체크
	// 모순이 없다면 N-1승 + 패배가 없는 사람의 승리기록이 사라졌다. (결승자)

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