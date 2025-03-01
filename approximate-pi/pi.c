#include <stdio.h>
#include <math.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
    #include <process.h> // For _beginthreadex
    typedef HANDLE thread_t;
#else
    #include <pthread.h>
    typedef pthread_t thread_t;
#endif

typedef long double (*piFunc)(int);

// Structure to hold data for each thread.
typedef struct {
    const char *methodName;
    piFunc func;
    int n;
} ThreadData;

// Get wall time in seconds (cross-platform)
double get_wall_time() {
    #ifdef _WIN32
        LARGE_INTEGER time, freq;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&time);
        return (double)time.QuadPart / freq.QuadPart;
    #else
        struct timespec ts;
        clock_gettime(1, &ts);
        return ts.tv_sec + ts.tv_nsec / 1e9;
    #endif
}
    
// https://stackoverflow.com/questions/74210984/how-to-achieve-parallelism-in-c :)
#ifdef _WIN32
unsigned __stdcall thread_function(void *arg) {
#else
void *thread_function(void *arg) {
#endif
    ThreadData *data = (ThreadData *)arg;
    double start = get_wall_time();
    long double result = data->func(data->n);
    double end = get_wall_time();
    double elapsed = end - start;

    printf("%s >> %.8Lf (Elapsed time: %.5f seconds)\n", data->methodName, result, elapsed);
#ifdef _WIN32
    _endthreadex(0);
    return 0;
#else
    return NULL;
#endif
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
    thread_t  threads[2];
    ThreadData data1 = {"Gregory Leibniz", gregoryLeibnizSeries, n};
    ThreadData data2 = {"Basel Problem", baselProblem, n};

#ifdef _WIN32
    threads[0] = (HANDLE)_beginthreadex(NULL, 0, thread_function, &data1, 0, NULL);
    threads[1] = (HANDLE)_beginthreadex(NULL, 0, thread_function, &data2, 0, NULL);

    // Wait for both threads to finish
    WaitForMultipleObjects(2, threads, TRUE, INFINITE);

    CloseHandle(threads[0]);
    CloseHandle(threads[1]);
#else
    pthread_create(&threads[0], NULL, thread_function, &data1);
    pthread_create(&threads[1], NULL, thread_function, &data2);

    // Wait for both threads to finish
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
#endif

    return 0;
}