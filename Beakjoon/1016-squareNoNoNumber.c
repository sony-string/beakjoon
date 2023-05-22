#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

typedef long long li;

#define fore(a, b) for(li i = (a); i < (b); i++)
int pool[1000001];


int main() {
	li _min, _max;
	li count;
	li upper;
	
	scanf("%lld %lld", &_min, &_max);
	memset(pool, 0, 4000004);

	upper = (li)sqrt(_max);
	li sqr;

	count = 0;
	fore(2, upper + 1) { 
		sqr = i * i;
		for (li k = (_min + sqr - 1) / sqr; sqr * k <= _max; k++) {
			if (pool[sqr * k - _min] == 0) {
				pool[sqr * k - _min] = 1;
				count++;
			}
		}
	}
	
	
	printf("%lld", (_max - _min + 1) - count);
	return 0;
}