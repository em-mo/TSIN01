#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include "node.h"
#include "send_status.h"
#include "resend.h"

struct StepData
{
	SendStatus outcome;
	int backlog;
	double estimatedBacklog;
	int arrivals;
	int departures;
	double averageDelay;
};

class Simulator
{
public:
    Simulator(int nodes, double arrivalRate, double resendChance);
    ~Simulator();
    StepData step();

private:
	std::vector<Node*> _nodes;
	std::vector<Node*> _sendingNodes;

	int _numberOfBacklogged;
	double _arrivalRatePerSlot;
	double _arrivalProbability;
	double _resendProbability;
	bool _bayesian;
	BayesianCalculator _bayesianCalculator;
	int _step;
	int _departures;
	int _totalDelay;
};

#endif