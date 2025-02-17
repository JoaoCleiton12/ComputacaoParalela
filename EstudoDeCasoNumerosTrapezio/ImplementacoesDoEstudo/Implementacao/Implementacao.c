#include <stdio.h>
#include <math.h>
#include <omp.h>

double f(double x) { /* Calcula f(x) */
	double valor;
	valor = exp(x);
	return (valor);
}
int main(int argc, char* argv[]) {
	double integral; /* Armazena resultado em integral */

	double a = 0.0, b = 1.0; /* Limite esquerdo e direito */

	long long n = 128000000000; /* Número de Trapezóides */

	double h; /* Largura da base do Trapezio ide */

	h = (b - a) / n;

	integral = (f(a) + f(b)) / 2.0;

	double t_inicio = omp_get_wtime();

	omp_set_num_threads(1);

	/* Faz a redução e escalona as iterações para as threads */
#pragma omp parallel for reduction (+: integral) schedule(static)
		for (long long i = 1; i < n - 1; i++) {
			integral += f(a + i * h);
		}
	integral *= h;

	double t_fim = omp_get_wtime();

	printf(" Com n = %ld trapezoides , a estimativa \n", n);
	printf("da integral de %f ate %f = %lf \n", a, b, integral);
	printf(" Tempo : \t %f com %d threads .\n", t_fim - t_inicio,omp_get_max_threads());
	return (0);
}