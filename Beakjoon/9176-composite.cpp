#include <bits/stdc++.h>
using namespace std;

typedef long long li;
int main() {
	int primes[] = { 11, 23, 29, 37, 41, 43, 47, 53, 59 };
	int K;
	scanf("%d", &K);
	for (int i = 0; primes[i] <= K; i++) {
		li n = 2;
		for (int k = 1; k < primes[i]; k++) {
			n *= 2;
		}
		n -= 1;
		int cnt = 0;
		bool isPrime = true;
		for (li k = 3; k * k <= n; k++) {
			while (n % k == 0) {
				if (cnt != 0)
					printf("* ");
				cnt++;
				isPrime = false;
				printf("%lld ", k);
				n /= k;
			}
		}
		if (!isPrime) {
			if (n != 1) {
				printf("* %lld = %lld = ( 2 ^ %d ) - 1\n", n, (li)pow(2, primes[i]) - 1, primes[i]);
			}
			else
				printf("= %lld = ( 2 ^ %d ) - 1\n", (li)pow(2, primes[i]) - 1, primes[i]);
		}
	}
	return 0;
}