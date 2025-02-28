#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

typedef long double (*piFunc)(int);

// Structure to hold data for each thread.
typedef struct {
    const char *methodName;
    piFunc func;
    int n;
} ThreadData;

void *thread_function(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    clock_t start = clock();
    long double result = data->func(data->n);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%s >> %.8Lf (Time: %.5f seconds)\n", data->methodName, result, time_taken);
    
    return NULL;
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
    const int n = 1e9;

    // 2 threads for 2 functions
    pthread_t threads[2];
    ThreadData data1 = {"Gregory Leibniz", gregoryLeibnizSeries, n};
    ThreadData data2 = {"Basel Problem", baselProblem, n};

    pthread_create(&threads[0], NULL, thread_function, &data1);
    pthread_create(&threads[1], NULL, thread_function, &data2);

    // Wait for both threads to finish.
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    return 0;
}