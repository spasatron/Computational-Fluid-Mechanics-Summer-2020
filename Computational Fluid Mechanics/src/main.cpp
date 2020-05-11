#include <iostream>



double rungeKutta45(double startVal, double startTime, double (*function)(double, double), double h, int itterations);
double testFunction(double time, double val);

int main() {
	std::cout << "Hello World" << std::endl;
	std::cout << "Basic Test Function: " << rungeKutta45(.5, 0, testFunction, .5, 4) << std::endl;

}


double rungeKutta45(double startVal, double startTime, double (*function)(double, double), double h, int itterations){
	double w = startVal;
	double k1, k2, k3, k4;
	double t = startTime;



	for (int i = 0; i < itterations; i++) {
		k1 = h * function(t, w);
		k2 = h * function(t + h / 2, w + k1 / 2);
		k3 = h * function(t + h / 2, w + k2 / 2);
		k4 = h * function(t + h, w + k3);
		w = w + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
		t += h;
	}


	return w;
}
double testFunction(double time, double val) {
	return val - time * time + 1;
}


