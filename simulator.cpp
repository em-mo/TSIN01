#include "simulator.h"
#include <math.h>

#include <iostream>

Simulator::Simulator(int nodes, double arrivalRatePerSlot, double resendChance)
: _arrivalRatePerSlot{arrivalRatePerSlot}, _resendProbability{resendChance}, _bayesianCalculator{arrivalRatePerSlot}, _bayesian{false}, _step{0},
  _departures{0}, _totalDelay{0}
{
	_arrivalProbability = 1 - exp(-_arrivalRatePerSlot / nodes);
	Node::initRandom();
	for (int i = 0; i < nodes; ++i)
	{
		if (resendChance == -1)
			_nodes.push_back(new BayesianNode(_arrivalProbability));
		else
			_nodes.push_back(new NormalNode(_arrivalProbability));
	}
	
	if (resendChance < 0)
		_bayesian = true;
}

Simulator::~Simulator()
{
	while(_nodes.size() > 0)
	{
		delete _nodes.back();
		_nodes.pop_back();
	}
}

StepData Simulator::step()
{
	SendStatus outcome = SendStatus::IDLE;
	int backlog = 0;
	int newArrival = 0;
	_sendingNodes.clear();

	if (_bayesian)
	{
		_resendProbability = _bayesianCalculator.getProbability();
	}

	for (auto node : _nodes)
	{
		if (node->hasPacket())
			++backlog;

		if (node->step(_resendProbability, _step))
		{
			_sendingNodes.push_back(node);
		}

		if (node->hasNewArrival())
			++newArrival;
	}

	if (_sendingNodes.size() == 1)
	{
		outcome = SendStatus::SUCCESS;
		int value = _sendingNodes.front()->successfulSend(_step);
		_totalDelay += value;
		++_departures;
	}
	else if (_sendingNodes.size() > 1)
	{
		outcome = SendStatus::COLLISION;
	}

	_bayesianCalculator.update(outcome);

	double averageDelay = -1;
	if (_departures != 0)
		averageDelay = _totalDelay / static_cast<double>(_departures);

	++_step;

	return StepData{outcome, backlog, _bayesianCalculator.getEstimatedBacklog(), newArrival, (outcome == SendStatus::SUCCESS ? 1 : 0), averageDelay};
}