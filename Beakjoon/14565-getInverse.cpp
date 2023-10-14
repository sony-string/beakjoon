#include <bits/stdc++.h>
using namespace std;

typedef long long li;

li x, y;
li uclid(li a, li b) {
	x = 1; y = -a / b; 
	if (a % b == 0) {
		x = 0; y = 1; return b;
	}
	li d = uclid(b, a % b);
	li xx, yy;
	xx = y;
	yy = x + y * (-a / b);
	x = xx; y = yy;
	return d;
}

int main() {
	li n, a;
	scanf("%lld %lld", &n, &a);
	li b, c;
	b = (n - (a % n)) % n;
	c = -1;
	li d = uclid(n, a);
	if (d == 1) { 
		if (y < 0)
			y = (y % n) + n;
		c = y %= n;
	};
	printf("%lld %lld", b, c);
	return 0;
}