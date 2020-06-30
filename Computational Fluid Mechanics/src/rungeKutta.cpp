
#include "rungeKutta.h"


namespace cfd 
{

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
		function(t + h / 2, k5, k2);

		for (int i = 0; i < numEq; i++) {
			k5[i] = y[i] + h * k2[i] / 2;
		}
		//Compute k3
		function(t + h / 2, k5, k3);

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


}