#include <iostream>
#include <array>
#include <fstream>
#include <math.h>

#define ITERATION_COUNT 101



void rungeKutta4(double w[], double t[], double (*function)(double, double), double h, int itterations);
double testFunction(double time, double val);
void testFunc(double t, double y[], double yp[]);
void rungeKutta4N(void function(double t, double y[], double yp[]), int numEq, double y[], double t, double h, double k1[], double k2[], double k3[], double k4[], double k5[], double solution[]);
int main() {


	double t = 0;
	double y[2] = { 0, 0 };
	double k1[2], k2[2], k3[2], k4[2], k5[2], sol[2];

	//rungeKutta4(y, t, testFunction, .01, ITERATION_COUNT);


	std::ofstream fileManager("dataForPlot.dat");
	if (!fileManager.fail()) {
		for (int i = 0; i < ITERATION_COUNT; i++) {
			fileManager << t << " " << y[0] << std::endl;
			rungeKutta4N(testFunc, 2, y, t, .01, k1, k2, k3, k4, k5, sol);
			t += .01;
			y[0] = sol[0];
			y[1] = sol[1];
		}
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

void testFunc(double t, double y[], double yp[]) {
	//std::cout << y[1] << std::endl;
	yp[0] = y[1];
	yp[1] = 9.8;
}


/*
	Purpose: rungeKutta4N computes on step of with runge kutta 4th order method in float arithmetic
	
	@param function(float, float[], float[]) Function takes the inputs and rewrites over yp[] in order to store the derivative information.
	@param numEq number of equations in the system
	@param y[] starting values for y
	@param t starting time/var
	@param h step size
	@param k1[] - k4[] the coeffiecients used to compute the approximation. Primed at the derivative values yp[] on input.
	@param solution[] OUTPUT ses the output to be the solution after one step
*/

void rungeKutta4N(void function(double t, double y[], double yp[]), int numEq, double y[], double t, double h, double k1[], double k2[], double k3[], double k4[], double k5[], double solution[])
{
	//Computed the first coefficient k1
	function(t, y, k1);
	for (int i = 0; i < numEq; i++) {
		k5[i] = y[i] + h * k1[i] / 2;
	}
	//Compute k2
	function(t + h/2, k5, k2);

	for (int i = 0; i < numEq; i++) {
		k5[i] = y[i] + h * k2[i]/2;
	}
	//Compute k3
	function(t + h/2, k5, k3);

	for (int i = 0; i < numEq; i++) {
		k5[i] = y[i] + h * k3[i];
	}
	//compute k4
	function(t + h, k5, k4);

	//Ready to compute solution
	for (int i = 0; i < numEq; i++) {
		solution[i] = y[i] + h * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]) / 6;
	}
}

