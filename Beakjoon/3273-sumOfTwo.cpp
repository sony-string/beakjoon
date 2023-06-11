#include <algorithm>
#include <stdio.h>
#include <vector>
using namespace std;


int main() {
	int size;
	vector<int> arr;
	int num;
	int sum = 0;
	int x, diff;
	scanf("%d", &size);
	for (int i = 0; i < size; i++) {
		scanf("%d", &num);
		arr.push_back(num);
	}
	scanf("%d", &x);
	sort(arr.begin(), arr.end());
	int lower, upper;
	
	for (int i = 0; i < size - 1; i++) {
		diff = x - arr[i];
		lower = lower_bound(arr.begin() + i + 1, arr.end(), diff) - arr.begin();
		upper = upper_bound(arr.begin() + i + 1, arr.end(), diff) - arr.begin();
		if (arr[lower] != diff) {
			continue;
		}
		else {
			sum += upper - lower;
		}
	}

	printf("%d", sum);
	return 0;
}