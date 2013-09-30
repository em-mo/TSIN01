#include "node.h"

std::uniform_real_distribution<double> Node::_uniformRandom{0, 1};
std::default_random_engine Node::_engine{};

Node::Node(double qa) : _qa{qa}, _hasPacket{false}, _hasNewArrival{false}
{
}

void Node::initRandom()
{
	std::random_device rd;
	_engine.seed(rd());
}

void Node::successfulSend()
{
	_hasPacket = false;
}

bool Node::hasPacket()
{
	return _hasPacket;
}

bool Node::hasNewArrival()
{
	return _hasNewArrival;
}

bool NormalNode::step(double qr)
{
	_hasNewArrival = false;
	if (_hasPacket)
		return _uniformRandom(_engine) < qr;
	else 
	{
		if (_uniformRandom(_engine) < _qa)
		{
			_hasNewArrival = true;
			_hasPacket = true;
			return true;
		}
	}
	return false;
}

bool BayesianNode::step(double qr)
{
	// No packet and new arrival
	_hasNewArrival = _uniformRandom(_engine) < _qa && !_hasPacket;

	_hasPacket = _hasPacket || _hasNewArrival;

	return _hasPacket && _uniformRandom(_engine) < qr;
}