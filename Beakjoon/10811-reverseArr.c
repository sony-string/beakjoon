#include <stdio.h>

int main()
{
    int a[101] = { 0 };
    int i, n, m, k;
    int q, w;
    int temp = 0;
    scanf("%d %d", &n, &m);

    for (i = 0; i <= n; i++) {
        a[i] = i;
    }

    for (i = 0; i < m; i++) {
        scanf("%d %d", &q, &w);
        for (k = w; k >= q; k--) {
            temp = a[k];
            a[k] = a[q];
            a[q] = temp;
            q++;
        }
    }

    for (i = 1; i <= n; i++) {
        printf("%d ", a[i]);
    }

    return 0;
}
