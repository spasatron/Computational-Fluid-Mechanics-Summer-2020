#define _USE_MATH_DEFINES
#define ITERATION_COUNT 2010



#include <iostream>
#include <array>
#include <fstream>
#include <math.h>
#include "rungeKutta.h"




double testFunction(double time, double val);
void testFunc(double t, double y[], double yp[]);
void problem1_1(double time, double y[], double yp[]);
double cd(double velocity);

int main() {


	double t = 0;
	double y[2];
	double k1[2], k2[2], k3[2], k4[2], k5[2], sol[2];
	memset(y, 0, sizeof(k1));
	memset(k1, 0, sizeof(k1));
	memset(k2, 0, sizeof(k1));
	memset(k3, 0, sizeof(k1));
	memset(k4, 0, sizeof(k1));
	memset(k5, 0, sizeof(k1));

	//rungeKutta4(y, t, testFunction, .01, ITERATION_COUNT);


	std::ofstream fileManager("dataForPlot.dat");
	if (!fileManager.fail()) {
		for (int i = 0; i < ITERATION_COUNT; i++) {
			fileManager << t << " " << y[1] << std::endl;
			cfd::rungeKutta4N(problem1_1, 2, y, t, .01, k1, k2, k3, k4, k5, sol);
			t += .01;
			y[0] = sol[0];
			y[1] = sol[1];
		}
	}
	else
		std::cout << "Warning File Failed to Create" << std::endl;


}


double testFunction(double time, double val) {
	return  sin(val) * time;
}

void testFunc(double t, double y[], double yp[]) {
	//std::cout << y[1] << std::endl;
	yp[0] = y[1];
	yp[1] = 9.8;
}



/*Function needed for problem 1.1
	diameter for ping pong ball is .036m
	density of water 1000 kg/m^3
	kv is 1*10^-6 m^2/s
	density of ball is 1.22 kg/m^3

	Forces:

	Boyant Force: pi*d^3*pf*g/6; (pf = fluid density)
		

*/
void problem1_1(double t, double y[], double yp[]) {
	//The derivative of position (y[0]) is velocity y[1]
	yp[0] = y[1];

	const double A = 1 + .5 * 1000 / 1.22;
	const double B = (1 - 1000 / 1.22) * 9.8; 
	const double C = 3 * 1000 / (4 * 1.22 * .036);




	//Boyant + force on accelerating body + viscosity forces
	double f = (-B - C * y[1] * abs(y[1]) * cd(abs(y[1])))/A;
	yp[1] = f;
}


double cd(double velocity) {
	double re = velocity * .036 / pow(10, -6);
	if (re == 0)
		return 0;
	if (re <= 1)
		return 24 / re;
	if (1 < re && re <= 400)
		return 24 / pow(re, .646);
	if (400 < re && re <= 3 * pow(10, 5))
		return .5;
	if (3 * pow(10, 5) < re && re <= 2 * pow(10, 6))
		return .000366 * pow(re, .4275);
	return .18;
}