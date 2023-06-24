#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct window {
	string title;
	int width, height;
	window(int w, int h, string titleString) {
		width = w;
		height = h;
		title = titleString;
	}

	bool operator<(const window& op) {
		return this->title < op.title;
	}
};

vector<window> windows;
int N, M;
char** screen;


void drawWindow(const window& win, int leftUpperPos[2]) {
	int titleLeftPadding = win.width - win.title.length();
	titleLeftPadding /= 2;

	int pos[2] = { leftUpperPos[0], leftUpperPos[1] };
	screen[pos[0]][pos[1]] = '+';
	screen[pos[0] + win.height - 1][pos[1]] = '+';
	screen[pos[0] + win.height - 1][pos[1] + win.width - 1] = '+';
	screen[pos[0]][pos[1] + win.width - 1] = '+';

	for (int i = 1; i < win.width - 1; i++) {
		if (i == titleLeftPadding) {
			screen[pos[0]][pos[1] + i - 1] = '|';
			for (auto ch : win.title) {
				screen[pos[0]][pos[1] + i] = ch;
				screen[pos[0] + win.height - 1][pos[1] + i] = '-';
				i++;
			}
			screen[pos[0]][pos[1] + i] = '|';
			screen[pos[0] + win.height - 1][pos[1] + i] = '-';
			continue;
		}
		screen[pos[0]][pos[1] + i] = '-';
		screen[pos[0] + win.height - 1][pos[1] + i] = '-';
	}
	for (int i = 1; i < win.height - 1; i++) {
		screen[pos[0] + i][pos[1]] = '|';
		screen[pos[0] + i][pos[1] + win.width - 1] = '|';
	}
	for (int r = 1; r < win.height - 1; r++) {
		memset(&screen[pos[0] + r][pos[1] + 1], '.', sizeof(char) * win.width - 2);
	}
}


int main() {
	string title;
	char* titleCharArr = new char[13];
	bool** isChecked;
	int width, height;
	int pos[2] = { 0, 0 };

	scanf("%d %d", &M, &N);
	screen = new char* [M];
	isChecked = new bool* [M];
	for (int i = 0; i < M; i++) {
		screen[i] = new char[N + 1];
		isChecked[i] = new bool[N];
		memset(isChecked[i], false, sizeof(bool) * N);
		scanf("%s", screen[i]);
	}

	for (int r = 0; r < M; r++) {
		for (int c = 0; c < N; c++) {
			if (isChecked[r][c]) {
				continue;
			}
			isChecked[r][c] = true;
			if (screen[r][c] == '+') {
				pos[0] = r;
				pos[1] = c + 1;
				while (screen[pos[0]][pos[1]] != '+') {
					if (isalpha(screen[pos[0]][pos[1]])) {
						int len = 0;
						while (isalpha(screen[pos[0]][pos[1]])) {
							titleCharArr[len] = screen[pos[0]][pos[1]];
							len++;
							pos[1] += 1;
						}
						titleCharArr[len] = '\0';
						title = titleCharArr;
						continue;
					}
					pos[1] += 1;
				}

				width = pos[1] - c + 1;
				pos[0] += 1;

				while (screen[pos[0]][pos[1]] != '+') {
					pos[0] += 1;
				}

				height = pos[0] - r + 1;

				windows.push_back(window(width, height, title));
				for (int i = 0; i < height; i++) {
					memset(&isChecked[r + i][c], true, sizeof(bool) * width);
				}
			}
		}
	}

	sort(windows.begin(), windows.end());
	for (int i = 0; i < M; i++) {
		memset(screen[i], '.', sizeof(char) * N);
		screen[i][N] = '\0';
	}
	pos[0] = 0;
	pos[1] = 0;
	for (auto window : windows) {
		drawWindow(window, pos);
		pos[0] += 1;
		pos[1] += 1;
	}
	for (int i = 0; i < M; i++) {
		printf("%s\n", screen[i]);
	}
	return 0;
}