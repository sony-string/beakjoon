#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;


typedef long long li;
typedef vector<li> vi;


int main() {
	li len;
	li counter[26];
	vi chPos[26];
	li removeCount = 0;
	li tempCount = 0;
	memset(counter, 0, sizeof(li) * 26);
	char* str;
	scanf("%lld", &len);
	str = new char[len + 1];
	scanf("%s", str);

	for (int i = 0; i < len; i++) {
		counter[str[i] - 'a'] += 1;
		chPos[str[i] = 'a'].push_back(i);
	}

	removeCount = len;
	for (int i = 1; i < len; i++) {
		
	}
}