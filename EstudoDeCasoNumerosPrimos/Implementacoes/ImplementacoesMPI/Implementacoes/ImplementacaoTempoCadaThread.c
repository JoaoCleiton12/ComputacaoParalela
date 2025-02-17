#include <iostream>
#include <mpi.h>
#include <iomanip>

bool Primo(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N = 700000000; // Limite superior do intervalo
    int intervalStart = 1 + (N / size) * rank;
    int intervalEnd = (rank == size - 1) ? N : (N / size) * (rank + 1);
    int localCount = 0;

    double startTime, endTime;

    startTime = MPI_Wtime(); // Inicia a contagem do tempo

    for (int i = intervalStart; i <= intervalEnd; ++i) {
        if (Primo(i)) {
            localCount++;
        }
    }

    endTime = MPI_Wtime(); // Termina a contagem do tempo

    int globalCount;
    MPI_Reduce(&localCount, &globalCount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    double* allTimes = nullptr;
    if (rank == 0) {
        allTimes = new double[size];
    }

    MPI_Gather(&endTime, 1, MPI_DOUBLE, allTimes, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        std::cout << "Total de numeros primos no intervalo [1, " << N << "]: " << globalCount << std::endl;
        std::cout << "Tempo de execucao de cada thread:" << std::endl;
        for (int i = 0; i < size; ++i) {
            std::cout << "Thread " << i << ": " << allTimes[i] - startTime << " segundos" << std::endl;
        }
        delete[] allTimes;
    }

    MPI_Finalize();
    return 0;
}
