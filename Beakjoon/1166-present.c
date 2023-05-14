#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double solve(double a, int n, int l, int w, int h) {
	unsigned long long count, lcount, wcount, hcount;
	double nano = 0.000000001;
	double left = 0, right, middle;
	right = l > w ? l : w;
	right = right > h ? right : h;

	
	for (int i = 0; i < 10000; i++) {
		middle = left + right;
		middle /= 2;
		lcount = (unsigned long long)((double)l / middle);
		wcount = (unsigned long long)((double)w / middle);
		hcount = (unsigned long long)((double)h / middle);
		count = lcount * wcount * hcount;

		if (count >= n) {
			left = middle;
		}
		else {
			right = middle;
		}
	}
	return left;
}

int main() {
	double len = 1000000000;
	int n, l, w, h;
	scanf("%d %d %d %d", &n, &l, &w, &h);
	len = solve(len, n, l, w, h);

	printf("%.10lf", len);
	return 0;
}