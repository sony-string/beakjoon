#include <stdio.h>

void swap(long long* a, long long* b) {
	long long temp = *a;
	*a = *b;
	*b = temp;
}

int main() {
	long long src[2][2], dst[2][2];
	long long i, isOverlapedX, isOverlapedY;
	long long overlapedXRange[2];

	for (i = 0; i < 2; i++) {
		scanf("%lld %lld", &src[i][0], &src[i][1]);
		scanf("%lld %lld", &dst[i][0], &dst[i][1]);
		if (dst[i][0] - src[i][0] < 0) {
			swap(&src[i][0], &dst[i][0]);
			swap(&src[i][1], &dst[i][1]);
		}
		else if (dst[i][0] - src[i][0] == 0) {
			if (dst[i][1] - src[i][1] < 0) {
				swap(&src[i][1], &dst[i][1]);
			}
		}
	}

	long long deltaX[2], deltaY[2];

	for (i = 0; i < 2; i++) {
		deltaX[i] = dst[i][0] - src[i][0];
		deltaY[i] = dst[i][1] - src[i][1];
	}
	overlapedXRange[0] = 9999999;
	overlapedXRange[1] = 9999999;
	//선분 0이 더 왼쪽
	if (src[0][0] <= src[1][0]) {
		//x축범위가 오버랩되면 1 안되면 0
		if (dst[0][0] - src[1][0] >= 0) {
			overlapedXRange[0] = src[1][0];
			overlapedXRange[1] = dst[0][0];
			isOverlapedX = 1;
		}
		else {
			isOverlapedX = 0;
		}
	}
	//선분 1이 더 왼쪽
	else {
		if (dst[1][0] - src[0][0] >= 0) {
			overlapedXRange[0] = src[0][0];
			overlapedXRange[1] = dst[1][0];
			isOverlapedX = 1;
		}
		else {
			isOverlapedX = 0;
		}
	}

	long long tempY[2][2];
	tempY[0][0] = dst[0][1];
	tempY[0][1] = src[0][1];	
	tempY[1][0] = dst[1][1];
	tempY[1][1] = src[1][1];

	if (deltaY[0] >= 0) {
		swap(&tempY[0][0], &tempY[0][1]);
	}
	if (deltaY[1] >= 0) {
		swap(&tempY[1][0], &tempY[1][1]);
	}
	//선분 0이 더 아래면
	if (tempY[0][0] < tempY[1][0]) {
		if (tempY[1][0] <= tempY[0][1]) {
			isOverlapedY = 1;
		}
		else { 
			isOverlapedY = 0;
		}
	}
	else {
		if (tempY[0][0] <= tempY[1][1]) {
			isOverlapedY = 1;
		}
		else {
			isOverlapedY = 0;
		}
	}

	//x, y 범위가 안겹치면 에초에 못만남
	if (isOverlapedX == 0 || isOverlapedY == 0) {
		printf("0");
		return 0;
	}
	
	long long L, R;
	L = deltaX[1] * deltaY[0] * (overlapedXRange[0] - src[0][0]) + deltaX[1] * deltaX[0] * src[0][1] - deltaX[0] * deltaY[1] * 
		(overlapedXRange[0] - src[1][0]) - deltaX[1] * deltaX[0] * src[1][1];

	R = deltaX[1] * deltaY[0] * (overlapedXRange[1] - src[0][0]) + deltaX[1] * deltaX[0] * src[0][1] - deltaX[0] * deltaY[1] * 
		(overlapedXRange[1] - src[1][0]) - deltaX[1] * deltaX[0] * src[1][1];
	if ((L <= 0 && R >= 0) || (L >= 0 && R <= 0) || L == 0 || R == 0) {
		printf("1");
		return 0;
	}
	printf("0");
	return 0;
}