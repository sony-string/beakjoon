#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;

int main() {
	int len;
	bool isSuccess = true;
	char* name = new char[51];
	char* palindrom = new char[51];
	char middle = 0;
	int idx;
	deque<char> nameCharVector;

	scanf("%s", name);
	len = strlen(name);
	for (int i = 0; i < len; i++) {
		nameCharVector.push_back(name[i]);
	}

	sort(nameCharVector.begin(), nameCharVector.end());
	
	idx = 0;
	isSuccess = true;
	while (!nameCharVector.empty()) {
		if (nameCharVector.size() >= 2) {
			if (nameCharVector[0] == nameCharVector[1]) {
				palindrom[idx] = nameCharVector[0];
				palindrom[len - idx - 1] = nameCharVector[1];
				idx++;
				nameCharVector.pop_front();
				nameCharVector.pop_front();
			}
			else if (len % 2 == 1 && middle == 0) {
				middle = nameCharVector[0];
				nameCharVector.pop_front();
			}
			else {
				isSuccess = false;
				break;
			}
		}
		else {
			palindrom[idx] = nameCharVector[0];
			nameCharVector.pop_front();
		}
	}

	if (middle != 0) {
		palindrom[idx] = middle;
	}

	if (isSuccess) {
		palindrom[len] = 0;
		printf("%s", palindrom);
	}
	else {
		printf("I'm Sorry Hansoo");
	}
	
	return 0;
}