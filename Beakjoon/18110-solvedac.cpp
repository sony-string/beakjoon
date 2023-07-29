#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <assert.h>
using namespace std;


typedef vector<int> vi;


int main() {
	int countPolls;
	int poll;
	int cutline;
	int sumPolls;
	vi pollArr;

	scanf("%d", &countPolls);

	if (countPolls != 0) {
		for (int i = 0; i < countPolls; i++) {
			scanf("%d", &poll);
			pollArr.push_back(poll);
		}

		sort(pollArr.begin(), pollArr.end());
		cutline = (int)round(countPolls * 0.15);

		if (countPolls - 2 * cutline <= 0) {
			printf("0");
		}
		else {

			sumPolls = 0;
			for (int i = cutline; i < countPolls - cutline; i++) {
				sumPolls += pollArr[i];
			}

			printf("%d", (int)round((double)sumPolls / (countPolls - 2 * cutline)));
		}
	}
	else {
		printf("0");
	}

	return 0;
}