#pragma once

#include <iostream>
#include <list>
#include <iterator>
#include <string>

#ifndef PERIODICTASK_H
#define PERIODICTASK_H

using namespace std;

class PeriodicTask{
	private:
		string newTask;
		double deadline;
	
	public:
		PeriodicTask();
		PeriodicTask(string periodicTask, double newDeadline);

		string getTask();
		double getDeadline();
};

#endif