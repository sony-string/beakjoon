#include <bits/stdc++.h>
using namespace std;

typedef long long li;
typedef vector<li> vi;

li solve(li n, li m) {	
	if (m == 1) return 0;
	if (n < 5) {
		li ret = 1;
		for (int i = 2; i <= n; i++) {
			ret = pow(i, ret);
		}
		return ret;
	}
	
	// phi(m) 계산
	vector<li> factors;
	li phi = m;
	for (li i = 2; i * i <= m; i++) {
		if (phi % i == 0) {
			factors.push_back(i);
			while (phi % i == 0) {
				phi /= i;
			}
		}
	}
	if (phi != 1) factors.push_back(phi);
	phi = m;
	for (auto& i : factors) {
		phi /= i;
		phi *= i - 1;
	}
	factors.clear();

	// n ^ e = n ^ (e mod phi(m)) (mod m)
	// 따라서 e mod phi(m) 계산
	li e = solve(n - 1, phi) + phi;
	
	// 로그시간 거듭제곱
	li mul = n;
	li ret = 1;	
	while (e != 0) {
		if (e % 2) {
			ret *= mul;
			ret %= m;
		}
		mul *= mul;
		mul %= m;
		e >>= 1;
	}
	return ret;
}

int main() {
	int n, m;
	li ret = 1;	
	scanf("%d %d", &n, &m);	
	printf("%lld", solve(n, m) % m);
	return 0;
}