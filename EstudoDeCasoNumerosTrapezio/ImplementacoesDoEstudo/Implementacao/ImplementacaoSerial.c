#include <stdio.h>
#include <math.h>
#include <omp.h>

double f(double x) { 
	return exp(x);
}
int main(int argc, char* argv[]) {

	//limites
	double a = 0.0, b = 1.0; 

	long long n = 63000000000;

	double h = (b - a) / n;

	double integral = (f(a) + f(b)) / 2.0;

	double t_inicio = omp_get_wtime();

	for (long long i = 1; i < n - 1; i++) {
		integral += f(a + i * h);
	}
	integral *= h;

	double t_fim = omp_get_wtime();

	printf(" Com n = %llu trapezoides , a estimativa \n", n);
	printf("da integral de %f ate %f = %lf \n", a, b, integral);
	printf(" Tempo : \t %f com %d threads .\n", t_fim - t_inicio, omp_get_max_threads());
	return (0);
}