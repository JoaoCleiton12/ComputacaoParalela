//versao 1

#include <stdio.h>
#include <math.h>
#include <omp.h>

double f(double x) {
    double valor;
    valor = exp(x);
    return valor;
}

int main(int argc, char* argv[]) {
    double integral = 0.0; 

    double a = 0.0, b = 1.0; 

    long long n = 128000000000; 

    double h = (b - a) / n;

    double t_inicio = omp_get_wtime();

    omp_set_num_threads();

    int num_threads = omp_get_num_procs(); 



#pragma omp parallel num_threads(num_threads)
    {
        double local_integral = 0.0;
        long long local_n = n / num_threads; 
        double local_h = (b - a) / n;


        //início e fim para uma thread
        long long local_inicio = omp_get_thread_num() * local_n + 1;
        long long local_fim = local_inicio + local_n;

        // Calcular a integral local
        for (long long i = local_inicio; i < local_fim; i++) {
            double x = a + i * local_h;
            local_integral += f(x);
        }

        // Adicionar a integral local 
        #pragma omp atomic
        integral += local_integral;
    }

    integral = (integral + (f(a) + f(b)) / 2.0) * h;

    double t_fim = omp_get_wtime();

    printf("Com n = %llu trapezoides, a estimativa \n", n);
    printf("da integral de %f ate %f = %lf \n", a, b, integral);
    printf("Tempo: \t %f com %d threads.\n", t_fim - t_inicio, num_threads);

    return 0;
}
