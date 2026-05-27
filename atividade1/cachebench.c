#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_BYTES (64 * 1024 * 1024) 

int main() {
    int *array = (int *)malloc(MAX_BYTES);
    if (!array) {
        printf("Erro ao alocar memoria\n");
        return 1;
    }

    int max_elements = MAX_BYTES / sizeof(int);
    for (int i = 0; i < max_elements; i++) {
        array[i] = 0;
    }

    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);

    printf("Tamanho_KB,Tempo_NS\n");

    for (size_t bytes = 4 * 1024; bytes <= MAX_BYTES; bytes *= 2) {
        size_t elements = bytes / sizeof(int);
        size_t mask = elements - 1;
        size_t steps = 64 * 1024 * 1024; 

        LARGE_INTEGER start, end;
        QueryPerformanceCounter(&start);

        volatile int *volatile_array = array;
        int accumulator = 0; 
        size_t p = 0;
        
        for (size_t i = 0; i < steps; i++) {
            p = (p + 31) & mask;
            accumulator += volatile_array[p];
        }

        QueryPerformanceCounter(&end);

        if (accumulator == 999999) printf(" "); 

        double total_time_ns = ((double)(end.QuadPart - start.QuadPart) * 1000000000.0) / (double)frequency.QuadPart;frequency.QuadPart;
        double time_per_access = total_time_ns / steps;

        printf("%lu,%0.2f\n", (unsigned long)(bytes / 1024), time_per_access);
    }

    free(array);
    return 0;
}