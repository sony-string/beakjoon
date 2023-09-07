#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define REALLOC_COEF 10

//int stack[50][3];
//int sorted[1000001][2];
//int arr[2][1000001][2];
int** stack;
int** sorted;
int*** arr;
int stackSize = 100;
int sortedSize = 10001;
int arrSize[2] = { 10001, 10001 };

enum {
	coef = 0, expo = 1
};

void mergeSort(int** arr, int size) {
	int originSize;
	int top = 0;
	int k, m, i;
	int l = 0, r = size - 1, flag = 0;
	int left, right;
	stack[top][0] = l;
	stack[top][1] = r;
	stack[top][2] = 0;
	top++;

	if (size > sortedSize) {
		originSize = sortedSize;
		while (size > sortedSize) {
			sortedSize *= REALLOC_COEF;
		}
		sorted = (int**)realloc(sorted, sortedSize * sizeof(int*));
		assert(sorted != NULL);
		for (i = originSize; i < sortedSize; i++) {
			sorted[i] = (int*)malloc(2 * sizeof(int));
			assert(sorted[i] != NULL);
		}
	}

	while (top != 0) {
		top--;
		l = stack[top][0]; r = stack[top][1]; flag = stack[top][2];
		while (1) {
			if (top >= stackSize) {
				stackSize *= REALLOC_COEF;
				stack = (int**)realloc(stack, stackSize * sizeof(int*));
				assert(stack != NULL);
				for (i = stackSize / 10; i < stackSize; i++) {
					stack[i] = (int*)malloc(3 * sizeof(int));
					assert(stack[i] != NULL);
				}
			}
			if (l == r) {
				break;
			}
			m = l + r;
			m /= 2;
			if (flag == 0) {
				stack[top][0] = l;
				stack[top][1] = r;
				stack[top][2] = 1;
				top++;
				r = m;
				flag = 0;
				continue;
			}
			else if (flag == 1) {
				stack[top][0] = l;
				stack[top][1] = r;
				stack[top][2] = 2;
				top++;
				l = m + 1;
				flag = 0;
				continue;
			}
			else {
				k = 0;
				left = l;
				right = m + 1;
				while (left <= m && right <= r) {
					if (arr[left][expo] >= arr[right][expo]) {
						sorted[k][0] = arr[left][0];
						sorted[k][1] = arr[left][1];
						left++;
						k++;
						continue;
					}
					else {
						sorted[k][0] = arr[right][0];
						sorted[k][1] = arr[right][1];
						right++;
						k++;
						continue;
					}
				}

				while (left <= m) {
					sorted[k][0] = arr[left][0];
					sorted[k][1] = arr[left][1];
					left++;
					k++;
				}
				while (right <= r) {
					sorted[k][0] = arr[right][0];
					sorted[k][1] = arr[right][1];
					right++;
					k++;
				}
				k = 0;
				for (left = l; left <= r; left++) {
					arr[left][0] = sorted[k][0];
					arr[left][1] = sorted[k][1];
					k++;
				}
				break;
			}
		}
	}
}

