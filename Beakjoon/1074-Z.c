#include <stdio.h>
#include <math.h>

/* 이진 탐색 2차원 배열 버전  */
 
int main() {
    int size, length, N, count = 1;
    int start[2];
    int row, col;
    scanf("%d %d %d", &N, &row, &col);
    
    length = (int)pow(2, N);
    size = length * length;
    start[0] = 0; start[1] = 0;

    while (size != 4) {
        if (row >= start[0] + (length / 2)) {
            start[0] += length / 2;
            count += size / 2;
            if (col >= start[1] + (length / 2)) {
                start[1] += length / 2;
                count += size / 4;
            }
        }
        else if (col >= start[1] + (length / 2)) {
            start[1] += length / 2;
            count += size / 4;
        }
        size /= 4;
        length /= 2;
    }

    count += (col - start[1]) + 2 * (row - start[0]);
    printf("%d", count - 1);

    return 0;
}