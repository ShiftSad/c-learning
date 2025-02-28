#include <stdio.h>
#include <math.h>
#include <time.h>

typedef long double (*piFunc)(int);

void printResult(const char *methodName, piFunc func, int n) {
    clock_t start = clock();
    long double result = func(n);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("%s >> %.8Lf (Time: %.5f seconds)\n", methodName, result, time_taken);
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

int main() {
    const int n = 1e5;

    printResult("Gregory Leibniz", gregoryLeibnizSeries, n);
    printResult("Basel Problem", baselProblem, n);

    return 0;
}