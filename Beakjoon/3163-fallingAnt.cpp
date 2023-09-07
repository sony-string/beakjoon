#include <iostream>
using namespace std;
#include <algorithm>
#include <queue>
#include <assert.h>



struct Falling {
	int l;
	int r;
	long long time;
	Falling(int ll , int rr, long long ttime) {
		l = ll;
		r = rr;
		time = ttime;
	}
	bool operator<(const Falling op) {
		return this->time > op.time;
	}
};


struct Ant {
	int id;
	long long pos;
	bool right;
};


int main() {
	priority_queue<Falling> q;
	Falling* e;
	
	Ant* arr;
	int cases;
	int id;
	long long pos, time, len;
	int l, r, k;
	int numAnt;

	scanf("%d", &cases);
	for (int T = 0; T < cases; T++) {
		scanf("%d", &numAnt);
		if (numAnt == 0) {
			break;
		}
		arr = new Ant[numAnt];
		scanf("%lld %d", &len, &k);
		for (int i = 0; i < numAnt; i++) {
			scanf("%lld %d", &pos, &id);
			arr[i].id = id;
			arr[i].pos = pos;
			arr[i].right = id > 0;
		}

		for (int i = 0; i < numAnt - 1; i++) {
			if (arr[i].right && !arr[i + 1].right) {
				e = new Falling(i, i + 1, (arr[i+1].pos - arr[i].pos) / 2))
			}
		}
	}
}