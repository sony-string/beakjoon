#include <bits/stdc++.h>
using namespace std;

const int R = 0, K = 1, B = 2;
int N, n;
int mov[8][2] = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2} };

bool outbounded(int x, int y) {
    return (x < 0 || x >= N || y < 0 || y >= N);
}
bool isKnight(pair<int, int>& a, pair<int, int>& b) {
    return ((abs(b.first - a.first) == 2 && abs(b.second - a.second) == 1) ||
        (abs(b.first - a.first) == 1 && abs(b.second - a.second) == 2));
}
bool isBishop(pair<int, int>& a, pair<int, int>& b) {
    return abs(b.first - a.first) == abs(b.second - a.second);
}
bool isRook(pair<int, int>& a, pair<int, int>& b) {
    return a.first == b.first || a.second == b.second;
}
bool samecolor(pair<int, int>& a, pair<int, int>& b) {
    return (b.first % 2 == b.second % 2) == (a.first % 2 == a.second % 2);
}


int main() {

    vector<pair<int, int>> pos;
    pair<int, int> p;
    scanf("%d", &N);
    pos.assign(N * N + 1, { 0, 0 });
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &n);
            pos[n].first = i;
            pos[n].second = j;
        }
    }
    int elapsed[3] = { 0, 0, 0 };
    int visited[10][10][3];
    int changecount[10][10][3];
    visited[pos[1].first][pos[1].second][0] = 0;
    visited[pos[1].first][pos[1].second][1] = 0;
    visited[pos[1].first][pos[1].second][2] = 0;
    changecount[pos[1].first][pos[1].second][0] = 0;
    changecount[pos[1].first][pos[1].second][1] = 0;
    changecount[pos[1].first][pos[1].second][2] = 0;

    queue<pair<int, pair<int, int>>> q;
    for (n = 1; n < N * N; n++) {
        elapsed[0] = visited[pos[n].first][pos[n].second][0];
        elapsed[1] = visited[pos[n].first][pos[n].second][1];
        elapsed[2] = visited[pos[n].first][pos[n].second][2];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < 3; k++) {
                    if (i != pos[n].first || j != pos[n].second) {
                        visited[i][j][k] = 1e9;
                        changecount[i][j][k] = 1e9;
                    }
                }
            }
        }
        int t = elapsed[0];
        int end;
        t = min(t, min(elapsed[1], elapsed[2]));
        q = queue<pair<int, pair<int, int>>>();
        t--;
        bool searching = true;
        while (searching) {
            t++;
            for (int i = 0; i < 3; i++) {
                if (t == visited[pos[n].first][pos[n].second][i])
                    q.emplace(i, pos[n]);
            }
            end = q.size();
            const auto& e = q.front();
            for (int i = 0; i < end; i++) {
                auto e = q.front();
                if (e.second == pos[n + 1]) searching = false;
                q.pop();
                for (int j = 0; j < 3; j++) {
                    if (e.first == j || visited[e.second.first][e.second.second][j] <= t + 1) {
                        if (visited[e.second.first][e.second.second][j] == t + 1 &&
                            changecount[e.second.first][e.second.second][j] > changecount[e.second.first][e.second.second][e.first] + 1)
                            changecount[e.second.first][e.second.second][j] = changecount[e.second.first][e.second.second][e.first] + 1;
                        continue;
                    }
                    q.emplace(j, e.second);
                    visited[e.second.first][e.second.second][j] = t + 1;
                    changecount[e.second.first][e.second.second][j] = changecount[e.second.first][e.second.second][e.first] + 1;
                }
                if (e.first == B) {
                    p = e.second;
                    while (!outbounded(++p.first, ++p.second)) {
                        if (visited[p.first][p.second][B] > t + 1) {
                            visited[p.first][p.second][B] = t + 1;
                            q.emplace(B, p);
                            changecount[p.first][p.second][B] = changecount[e.second.first][e.second.second][B];
                        }
                        else if (visited[p.first][p.second][B] == t + 1 &&
                            changecount[p.first][p.second][B] > changecount[e.second.first][e.second.second][B]) {
                            changecount[p.first][p.second][B] = changecount[e.second.first][e.second.second][B];
                        }
                    }
                    p = e.second;
                    while (!outbounded(--p.first, ++p.second)) {
                        if (visited[p.first][p.second][B] > t + 1) {
                            visited[p.first][p.second][B] = t + 1;
                            q.emplace(B, p);
                            changecount[p.first][p.second][B] = changecount[e.second.first][e.second.second][B];
                        }
                        else if (visited[p.first][p.second][B] == t + 1 &&
                            changecount[p.first][p.second][B] > changecount[e.second.first][e.second.second][B]) {
                            changecount[p.first][p.second][B] = changecount[e.second.first][e.second.second][B];
                        }
                    }
                    p = e.second;
                    while (!outbounded(--p.first, --p.second)) {
                        if (visited[p.first][p.second][B] > t + 1) {
                            visited[p.first][p.second][B] = t + 1;
                            q.emplace(B, p);
                            changecount[p.first][p.second][B] = changecount[e.second.first][e.second.second][B];
                        }
                        else if (visited[p.first][p.second][B] == t + 1 &&
                            changecount[p.first][p.second][B] > changecount[e.second.first][e.second.second][B]) {
                            changecount[p.first][p.second][B] = changecount[e.second.first][e.second.second][B];
                        }
                    }
                    p = e.second;
                    while (!outbounded(++p.first, --p.second)) {
                        if (visited[p.first][p.second][B] > t + 1) {
                            visited[p.first][p.second][B] = t + 1;
                            q.emplace(B, p);
                            changecount[p.first][p.second][B] = changecount[e.second.first][e.second.second][B];
                        }
                        else if (visited[p.first][p.second][B] == t + 1 &&
                            changecount[p.first][p.second][B] > changecount[e.second.first][e.second.second][B]) {
                            changecount[p.first][p.second][B] = changecount[e.second.first][e.second.second][B];
                        }
                    }
                }
                else if (e.first == K) {
                    for (int i = 0; i < 8; i++) {
                        p = { e.second.first + mov[i][0], e.second.second + mov[i][1] };
                        if (!outbounded(p.first, p.second)) {
                            if (visited[p.first][p.second][K] > t + 1) {
                                visited[p.first][p.second][K] = t + 1;
                                q.emplace(K, p);
                                changecount[p.first][p.second][K] = changecount[e.second.first][e.second.second][K];
                            }
                            else if (visited[p.first][p.second][K] == t + 1 &&
                                changecount[p.first][p.second][K] > changecount[e.second.first][e.second.second][K]) {
                                changecount[p.first][p.second][K] = changecount[e.second.first][e.second.second][K];
                            }
                        }
                    }
                }
                else {
                    p = e.second;
                    while (!outbounded(++p.first, p.second)) {
                        if (visited[p.first][p.second][R] > t + 1) {
                            visited[p.first][p.second][R] = t + 1;
                            q.emplace(R, p);
                            changecount[p.first][p.second][R] = changecount[e.second.first][e.second.second][R];
                        }
                        else if (visited[p.first][p.second][R] == t + 1 &&
                            changecount[p.first][p.second][R] > changecount[e.second.first][e.second.second][R]) {
                            changecount[p.first][p.second][R] = changecount[e.second.first][e.second.second][R];
                        }
                    }
                    p = e.second;
                    while (!outbounded(--p.first, p.second)) {
                        if (visited[p.first][p.second][R] > t + 1) {
                            visited[p.first][p.second][R] = t + 1;
                            q.emplace(R, p);
                            changecount[p.first][p.second][R] = changecount[e.second.first][e.second.second][R];
                        }
                        else if (visited[p.first][p.second][R] == t + 1 &&
                            changecount[p.first][p.second][R] > changecount[e.second.first][e.second.second][R]) {
                            changecount[p.first][p.second][R] = changecount[e.second.first][e.second.second][R];
                        }
                    }
                    p = e.second;
                    while (!outbounded(p.first, --p.second)) {
                        if (visited[p.first][p.second][R] > t + 1) {
                            visited[p.first][p.second][R] = t + 1;
                            q.emplace(R, p);
                            changecount[p.first][p.second][R] = changecount[e.second.first][e.second.second][R];
                        }
                        else if (visited[p.first][p.second][R] == t + 1 &&
                            changecount[p.first][p.second][R] > changecount[e.second.first][e.second.second][R]) {
                            changecount[p.first][p.second][R] = changecount[e.second.first][e.second.second][R];
                        }
                    }
                    p = e.second;
                    while (!outbounded(p.first, ++p.second)) {
                        if (visited[p.first][p.second][R] > t + 1) {
                            visited[p.first][p.second][R] = t + 1;
                            q.emplace(R, p);
                            changecount[p.first][p.second][R] = changecount[e.second.first][e.second.second][R];
                        }
                        else if (visited[p.first][p.second][R] == t + 1 &&
                            changecount[p.first][p.second][R] > changecount[e.second.first][e.second.second][R]) {
                            changecount[p.first][p.second][R] = changecount[e.second.first][e.second.second][R];
                        }
                    }
                }
            }
        }
    }

    elapsed[0] = visited[pos[N * N].first][pos[N * N].second][0];
    elapsed[1] = visited[pos[N * N].first][pos[N * N].second][1];
    elapsed[2] = visited[pos[N * N].first][pos[N * N].second][2];
    int t = elapsed[0];
    t = min(t, min(elapsed[1], elapsed[2]));
    int cnt = 1e9;
    for (int i = 0; i < 3; i++) {
        if (visited[pos[N * N].first][pos[N * N].second][i] != t)
            continue;
        cnt = min(cnt, changecount[pos[N * N].first][pos[N * N].second][i]);
    }
    printf("%d %d", t, cnt);
    return 0;
}