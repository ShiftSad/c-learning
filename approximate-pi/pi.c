#include <stdio.h>
#include <math.h>

long double gregoryLeibnizSeries(int n);
long double baselProblem(int n);

int main() {
    const int n = 1e9;

    printf("Gregory Leibniz >> %.12Lf\n", gregoryLeibnizSeries(n));
    printf("Basel Problem >> %.12Lf \n", baselProblem(n));

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

// Thanks https://en.wikipedia.org/wiki/Pi :)
long double baselProblem(int n) {
    long double pi = 0.0;
    long double one = 1.0;

    for (long double i = 1; i < n; i++) {
        pi += (one / (i * i));
    }

    pi *= 6.0L;
    pi = sqrtl(pi);

    return pi;
}