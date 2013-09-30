#ifndef NODE_H
#define NODE_H

#include <random>

class Node
{
public:
	Node(double qa);
	virtual bool step(double qr) = 0;
	static void initRandom();
	void successfulSend();
	bool hasPacket();
	bool hasNewArrival();

protected:
	double _qa;
	bool _hasPacket;
	bool _hasNewArrival;
	static std::uniform_real_distribution<double> _uniformRandom;
	static std::default_random_engine _engine;

private:

};

class NormalNode : public Node
{
public:
	NormalNode(double qa) : Node{qa} {}
	virtual bool step(double qr);
private:
};

class BayesianNode : public Node
{
public:
	BayesianNode(double qa) : Node{qa} {}
	virtual bool step(double qr);
private:
};

#endif