#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

enum {
	len = 0, wid = 1, hei = 2
};

enum cube {
	size = 0, numCubes = 1
};

int powOf2[21];

long long solve(long long length, long long width, long long height, long long** cubes, int numTypes) {
	long long shortLen, powNum, num;
	long long margin[3];
	shortLen = length > width ? width : length;
	shortLen = shortLen < height ? shortLen : height;
	long long biggestCube, needed = 0, vol, count;

	for (int i = 20; i >= 0; i--) {
		if (shortLen >= powOf2[i]) {
			biggestCube = powOf2[i];
			powNum = i;
			break;
		}
	}
	margin[len] = length - biggestCube;
	margin[wid] = width - biggestCube;
	margin[hei] = height - biggestCube;
	biggestCube = biggestCube * biggestCube * biggestCube;
	if (biggestCube == 1) {
		if (cubes[0][size] == 0) {
			count = length * height * width;
			if (count > cubes[0][numCubes]) {
				return -1;
			}
			cubes[0][numCubes] -= count;
			return count;
		}
		else {
			return -1;
		}
	}

	num = numTypes - 1;
	while (biggestCube > 0) {
		if (num == -1) {
			return -1;
		}
		vol = powOf2[cubes[num][size]];
		vol = vol * vol * vol;
		count = biggestCube / vol;
		if (count > cubes[num][numCubes]) {
			count = cubes[num][numCubes];
			cubes[num][numCubes] = 0;
		}
		else {
			cubes[num][numCubes] -= count;
		}
		biggestCube -= (unsigned long long)count * vol;
		needed += count;
		num--;
	}
	if (margin[hei] > 0) {
		count = solve(length, width, margin[hei], cubes, numTypes);
		if (count == -1) {
			return -1;
		}
		needed += count;
	}
	if (margin[len] > 0) {
		count = solve(margin[len], width, height - margin[hei], cubes, numTypes);
		if (count == -1) {
			return -1;
		}
		needed += count;
	}
	if (margin[wid] > 0) {
		count = solve(length - margin[len], margin[wid], height - margin[hei], cubes, numTypes);
		if (count == -1) {
			return -1;
		}
		needed += count;
	}
	return needed;
}

int main() {
	long long length, width, height;
	int num;
	int numTypes;
	long long** cubes;
	long long needed;


	scanf("%lld %lld %lld", &length, &width, &height);
	scanf("%d", &numTypes);

	cubes = (long long**)malloc(numTypes * sizeof(long long*));

	for (int i = 0; i < numTypes; i++) {
		cubes[i] = malloc(2 * sizeof(int));
		scanf("%lld %lld", cubes[i], cubes[i] + 1);
	}
	num = 1;
	for (int i = 0; i <= 20; i++) {
		powOf2[i] = num;
		num <<= 1;
	}


	needed = solve(length, width, height, cubes, numTypes);
	if (needed == -1) {
		printf("-1");
		return 0;
	}
	printf("%lld", needed);
	return 0;
}