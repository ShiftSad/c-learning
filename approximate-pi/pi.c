#include <stdio.h>

long double gregoryLeibnizSeries(int n);

int main() {
    const int n = 1e9;

    printf("Gregory Leibniz >> %Lf\n", gregoryLeibnizSeries(n));

    return 0;
}

// Thanks https://en.wikipedia.org/wiki/Pi :)
long double gregoryLeibnizSeries(int n) {
    long double pi = 0.0;

    for (int i = 0; i < n; i++) {
        pi += (i % 2 == 0 ? 1.0 : -1.0) / (2.0 * i + 1.0);
    }

    pi *= 4;

    return pi;
}