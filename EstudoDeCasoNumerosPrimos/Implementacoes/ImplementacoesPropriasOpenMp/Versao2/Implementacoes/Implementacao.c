//IMPLEMENTAÇÃO PRÓPRIA 2

#include <iostream>
#include <omp.h>

bool primo(long int n) {
    long int i;
    if (n < 2)
    {
        return false;
    }
    else {
        for (int i = 2; i <= sqrt(n); ++i) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }
}

int contarprimos(int start, int end) {
    int count = 0;
#pragma omp parallel for reduction(+:count)
    for (int i = start; i <= end; ++i) {
        if (primo(i))
            count++;
    }
    return count;
}

int main() {
    int end = 700000000; 

    omp_set_num_threads(12);

    double t_inicio = omp_get_wtime(); 

    int total = contarprimos(1, end);

    double t_fim = omp_get_wtime();

    printf("Quant. de primos entre 1 e %ld: %ld\n", end, total);
    printf("Tempo de execucao: %f com %d threads\n", t_fim - t_inicio, omp_get_max_threads());


    return 0;
}
