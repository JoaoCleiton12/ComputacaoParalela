//IMPLEMENTAÇÃO PRÓPRIA 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

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

int main(int argc, char* argv[]) {
    double t_inicio, t_fim, t_inicio_thread, t_fim_thread;
    long int i, n, total;
    double** tempos;

    omp_set_num_threads(8);

    n = 700000000;

    if (n < 2) {
        printf("Valor invalido! Entre com um valor maior inteiro\n");
        return 0;
    }
    total = 0;

    t_inicio = omp_get_wtime();

    int num_threads = omp_get_max_threads();
    tempos = (double**)malloc(num_threads * sizeof(double*)); 

    for (int k = 0; k < num_threads; k++) {
        tempos[k] = (double*)malloc(sizeof(double));
    }

#pragma omp parallel
    {
        int tid = omp_get_thread_num(); 
       // armazenar o tempo de execução local da thread
        double tempo_local = 0.0; 

        // local para cada thread
        long int local_total = 0; 

#pragma omp for schedule(dynamic ,10000)
        for (i = 3; i <= n; i += 2) {
            t_inicio_thread = omp_get_wtime();
            if (primo(i) == true)
                local_total++;
            t_fim_thread = omp_get_wtime(); 
            tempo_local += t_fim_thread - t_inicio_thread;
        }
        tempos[tid][0] = tempo_local;

        // Acrescenta o dois
        #pragma omp single
        total += 1;

        // Soma os totais locais 
        #pragma omp atomic
        total += local_total;

        t_fim = omp_get_wtime();

    }
    for (int j = 0; j < num_threads; j++) {
        printf("Thread %d: %f\n", j, tempos[j][0]); // Imprime o tempo de execução de cada thread.
        free(tempos[j]); // Libera a memória alocada para cada linha da matriz 'tempos'.
    }

    printf("Quant. de primos entre 1 e %ld: %ld\n", n, total);
    printf("Tempo total de execucao: %f com %d threads\n", t_fim - t_inicio,omp_get_max_threads());

    // Libera a memória 
    free(tempos); 
}