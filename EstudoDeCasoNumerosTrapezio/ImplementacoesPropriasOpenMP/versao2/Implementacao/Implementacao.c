//versao 2


#include <stdio.h>
#include <math.h>
#include <omp.h>

double f(double x) {
    return exp(x);
}

double trap(double a, double b, long long n) {
    double h = (b - a) / n;
    double sum = 0.0;

#pragma omp parallel for reduction(+:sum) schedule(static)
    for (long long i = 1; i < n; ++i) {
        double x = a + i * h;
        sum += f(x);
    }

    sum += (f(a) + f(b)) / 2.0;

    return h * sum;
}

int main() {
    long long n = 128000000000; 
    double a = 0.0; 
    double b = 1.0; 

    double t_inicio = omp_get_wtime();

    double integral = trap(a, b, n);

    double t_fim = omp_get_wtime();

    printf("Integral da funcao exponencial de %f a %f: %f\n", a, b, integral);
    printf("Com n = %lld trapezoides\n", n);
    printf("Tempo de execucao: %f segundos\n", t_fim - t_inicio);
    printf("Numero de threads em execucao: %d\n", omp_get_max_threads());

    return 0;
}
