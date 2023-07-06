#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;


#ifndef LLONG_MAX
#define LLONG_MAX 9223372036854775807
#endif


typedef long long li;


li solve(li price, int expo = 15, li coinCount = 0) {
	li count = 0;
	li coinValue;
	li bestCoinCount = LLONG_MAX;

	coinValue = pow(10, expo);

	for (; expo > 0; expo--) {
		if (expo % 2 == 1) {
			if (price >= (coinValue / 10) * 25) {
				count = price / ((coinValue / 10) * 25);
				bestCoinCount = min(solve(
					price - count * ((coinValue / 10) * 25),
					expo,
					coinCount + count), bestCoinCount);
			}
		}

		if (price >= coinValue) {
			count = price / coinValue;
			price -= count * coinValue;
			coinCount += count;
		}

		coinValue /= 10;
	}

	if (price > 0) {
		coinCount += price;
	}

	bestCoinCount = min(coinCount, bestCoinCount);
	return bestCoinCount;
}


int main() {
	int T;
	li price;
	li coinCount;

	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		scanf("%lld", &price);
		coinCount = solve(price);

		printf("%lld\n", coinCount);
	}

	return 0;
}