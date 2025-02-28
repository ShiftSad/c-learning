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

// Thanks chatgpt
double get_wall_time() {
    struct timespec ts;
    clock_gettime(1, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

// https://stackoverflow.com/questions/74210984/how-to-achieve-parallelism-in-c :)
void *thread_function(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    double start = get_wall_time();
    long double result = data->func(data->n);
    double end = get_wall_time();
    double elapsed = end - start;

    printf("%s >> %.8Lf (Elapsed time: %.5f seconds)\n", data->methodName, result, elapsed);
    return NULL;
}

// Thanks https://en.wikipedia.org/wiki/Pi :)
long double gregoryLeibnizSeries(int n) {
    long double pi = 0.0L;

    for (int i = 0; i < n; i++) {
        pi += (i % 2 == 0 ? 1.0L : -1.0L) / (2.0L * i + 1.0L);
    }

    return pi *= 4;
}

// Thanks https://en.wikipedia.org/wiki/Pi :)
long double baselProblem(int n) {
    long double pi = 0.0;

    for (long double i = 1; i < n; i++) {
        pi += (1.0L / (i * i));
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