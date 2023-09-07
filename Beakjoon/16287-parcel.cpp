#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <string.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<pair<int, ii>> viii;

bool compare(const pair<int, ii>& a, const pair<int, ii>& b) {
    return a.first < b.first;
}


viii derivedArr;
vi arr;

int arrsize;
int goal;


int main() {
    scanf("%d %d", &goal, &arrsize);
    bool found = false;
    int w;
    int newSize = arrsize * (arrsize - 1);
    newSize /= 2;
    viii::iterator upper;
    for (int i = 0; i < arrsize; i++) {
        scanf("%d", &w);
        arr.push_back(w);
    }

    for (int i = 0; i < arrsize - 1; i++) {
        for (int j = i + 1; j < arrsize; j++) {
            derivedArr.push_back(make_pair(arr[i] + arr[j], make_pair(i, j)));
        }
    }
    sort(derivedArr.begin(), derivedArr.end());


    for (int i = 0; i < newSize - 1; i++) {
        w = goal - derivedArr[i].first;
        if (w < derivedArr[i].first) {
            break;
        }

        upper = lower_bound(derivedArr.begin(), derivedArr.end(), make_pair(w, make_pair(0, 0)), compare);
        
        for (viii::iterator iter = upper; iter != derivedArr.end(); iter++) {
            if ((*iter).first != w) {
                break;
            }
            else if (derivedArr[i].second.first == (*iter).second.first || derivedArr[i].second.first == (*iter).second.second) {
                continue;
            }
            else if (derivedArr[i].second.second == (*iter).second.first || derivedArr[i].second.second == (*iter).second.second) {
                continue;
            }
            else {
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }

    if (found) {
        printf("YES");
    }
    else {
        printf("NO");
    }
    return 0;
}