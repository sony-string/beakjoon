#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;


int findlca(int a, int b) {
	if (a < b) {
		int temp = a;
		a = b;
		b = temp;
	}
	int alevel = (int)log2(a);
	int blevel = (int)log2(b);
	
	while (alevel != blevel) {
		a /= 2;
		alevel -= 1;
	}
	
	while (a != b) {
		a /= 2;
		b /= 2;
	}

	return a;
}


int main() {
	int cases;
	int a, b;
	scanf("%d", &cases);

	for (int i = 0; i < cases; i++) {
		scanf("%d %d", &a, &b);
		printf("%d\n", 10 * findlca(a, b));
	}
	return 0;
}