#include "resend.h"
#include <algorithm>
#include <cmath>
BayesianCalculator::BayesianCalculator(double totalArrivalRate)  : _arrivalRate{totalArrivalRate}, _nHat{totalArrivalRate}, _currentProbability{1/_nHat}
{

}

void BayesianCalculator::update(SendStatus status)
{
	if (status == SendStatus::COLLISION)
		_nHat = std::max(_arrivalRate, _nHat + _arrivalRate - 1);
	else
		_nHat = _nHat + _arrivalRate + 1 / (exp(1) - 2);

	_currentProbability = 1 / _nHat;
}

double BayesianCalculator::getProbability()
{
	return _currentProbability;
}