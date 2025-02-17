#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int primo(long int n) {
    long int i;
    for (i = 3; i < (long int)(sqrt(n) + 1); i += 2)
        if (n % i == 0) return 0;
    return 1;
}

int main(int argc, char* argv[]) {
    double t_inicio, t_fim;
    long int i, n, total;
    int num_threads;
    double** tempos;

    omp_set_num_threads(1);
    if (argc < 2) {
        printf("Valor invalido! Entre com o valor do maior inteiro\n");
        return 0;
    }
    else {
        n = strtol(argv[1], (char**)NULL, 10);
    }
    total = 0;
    t_inicio = omp_get_wtime();
    num_threads = omp_get_max_threads();
    tempos = (double**)malloc(num_threads * sizeof(double*));
    for (int k = 0; k < num_threads; k++) {
        tempos[k] = (double*)malloc(sizeof(double));
    }

    /* Solução trivial */
#pragma omp parallel private(i, t_inicio, t_fim)
    {
        int tid = omp_get_thread_num();
        double tempo_local = 0.0;

#pragma omp for reduction(+:total) schedule(static)
        for (i = 3; i <= n; i += 2) {
            t_inicio = omp_get_wtime();
            if (primo(i) == 1) total++;
            t_fim = omp_get_wtime();
            tempo_local += t_fim - t_inicio;
        }

        tempos[tid][0] = tempo_local;
    }

    /* Acrescenta o dois, que também é primo */
    total += 1;
    t_fim = omp_get_wtime();

    printf("Quant. de primos entre 1 e %ld: %ld\n", n, total);
    printf("Tempo total de execucao: %f com %d threads\n", t_fim - t_inicio, num_threads);

    printf("Tempo de execucao de cada thread:\n");
    for (int j = 0; j < num_threads; j++) {
        printf("Thread %d: %f\n", j, tempos[j][0]);
        free(tempos[j]);
    }
    free(tempos);

    return 0;
}
