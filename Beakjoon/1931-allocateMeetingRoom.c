#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main() {
	int numMeetings, i, max = 0, start, end;
	int  index, parent, left, right, smaller;
	scanf("%d", &numMeetings);
	int** Heap = (int**)malloc(numMeetings * sizeof(int*));
	int** arr = (int**)malloc(numMeetings * sizeof(int*));
	for (i = 0; i < numMeetings; i++) {
		Heap[i] = (int*)malloc(2 * sizeof(int));
		arr[i] = (int*)malloc(2 * sizeof(int));
	}
	for (i = 0; i < numMeetings; i++) {
		scanf(" %d %d", &start, &end);
		index = i;
		Heap[index][0] = start;
		Heap[index][1] = end;
		while (index > 0) {
			parent = (index - 1) / 2;
			if (Heap[parent][1] > end) {
				swap(&Heap[index][0], &Heap[parent][0]);
				swap(&Heap[index][1], &Heap[parent][1]);
			}
			else if (Heap[parent][1] == end) {
				if (Heap[parent][0] > start) {
					swap(&Heap[index][0], &Heap[parent][0]);
					swap(&Heap[index][1], &Heap[parent][1]);
				}
			}
			index = parent;
		}
	}
	for (i = 0; i < numMeetings; i++) {
		arr[i][0] = Heap[0][0];
		arr[i][1] = Heap[0][1];
		Heap[0][0] = Heap[numMeetings - 1 - i][0];
		Heap[0][1] = Heap[numMeetings - 1 - i][1];
		index = 0;
		while (index < numMeetings - 1 - i) {
			left = index * 2 + 1, right = index * 2 + 2;
			if (right < numMeetings - 1 - i) {
				if (Heap[left][1] < Heap[right][1]) {
					smaller = left;
				}
				else if (Heap[left][1] == Heap[right][1]) {
					if (Heap[left][0] < Heap[right][0]) {
						smaller = left;
					}
					else {
						smaller = right;
					}
				}
				else {
					smaller = right;
				}
			}
			else if (left == numMeetings - 2 - i) 
			{
				smaller = left;
			}
			else {
				break;
			}
			if (Heap[smaller][1] < Heap[index][1]) {
				swap(&Heap[smaller][0], &Heap[index][0]);
				swap(&Heap[smaller][1], &Heap[index][1]);
				index = smaller;
			}
			else if (Heap[smaller][1] == Heap[index][1]) {
				if (Heap[smaller][0] < Heap[index][0]) {
					swap(&Heap[smaller][0], &Heap[index][0]);
					swap(&Heap[smaller][1], &Heap[index][1]);
					index = smaller;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
	}
	end = arr[0][1];
	int count = 1;
	for (i = 1; i < numMeetings; i++) {
		if (arr[i][0] >= end) {
			end = arr[i][1];
			count++;
		}
	}
	printf("%d", count);
	return 0;
}