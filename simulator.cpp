#include "simulator.h"
#include <math.h>

Simulator::Simulator(int nodes, double arrivalRatePerSlot, double resendChance)
: _arrivalRatePerSlot{arrivalRatePerSlot}, _resendProbability{resendChance}, _bayesianCalculator{arrivalRatePerSlot}, _bayesian{false}
{
	_arrivalProbability = 1 - exp(-_arrivalRatePerSlot / nodes);
	Node::initRandom();
	for (int i = 0; i < nodes; ++i)
	{
		if (resendChance == -1)
			_nodes.push_back(new BayesianNode(arrivalRatePerSlot));
		else
			_nodes.push_back(new NormalNode(arrivalRatePerSlot));
	}
	
	if (resendChance < 0)
		_bayesian = true;
}

void Simulator::step()
{
	SendStatus outcome = SendStatus::IDLE;
	int backlog = 0;
	if (_bayesian)
	{
		_resendProbability = _bayesianCalculator.getProbability();
	}

	for (auto node : _nodes)
	{
		if (node->hasPacket())
			++backlog;

		if (node->step(_resendProbability))
		{
			_sendingNodes.push_back(node);
		}
	}

	if (_sendingNodes.size() == 1)
	{
		outcome = SendStatus::SUCCESS;
		_sendingNodes.front()->successfulSend();
	}

}