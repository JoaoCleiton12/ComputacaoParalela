#include <iostream>
#include <mpi.h>
#include <iomanip>

bool primo( int n) {
    int i;
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

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N = 7000;
    int intervalStart = 1 + (N / size) * rank;
    int intervalEnd = (rank == size - 1) ? N : (N / size) * (rank + 1);
    int localCount = 0;

    double startTime, endtime;

    if (rank == 0)
    {
        startTime = MPI_Wtime();
    }

    for (int i = intervalStart; i <= intervalEnd; ++i) {
        if (primo(i)) {
            localCount++;
        }
    }

    int globalCount;
    MPI_Reduce(&localCount, &globalCount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);



    if (rank == 0) {
        endtime = MPI_Wtime(); 
        printf("Total de numeros primos no intervalo [1, %d]: %d\n", N, globalCount);
        printf("Tempo de execucao: %.7f segundos\n", endtime - startTime);
    }

    MPI_Finalize();
    return 0;
}
