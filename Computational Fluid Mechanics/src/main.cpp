#include <iostream>
#include <array>
#include <fstream>
#include <math.h>

#define ITERATION_COUNT 400



void rungeKutta4(double w[], double t[], double (*function)(double, double), double h, int itterations);
double testFunction(double time, double val);

int main() {

	double y[ITERATION_COUNT];
	double t[ITERATION_COUNT];

	t[0] = 0;
	y[0] = .5;

	rungeKutta4(y, t, testFunction, .01, ITERATION_COUNT);


	std::ofstream fileManager("dataForPlot.dat");
	if (!fileManager.fail()) {
		for (int i = 0; i < ITERATION_COUNT; i++)
			fileManager << t[i] << " " << y[i] << std::endl;
	}
	else
		std::cout << "Warning File Failed to Create" << std::endl;


}

//To Do: Add Functionality for systems of differential equations
void rungeKutta4(double w[], double t[], double (*function)(double, double), double h, int itterations){
	double k1, k2, k3, k4;

	for (int i = 0; i < itterations-1; i++) {
		k1 = h * function(t[i], w[i]);
		k2 = h * function(t[i] + h / 2, w[i] + k1 / 2);
		k3 = h * function(t[i] + h / 2, w[i] + k2 / 2);
		k4 = h * function(t[i] + h, w[i] + k3);
		w[i+1] = w[i] + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
		t[i+1] = t[i] + h;
	}

}
double testFunction(double time, double val) {
	return  sin(val) * time;
}

