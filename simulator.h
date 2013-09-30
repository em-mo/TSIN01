#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include "node.h"
#include "send_status.h"
#include "resend.h"

class Simulator
{
public:
    Simulator(int nodes, double arrivalRate, double resendChance);
    void step();

private:
	std::vector<Node*> _nodes;
	std::vector<Node*> _sendingNodes;

	int _numberOfBacklogged;
	double _arrivalRatePerSlot;
	double _arrivalProbability;
	double _resendProbability;
	bool _bayesian;
	BayesianCalculator _bayesianCalculator;
};

#endif