#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int stack[10001][3];
int sorted[10001][2];
int arr[2][10001][2];

enum {
	coef = 0, expo = 1
};

void mergeSort(int arr[][2], int size) {
	int top = 0;
	int k, m;
	int l = 0, r = size - 1, flag = 0;
	int left, right;
	stack[top][0] = l;
	stack[top][1] = r;
	stack[top][2] = 0;
	top++;

	while (top != 0) {
		top--;
		l = stack[top][0]; r = stack[top][1]; flag = stack[top][2];
		while (1) {
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
				memcpy(&arr[l][0], &sorted[0][0], (r - l + 1) * sizeof(int[2]));
				break;
			}
		}
	}
}

int main() {
	//arr[polynomial][term][coef / expo]
	FILE* fp = freopen("input.txt", "r", stdin);
	clock_t start, end;
	start = clock();
	int size[2] = { 0, 0 };
	int sizeSum;
	char ch;
	char* buffer;
	int T = 0, l , r, count;

	while (scanf("%c", &ch) != EOF) {
		if (ch != '(') {
			T = 1;
			continue;
		}
		scanf("%d,%d)", &arr[T][size[T]][coef], &arr[T][size[T]][expo]);
		size[T]++;
	}

	fclose(fp);
	mergeSort(arr[0], size[0]);
	mergeSort(arr[1], size[1]);
	sizeSum = size[0] + size[1];
	buffer = (char*)malloc((sizeSum) * 18);
	setvbuf(stdout, buffer, _IOFBF, (size[0] + size[1]) * 18);
	l = 0; r = 0; count = 0;
	while (l < size[0] && r < size[1]) {
		if (arr[0][l][expo] > arr[1][r][expo]) {
			printf("%dx^%d", arr[0][l][coef], arr[0][l][expo]);
			l++;
			count++;
		}
		else if (arr[0][l][expo] < arr[1][r][expo]) {
			printf("%dx^%d", arr[1][r][coef], arr[1][r][expo]);
			r++;
			count++;
		}
		else {
			printf("%dx^%d", arr[1][r][coef] + arr[0][l][coef], arr[0][l][expo]);
			l++; r++;
			count += 2;
		}
		if (count < sizeSum) {
			printf(" + ");
		}
	}
	while (l < size[0]) {
		printf("%dx^%d", arr[0][l][coef], arr[0][l][expo]);
		l++;
		if (l < size[0]) {
			printf(" + ");
		}
	}
	while (r < size[1]) {
		printf("%dx^%d", arr[1][r][coef], arr[1][r][expo]);
		r++;
		if (r < size[1]) {
			printf(" + ");
		}
	}
	fflush(stdout);
	end = clock();
	printf("\n%.5f sec\n", (double)((double)end - start) / CLOCKS_PER_SEC);
	fflush(stdout);
	return 0;
}