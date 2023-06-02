#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <algorithm>
using namespace std;

typedef long long li;

struct Point {
	int x, y;
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

Point pivot(0, 0);
bool angleCmp(Point* a, Point* b) {
	double d1x = a->x - pivot.x, d1y = a->y - pivot.y;
	double d2x = b->x - pivot.x, d2y = b->y - pivot.y;
	
	double angle1 = atan2(d1x, d1y), angle2 = atan2(d2x, d2y);
	if (angle1 == angle2) {
		return (d1x * d1x + d1y * d1y) < (d2x * d2x + d2y * d2y);
	}
	else {
		return angle1 < angle2;
	}
}


li ccwTest(Point* p, Point* q, Point* r) {
	li d1x, d1y, d2x, d2y;
	d1x = q->x - p->x;
	d1y = q->y - p->y;
	d2x = r->x - p->x;
	d2y = r->y - p->y;

	return (d1x * d2y) - (d1y * d2x);
}


int main() {
	int numPoints;
	Point** points;
	int x, y;
	Point* p, * q, * r;
	int lowest = 0;
	int top;
	li ccw;
	vector<Point> vertex;

	scanf("%d", &numPoints);
	points = new Point * [numPoints];
	for (int i = 0; i < numPoints; i++) {
		scanf("%d %d", &x, &y);
		points[i] = new Point(x, y);
		if (points[i]->y < points[lowest]->y) {
			lowest = i;
		}
		else if (points[i]->y == points[lowest]->y) {
			if (points[i]->x < points[lowest]->x) {
				lowest = i;
			}
		}
	}

	Point* temp = points[0];
	points[0] = points[lowest];
	points[lowest] = temp;
	pivot.x = points[0]->x;
	pivot.y = points[0]->y;
	sort(points + 1, points + numPoints, angleCmp);

	vertex.push_back(pivot);
	for (int i = 1; i < numPoints; i++) {
		top = vertex.size();
		if (top < 2) {
			vertex.push_back(*points[i]);
			continue;
		}
		p = &vertex[top - 2];
		q = &vertex[top - 1];
		r = points[i];
			
		ccw = ccwTest(p, q, r);
		while (ccw > 0 && top >= 3) {
			vertex.pop_back();
			top--;
			p = &vertex[top - 2];
			q = &vertex[top - 1];
			ccw = ccwTest(p, q, r);
		}
		if (ccw == 0) {
			vertex.pop_back();
		}
		vertex.push_back(*points[i]);
	}

	top = vertex.size();
	if (top >= 2) {
		p = &vertex[top - 2];
		q = &vertex[top - 1];
		r = points[0];

		ccw = ccwTest(p, q, r);
		while (ccw >= 0) {
			vertex.pop_back();
			top--;
			p = &vertex[top - 2];
			q = &vertex[top - 1];
			ccw = ccwTest(p, q, r);
		}
	}
	printf("%d", top);

	return 0;
}