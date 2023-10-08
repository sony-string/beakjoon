#include <bits/stdc++.h>
using namespace std;

typedef struct Fraction {
	long long up, down;
	Fraction(long long i, long long j) : up(i), down(j) { makegcd(); }
	Fraction operator+(Fraction& rhs) {
		Fraction ret(up, down);
		ret.down = down * rhs.down;
		ret.up = up * rhs.down;
		ret.up = ret.up + rhs.up * down;
		return ret;
	}
	Fraction operator-(Fraction& rhs) {
		Fraction ret(up, down);
		ret.down = down * rhs.down;
		ret.up = up * rhs.down;
		ret.up = ret.up - rhs.up * down;
		return ret;
	}
	Fraction operator*(Fraction& rhs) {
		Fraction ret(up, down);
		ret.down = down * rhs.down;
		ret.up = up * rhs.up;
		return ret;
	}
	Fraction operator/(Fraction& rhs) {
		Fraction ret(up, down);
		ret.down = down * rhs.up;
		ret.up = up * rhs.down;
		return ret;
	}
	bool operator== (Fraction& rhs) {
		if (rhs.down == 0 && down == 0)
			return true;
		else if (rhs.up == 0 && up == 0)
			return true;
		return (rhs.up == up) && (rhs.down == down);
	}
	void makegcd() {
		if (down == 0) {
			up = 10000;
			down = 1;
		}
		else if (up != 0) {
			auto d = gcd(up, down);
			up /= d;
			down /= d;
		}
		else {
			down = 1;
		}
		if (down < 0) {
			up *= -1;
			down *= -1;
		}
	}
	bool isinf() {
		return up == 10000 && down == 1;
	}
	bool iszero() {
		return !up && down;
	}
	bool operator< (const Fraction& rhs) {
		return (up * rhs.down) < (rhs.up * down);
	}
} Frac;

bool operator< (const Fraction& lhs, const Fraction& rhs) {
	return (lhs.up * rhs.down) < (rhs.up * lhs.down);
}


int main() {
	int N;
	vector<pair<int, int>> arr;
	map<Frac, int> lines, ps;
	scanf("%d", &N);
	arr.assign(N, { 0 , 0 });
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &arr[i].first, &arr[i].second);
	}
	if (N == 1) {
		if (arr[0].first == 0 && arr[0].second == 0)
			printf("-1");
		else
			printf("1");
		return 0;
	}
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			Frac s(arr[j].second - arr[i].second, arr[j].first - arr[i].first);
			if (s.up != 10000 && s.up != 0) {
				swap(s.up, s.down);
				s.up *= -1;
				s.makegcd();
			}
			else if (s.up == 10000) {
				s.up = 0;
				s.down = 1;
			}
			else {
				s.up = 10000;
				s.down = 1;
			}
			Frac m(arr[i].second + arr[j].second, arr[i].first + arr[j].first);
			if (!(s == m) && !(arr[i].second + arr[j].second == 0 && arr[i].first + arr[j].first == 0)) continue;
			auto line = lines.find(s);
			if (line == lines.end()) {
				lines.emplace(s, 1);
			}
			else {
				(*line).second += 1;
			}
		}
	}
	int newN = N;
	for (int i = 0; i < N; i++) {
		if (arr[i].first == 0 && arr[i].second == 0) {
			newN = N - 1;
			continue;
		}
		Frac m(arr[i].second, arr[i].first);
		auto line = ps.find(m);
		if (line == ps.end()) {
			ps.emplace(m, 1);
		}
		else {
			(*line).second += 1;
		}
	}
	N = newN;

	int cnt = 0;
	for (const auto& i : lines) {
		int n = N;
		auto line = ps.find(i.first);
		if (line != ps.end()) {
			n -= (*line).second;
		}
		if (n % 2 != 0) continue;
		else if (n / 2 == i.second) cnt++;
	}
	for (const auto& i : ps) {
		if (i.second == N) cnt++;
	}

	printf("%d", cnt);
	return 0;
}