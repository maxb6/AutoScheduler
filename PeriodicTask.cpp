#include "PeriodicTask.h"

using namespace std;

//Class that creates a task with a type of task and a period/deadline
PeriodicTask::PeriodicTask(){
	PeriodicTask::newTask = "null";
	PeriodicTask::deadline = -1;
}

PeriodicTask::PeriodicTask(string periodicTask, double newDeadline){
	newTask = periodicTask;
	deadline = newDeadline;
}

string PeriodicTask::getTask(){
	return newTask;
}

double PeriodicTask::getDeadline(){
	return deadline;
}