#pragma once


namespace cfd
{


	void rungeKutta4N(void function(double t, double y[], double yp[]), int numEq, double y[], double t, double h, double k1[], double k2[], double k3[], double k4[], double k5[], double solution[]);


}
