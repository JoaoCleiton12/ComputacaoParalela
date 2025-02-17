//IMPLEMENTAÇÃO PRÓPRIA 1


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <iostream>
using namespace std;

//verifica se é primo
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

int main(int argc, char* argv[]) {
	double t_inicio, t_fim;
	long int i, n, total;

	omp_set_num_threads(4);

	n = 700000000;

	if (n < 2) {
		printf("Valor invalido! Entre com um valor maior inteiro\n");
		return 0;
	}
	total = 0;

	t_inicio = omp_get_wtime();
#pragma omp parallel for reduction(+:total) schedule(dynamic ,10000)
	for (i = 3; i <= n; i += 2)
		if (primo(i) == true) total++;
	/* Acrescenta o dois, que também é primo */
	total += 1;
	t_fim = omp_get_wtime();
	printf("Quant. de primos entre 1 e %ld: %ld\n", n, total);
	printf("Tempo de execucao: %f com %d threads\n", t_fim - t_inicio,
		omp_get_max_threads());
}