int main() {
	clock_t start, end;
	start = clock();
	FILE* fp = freopen("input.txt", "r", stdin);

	void* temp;
	stack = (int**)malloc(stackSize * sizeof(int*));
	sorted = (int**)malloc(sortedSize * sizeof(int*));
	//arr[polynomial][term][coef / expo]
	arr = (int***)malloc(2 * sizeof(int**));
	arr[0] = (int**)malloc(arrSize[0] * sizeof(int*));
	arr[1] = (int**)malloc(arrSize[1] * sizeof(int*));
	int size[2] = { 0, 0 };
	int sizeSum;
	char ch;
	int T = 0, l, r, i, printFlag;
	int coefficient, exponential;


	/*
	다항식 입력 처리
	자료구조는 동적 할당 된 연속 리스트
	realloc은 10배씩 증가
	*/
	for (i = 0; i < stackSize; i++) {
		stack[i] = (int*)malloc(3 * sizeof(int));
	}
	for (i = 0; i < sortedSize; i++) {
		sorted[i] = (int*)malloc(2 * sizeof(int));
		arr[0][i] = (int*)malloc(2 * sizeof(int));
		arr[1][i] = (int*)malloc(2 * sizeof(int));
	}

	while (scanf("%c", &ch) != EOF) {
		if (ch != '(') {
			T = 1;
			continue;
		}
		scanf("%d,%d)", &arr[T][size[T]][coef], &arr[T][size[T]][expo]);
		size[T]++;
		if (size[T] >= arrSize[T]) {
			arrSize[T] *= REALLOC_COEF;
			arr[T] = (int**)realloc(arr[T], arrSize[T] * sizeof(int*));
			assert(arr[T] != NULL);
			for (i = arrSize[T] / 10; i < arrSize[T]; i++) {
				arr[T][i] = (int*)malloc(2 * sizeof(int));
				assert(arr[T][i] != NULL);
			}
		}
	}
	fclose(fp);
	/*
	다항식 정렬
	*/
	mergeSort(arr[0], size[0]);
	mergeSort(arr[1], size[1]);


	/*
	빠른 표준 출력을 위한 버퍼링
	버퍼의 기본 크기는 20 * (항의 개수) byte 이나, 할당 실패시 계수를 줄여가며 할당 재시도
	*/
	/*
	sizeSum = size[0] + size[1];
	char* buffer;
	i = 18;
	buffer = (char*)malloc((sizeSum) * i);
	for (; i >= 1 && buffer == NULL; i--) {
		buffer = (char*)malloc((sizeSum)*i);
		if (buffer != NULL) {
			break;
		}
	}
	setvbuf(stdout, buffer, _IOFBF, (size[0] + size[1]) * i);
	*/


	/*
	표준 출력을 파일 출력으로 redirecting
	*/
	//freopen("output.txt", "w", stdout);


	/*
	다항식 덧셈 및 출력
	*/
	l = 0; r = 0;
	printFlag = 0;
	while (l < size[0] && r < size[1]) {
		if (arr[0][l][expo] > arr[1][r][expo]) {
			coefficient = arr[0][l][coef];
			exponential = arr[0][l][expo];
			l++;
		}
		else if (arr[0][l][expo] < arr[1][r][expo]) {
			coefficient = arr[1][r][coef];
			exponential = arr[1][r][expo];
			r++;
		}
		else {
			coefficient = arr[1][r][coef] + arr[0][l][coef];
			exponential = arr[1][r][expo];
			l++; r++;
		}

		if (coefficient == 0) {
			continue;
		}
		else if (printFlag == 1) {
			if (coefficient > 0) {
				//printf(" + %dx^%d", coefficient, exponential);
				continue;
			}
			else {
				//printf(" - %dx^%d", -1 * coefficient, exponential);
				continue;
			}
		}
		else {
			printFlag = 1;
			//printf("%dx^%d", coefficient, exponential);
			continue;
		}
	}

	while (l < size[0]) {
		if (arr[0][l][coef] == 0) {
			l++;
			continue;
		}
		else if (printFlag == 1) {
			if (coefficient > 0) {
				//printf(" + %dx^%d", arr[0][l][coef], arr[0][l][expo]);
				l++;
				continue;
			}
			else {
				//printf(" - %dx^%d", -1 * arr[0][l][coef], arr[0][l][expo]);
				l++;
				continue;
			}
		}
		else {
			printFlag = 1;
			//printf("%dx^%d", arr[0][l][coef], arr[0][l][expo]);
			l++;
			continue;
		}
	}
	while (r < size[1]) {
		if (arr[1][r][coef] == 0) {
			r++;
			continue;
		}
		else if (printFlag == 1) {
			if (coefficient > 0) {
				//printf(" + %dx^%d", arr[1][r][coef], arr[1][r][expo]);
				r++;
				continue;
			}
			else {
				//printf(" - %dx^%d", -1 * arr[1][r][coef], arr[1][r][expo]);
				r++;
				continue;
			}
		}
		else {
			printFlag = 1;
			//printf("%dx^%d", arr[1][r][coef], arr[1][r][expo]);
			r++;
			continue;
		}
	}
	fflush(stdout);
	end = clock();
	printf("\n%.5f sec\n", (double)((double)end - start) / CLOCKS_PER_SEC);
	fflush(stdout);
	return 0;
}