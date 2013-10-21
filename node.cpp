#include "node.h"

std::uniform_real_distribution<double> Node::_uniformRandom{0, 1};
std::default_random_engine Node::_engine{};

Node::Node(double qa) : _qa{qa}, _hasPacket{false}, _packetArrivalSlot{0}, _hasNewArrival{false}
{
}

void Node::initRandom()
{
	std::random_device rd;
	_engine.seed(rd());
}

int Node::successfulSend(int departureSlot)
{
	int delay = departureSlot - _packetArrivalSlot;
	_hasPacket = false;
	_packetArrivalSlot = 0;

	return delay;

}

bool Node::hasPacket()
{
	return _hasPacket;
}

bool Node::hasNewArrival()
{
	return _hasNewArrival;
}

bool NormalNode::step(double qr, int slotNumber)
{
	double randomValue = _uniformRandom(_engine);
	_hasNewArrival = false;
	if (_hasPacket)
		return randomValue < qr;
	else 
	{
		if (randomValue < _qa)
		{
			_packetArrivalSlot = slotNumber;
			_hasNewArrival = true;
			_hasPacket = true;
			return true;
		}
	}
	return false;
}

bool BayesianNode::step(double qr, int slotNumber)
{
	// No packet and new arrival
	_hasNewArrival = _uniformRandom(_engine) < _qa && !_hasPacket;

	if (_hasNewArrival)
	{
		_packetArrivalSlot = slotNumber;
		_hasPacket = true;
		return false;
	}

	_hasPacket = _hasPacket || _hasNewArrival;

	return _hasPacket && _uniformRandom(_engine) < qr;
}