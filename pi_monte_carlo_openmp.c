#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>

int main(int argc, char *argv[]) {
    long long num_points = 1000000000LL;  // 預設 10 億點
    long long inside_circle = 0;
    double start_time, end_time;

    if (argc > 1) {
        num_points = atoll(argv[1]);
    }

    printf("開始計算，使用 %lld 個點...\n", num_points);

    start_time = omp_get_wtime();

    #pragma omp parallel reduction(+:inside_circle)
    {
        unsigned int seed = omp_get_thread_num() + time(NULL);
        long long local_count = 0;

        // 每個執行緒自己算一部分
        #pragma omp for
        for (long long i = 0; i < num_points; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1.0) {
                local_count++;
            }
        }
        inside_circle += local_count;
    }

    double pi_estimate = 4.0 * inside_circle / num_points;
    end_time = omp_get_wtime();

    printf("估算 π 值: %.10f\n", pi_estimate);
    printf("實際 π 值: 3.1415926535\n");
    printf("執行時間: %.3f 秒\n", end_time - start_time);
    printf("使用核心數: %d\n", omp_get_max_threads());

    return 0;
}