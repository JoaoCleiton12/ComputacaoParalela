#include <stdio.h>
#include <math.h>
#include <mpi.h>

double f(double x) {
    return exp(x);
}

int main(int argc, char* argv[]) {
    int rank, size;
    double total_integral;

    double a = 0.0, b = 1.0;
    long long n = 63000000000;
    double h;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    h = (b - a) / n;

    double t_inicio = MPI_Wtime();

    double integral = 0.0;
    for (long long i = rank + 1; i <= n; i += size) {
        integral += f(a + i * h);
    }
    integral *= h;

    MPI_Reduce(&integral, &total_integral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    double t_fim = MPI_Wtime();

    if (rank == 0) {
       
        printf("Com n = %lld trapezoides, a estimativa\n", n);
        printf("da integral de %f ate %f = %lf\n", a, b, total_integral);
        printf("Tempo de execucao: %f segundos\n", t_fim - t_inicio);
    }

    MPI_Finalize();
    return 0;
}
