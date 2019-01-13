#include <iostream>
#include <cmath>
#include <ctime>
#include <iomanip>

#define _USE_MATH_DEFINES

double func(double x) {
	return (pow(x+5,4));
}

double mutation(double x0, double x1) {
	const int NUM = 10000000;
	return fabs((double)((rand() * NUM) % (int)((x1 - x0) * NUM) + 1) / NUM) + x0;
}

double inversion(double x, double eps) {
	static int sign = 0;
	sign++;
	sign %= 2;

	if (sign == 0)
		return x - eps;
	else
		return x + eps;
}

void crossover(double* x, double eps, double x0, double x1) {
	int k = 99;
	for (int i(0); i < 8; i++)
		for (int j(i + 1); j < 8; j++) {
			x[k] = (x[i] + x[j] / 2);
			k--;
		}

	for (int i(0); i < 8; i++) {
		x[k] = inversion(x[i], eps);
		k--;
		x[k] = inversion(x[i], eps);
		k--;
	}

	for (int i(8); i < k; i++)
		x[i] = mutation(x0, x1);
}

void sort(double* x, double* y) {
	for(int i(0); i < 100; i++)
		for (int j(i + 1); j < 100; j++) {
			if (fabs(y[j]) < fabs(y[i])) {
				std::swap(y[i], y[j]);
				std::swap(x[i], x[j]);
			}
		}
}

double genetic(double x0, double x1, double eps) {

	double population[100];
	double f[100];
	int iter = 0;

	
	for (int i(0); i < 100; i++) {
		population[i] = mutation(x0, x1);
		f[i] = func(population[i]);
	}

	auto _cout = [](double* x, double* y) {
		std::cout << "Population = " << x[0] << "\t\t Function = " << y[0]<< std::endl;
	};

	_cout(population, f);

	
	sort(population, f);

	_cout(population, f);

	do {
		iter++;
		crossover(population, eps, x0, x1);

		for (int i(0); i < 100; i++)
			f[i] = func(population[i]);

		sort(population, f);

		_cout(population, f);

	} while (fabs(f[0]) > eps && iter < 100000);

	std::cout << "Iterations: " << iter << std::endl;
	return population[0];
}

int main() {

	std::cout << std::setprecision(4) << std::fixed;

	srand(time(NULL));

	std::cout << "f(x) = x^2+5" << std::endl;

	double x0, x1, eps;

	std::cout << "x0, x1, eps: ";
	std::cin >> x0 >> x1 >> eps;

	std::cout << genetic(x0, x1, eps) << std::endl;

	std::cin.ignore();
	std::cin.get();
	return 0;
}
