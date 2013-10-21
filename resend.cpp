#include "resend.h"
#include <algorithm>
#include <cmath>
#include <iostream>

BayesianCalculator::BayesianCalculator(double totalArrivalRate)  : _arrivalRate{totalArrivalRate}, _nHat{totalArrivalRate}, _currentProbability{1/_nHat}
{

}

void BayesianCalculator::update(SendStatus status)
{
	if (status == SendStatus::COLLISION)
		_nHat = _nHat + _arrivalRate + 1 / (exp(1) - 2);
	else
		_nHat = std::max(_arrivalRate, _nHat + _arrivalRate - 1);

	_currentProbability = 1 / _nHat;
}

double BayesianCalculator::getProbability()
{
	return _currentProbability;
}

double BayesianCalculator::getEstimatedBacklog()
{
	return _nHat;
}