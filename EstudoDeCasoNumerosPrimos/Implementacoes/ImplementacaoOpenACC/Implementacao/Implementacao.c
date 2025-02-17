#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int is_prime(int n) {
    if (n <= 1)
        return 0;
    if (n <= 3)
        return 1;
    if (n % 2 == 0 || n % 3 == 0)
        return 0;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    }
    return 1;
}

int main() {
    int lower_bound = 1;
    int upper_bound = 1000000; // Defina o intervalo desejado
    int count = 0;

    clock_t start, end;

    start = clock();

    #pragma acc parallel loop reduction(+:count)
    for (int i = lower_bound; i <= upper_bound; i++) {
        count += is_prime(i);
    }

    end = clock();
    double execution_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Número de primos encontrados: %d\n", count);
    printf("Tempo de execução: %f segundos\n", execution_time);

    return 0;
}

