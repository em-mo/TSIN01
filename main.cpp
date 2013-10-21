#include "simulator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>

int main(int argc, char** argv)
{
	const int nodes = 100;
	double arrivalRate = 1 / exp(1);
	double resendChance = 0.01;
	if (argc == 3)
	{
		arrivalRate = std::stof(argv[1]);
		resendChance = std::stof(argv[2]);
	}
	else if (argc != 1)
	{
		std::cout << "Wrong number of arguments!" << std::endl;
		return -1;
	}

	Simulator simulator{nodes, arrivalRate, resendChance};
	StepData stepData;
	std::ofstream outputFile;
	outputFile.open("output.txt", std::ios::trunc);
	int totalArrivals = 0;
	int totalDepartures = 0;

	outputFile << "Slot " << "Backlog " << "EstimatedBacklog " << "Arrivals " << "Departures " << "AverageDelay " << "Outcome" << std::endl;

	for (int i = 0; i < 10000; ++i)
	{
		stepData = simulator.step();

		totalArrivals += stepData.arrivals;
		totalDepartures += stepData.departures;

		outputFile.setf(std::ios::showpoint);
		outputFile << std::setw(3) << i << " " << std::setw(3) << stepData.backlog << " " << std::setw(4) << std::setprecision(3) << stepData.estimatedBacklog << " " << std::setw(4) << totalArrivals << " " << std::setw(4) << totalDepartures << " " << std::setw(4) << stepData.averageDelay << " ";
		std::string outcomeString;
		if (stepData.outcome == SendStatus::IDLE)
		{
			outcomeString = "IDLE";
		}
		else if (stepData.outcome == SendStatus::COLLISION)
		{
			outcomeString = "COLLISION";
		}
		else
		{
			outcomeString = "SUCCESS";
		}

		outputFile << outcomeString << std::endl;
	}
	outputFile.close();
}