#ifndef RESEND_H
#define RESEND_H

#include "send_status.h"

class BayesianCalculator
{
public:
	BayesianCalculator(double totalArrivalRate);
	void update(SendStatus status);
	double getProbability();
	double getEstimatedBacklog();
private:
	double _arrivalRate;
	double _nHat;
	double _currentProbability;
};

#endif