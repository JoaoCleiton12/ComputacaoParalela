//IMPLEMENTAÇÃO PRÓPRIA 2

#include <iostream>
#include <omp.h>
#include <cmath>

bool primo(long int n) {
    long int i;
    if (n < 2) {
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
#pragma omp parallel reduction(+:count)
    {
        double t_inicio_thread = omp_get_wtime();
#pragma omp for
        for (int i = start; i <= end; ++i) {
            if (primo(i))
                count++;
        }
        double t_fim_thread = omp_get_wtime(); 
        printf("Thread %d: Tempo de execucao: %f\n", omp_get_thread_num(), t_fim_thread - t_inicio_thread);
    }
    return count;
}

int main() {
    int end = 70000; 

    
    omp_set_num_threads();

    double t_inicio = omp_get_wtime();

    int total = contarprimos(1, end);

    double t_fim = omp_get_wtime(); 

    printf("Quant. de primos entre 1 e %d: %d\n", end, total);
    printf("Tempo total de execucao: %f\n", t_fim - t_inicio);

    return 0;
}
