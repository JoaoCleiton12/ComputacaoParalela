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
	if (argc < 2) {
		printf("Valor invalido! Entre com o valor do, maior inteiro\n");
			return 0;
	}
	else {
		n = strtol(argv[1], (char**)NULL, 10);
	}
	total = 0;
	t_inicio = omp_get_wtime();
	/* Solução trivial */
#pragma omp parallel for reduction(+:total) schedule(static)
/* Solução melhorada: schedule(dynamic ,10000) */
	for (i = 3; i <= n; i += 2)
		if (primo(i) == 1) total++;
	/* Acrescenta o dois, que também é primo */
	total += 1;
	t_fim = omp_get_wtime();
	printf("Quant. de primos entre 1 e %ld: %ld\n", n, total);
	printf("Tempo de execucao: %f com %d threads\n", t_fim - t_inicio,
		omp_get_max_threads());
}