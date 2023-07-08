#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;


#define fori(a) for(int i = 0; i < a; i++)
#define fork(a) for(int k = 0; k < a; k++)


typedef long long li;
typedef pair<li, li> ii;
typedef vector<li> vi;
typedef vector<ii> vii;


int main() {
	li t, s, m, curt;
	int N;
	vii jobs;

	scanf("%d", &N);
	fori(N) {
		scanf("%lld %lld", &t, &s);
		jobs.emplace_back(s, t);
	}

	sort(jobs.begin(), jobs.end());
	m = 1e9;
	curt = 0;
	for (const auto& job : jobs) {
		curt += job.second;
		if (curt > job.first) {
			m = -1;
			break;
		}
		else {
			m = min(job.first - curt, m);
		}
	}

	printf("%lld", m);
	return 0;
}