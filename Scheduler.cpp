#include "Variables.h"
#include "FileReader.h"
#include "PeriodicTask.h"
#include <math.h>
#include <signal.h>
#include <time.h>
#include <sys/neutrino.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <csignal>
#include <iostream.h>

using namespace std;

//Class variables
vector<Variables> vars;
vector<PeriodicTask*> readyQueue;
pthread_mutex_t queueMutex = PTHREAD_MUTEX_INITIALIZER;
sigset_t sigst;

struct timeval;
struct timespec timeV;
static unsigned int startTime;
unsigned int timeNow;
clock_t time_req;

double fuelConsumption = 0;
double engineSpeed = 0;
double engineCoolantTemperature = 0;
double currentGear = 0;
double vehicleSpeed = 0;

int fuelConsumptionPeriod;
int engineSpeedPeriod;
int engineCoolantPeriod;
int currentGearPeriod;
int vehicleSpeedPeriod;

//Storing the highest priority task (smallest period/deadline) in the ready queue
PeriodicTask* getHighPriority() {
	//Mutex lock to put and take from a queue
    pthread_mutex_lock(&queueMutex);

    //EDF to schedule a task with the smallest period/deadline
    int priorityIndex = 0;
    for (int i = 0; i < readyQueue.size(); i++) {
        if (readyQueue[priorityIndex]->getDeadline() > readyQueue[i]->getDeadline()) {
            priorityIndex = i;
        }
    }

    //Get the task with smallest deadline/period (high priori) and take it from the queue
    PeriodicTask* executingTask = readyQueue[priorityIndex];
    readyQueue.erase(readyQueue.begin() + priorityIndex);
	
	//mutex unlock releases resource of taskQueue
	pthread_mutex_unlock(&queueMutex);

    //return highest priority task
    return executingTask;
}


void *mutexForFuelConsumption(void* lockPeriod){
	while(true){
		//Getting how much time passed since the beginning of execution
		clock_gettime(CLOCK_MONOTONIC, &timeV);
		timeNow = timeV.tv_sec * 1000 + timeV.tv_nsec / 1000000;
		double executionTime = (double)(timeNow-startTime); 
		
		//Creates a task object with a task type (name of variable) and a period/deadline
		PeriodicTask* newTask = new PeriodicTask("fuelConsumptionRowData", executionTime);
		
		//Mutex lock on the queue to add the task
	    pthread_mutex_lock(&queueMutex);
		//Adds a the task to the ready queue
	    readyQueue.push_back(newTask);
		//Unlocks the mutex since were not using it anymore
	    pthread_mutex_unlock(&queueMutex);
		
		//Task wil go to sleep for the specified interval
	    delay ((int)lockPeriod);
	}
}

void *mutexForEngineSpeed(void* lockPeriod) {
	while(true){
		//Getting how much time passed since the beginning of execution
		clock_gettime(CLOCK_MONOTONIC, &timeV);
		timeNow = timeV.tv_sec * 1000 + timeV.tv_nsec / 1000000;
		double executionTime = (double)(timeNow-startTime);

		//Creates a task object with a task type (name of variable) and a period/deadline
		PeriodicTask* newTask = new PeriodicTask("engineSpeedRowData", executionTime);

		//Mutex lock on the queue to add the task
	    pthread_mutex_lock(&queueMutex);
	    //Adds a the task to the ready queue
	    readyQueue.push_back(newTask);
	    //Unlocks the mutex since were not using it anymore
	    pthread_mutex_unlock(&queueMutex);
		
		//Task wil go to sleep for the specified interval
	    delay ((int)lockPeriod);
	}
}

void *mutexForEngineCoolantTemperature(void* lockPeriod) {
	while (true){
		//Getting how much time passed since the beginning of execution
	    clock_gettime(CLOCK_MONOTONIC, &timeV);
		timeNow = timeV.tv_sec * 1000 + timeV.tv_nsec / 1000000;
		double executionTime = (double)(timeNow-startTime);

		//Creates a task object with a task type (name of variable) and a period/deadline
		PeriodicTask* newTask = new PeriodicTask("engineCoolantTemperatureRowData", executionTime);

		//Mutex lock on the queue to add the task
	    pthread_mutex_lock(&queueMutex);
	    //Adds a the task to the ready queue
	    readyQueue.push_back(newTask);
	    //Unlocks the mutex since were not using it anymore
	    pthread_mutex_unlock(&queueMutex);
		
		//Task wil go to sleep for the specified interval
	    delay ((int)lockPeriod);
	}
}

void *mutexForCurrentGear(void* lockPeriod) {
	while (true){
		//Getting how much time passed since the beginning of execution
	    clock_gettime(CLOCK_MONOTONIC, &timeV);
		timeNow = timeV.tv_sec * 1000 + timeV.tv_nsec / 1000000;
		double executionTime = (double)(timeNow-startTime);

		//Creates a task object with a task type (name of variable) and a period/deadline
		PeriodicTask* newTask = new PeriodicTask("currentGearRowData", executionTime);

		//Mutex lock on the queue to add the task
	    pthread_mutex_lock(&queueMutex);
	    //Adds a the task to the ready queue
	    readyQueue.push_back(newTask);
	    //Unlocks the mutex since were not using it anymore
	    pthread_mutex_unlock(&queueMutex);
		
		//Task wil go to sleep for the specified interval
	    delay ((int)lockPeriod);
	}
}

void *mutexForVehicleSpeed(void* lockPeriod) {
	while (true){
		//Getting how much time passed since the beginning of execution
	    clock_gettime(CLOCK_MONOTONIC, &timeV);
		timeNow = timeV.tv_sec * 1000 + timeV.tv_nsec / 1000000;
		double executionTime = (double)(timeNow-startTime);

		//Creates a task object with a task type (name of variable) and a period/deadline
		PeriodicTask* newTask = new PeriodicTask("vehicleSpeedRowData", executionTime);

		//Mutex lock on the queue to add the task
	    pthread_mutex_lock(&queueMutex);
	    //Adds a the task to the ready queue
	    readyQueue.push_back(newTask);
	    //Unlocks the mutex since were not using it anymore
	    pthread_mutex_unlock(&queueMutex);
		
		//Task wil go to sleep for the specified interval
	    delay ((int)lockPeriod);
	}
}

void *mutexForConsoleOutput(void* lockPeriod) {
	while (true){
		//Getting how much time passed since the beginning of execution
	    clock_gettime(CLOCK_MONOTONIC, &timeV);
		timeNow = timeV.tv_sec * 1000 + timeV.tv_nsec / 1000000;
		double executionTime = (double)(timeNow-startTime);

		//Creates a task object with a task type (name of variable) and a period/deadline
		PeriodicTask* newTask = new PeriodicTask("consoleOutput", executionTime);

		//Mutex lock on the queue to add the task
	    pthread_mutex_lock(&queueMutex);
	    //Adds a the task to the ready queue
	    readyQueue.push_back(newTask);
	    //Unlocks the mutex since were not using it anymore
	    pthread_mutex_unlock(&queueMutex);
		
		//Task wil go to sleep for the specified interval
	    delay ((int)lockPeriod);
	}
}

void fuelConsumptionRowData() {
	//How much time passed since the beginning of execution
	clock_gettime(CLOCK_MONOTONIC, &timeV);
	int timeNow = timeV.tv_sec * 1000 + timeV.tv_nsec / 1000000; 
	//Get the line where the data is stored
	int fileRow = (int)((double)(timeNow-startTime)/ 1000); //seconds
	//Get the value of the variable at the precise time
	if (fileRow > 0 && fileRow < vars.size()) {
        fuelConsumption = vars.at(fileRow).getFuelConsumption();
    }
}

void engineSpeedRowData() {
	//How much time passed since the beginning of execution
   clock_gettime(CLOCK_MONOTONIC, &timeV);
	int timeNow = timeV.tv_sec * 1000 + timeV.tv_nsec / 1000000;
	//Get the line where the data is stored
	int fileRow = (int)((double)(timeNow-startTime)/ 1000);
	//Get the value of the variable at the precise time
	if (fileRow > 0 && fileRow < vars.size()) {
        engineSpeed = vars.at(fileRow).getEngineSpeed();
    }
}

void engineCoolantTemperatureRowData() {
	//How much time passed since the beginning of execution
    clock_gettime(CLOCK_MONOTONIC, &timeV);
	int timeNow = timeV.tv_sec * 1000 + timeV.tv_nsec / 1000000;
	//Get the line where the data is stored
	int fileRow = (int)((double)(timeNow-startTime)/ 1000);
	//Get the value of the variable at the precise time
	if (fileRow > 0 && fileRow < vars.size()) {
        engineCoolantTemperature  = vars.at(fileRow).getEngineCoolantTemp();
    }
}

void currentGearRowData() {
	//How much time passed since the beginning of execution
    clock_gettime(CLOCK_MONOTONIC, &timeV);
	int timeNow = timeV.tv_sec * 1000 + timeV.tv_nsec / 1000000;
	//Get the line where the data is stored
	int fileRow = (int)((double)(timeNow-startTime)/ 1000);
	//Get the value of the variable at the precise time
	if (fileRow > 0 && fileRow < vars.size()) {
        currentGear = vars.at(fileRow).getCurrentGear();
    }
}

void vehicleSpeedRowData() {
	//How much time passed since the beginning of execution
   clock_gettime(CLOCK_MONOTONIC, &timeV);
	int timeNow = timeV.tv_sec * 1000 + timeV.tv_nsec / 1000000;
	//Get the line where the data is stored
	int fileRow = (int)((double)(timeNow-startTime)/ 1000);
	//Get the value of the variable at the precise time
	if (fileRow > 0 && fileRow < vars.size()) {
        vehicleSpeed = vars.at(fileRow).getVehicleSpeed();
    }
}

void consoleOutput() {
	//How much time passed since the beginning of execution
	clock_gettime(CLOCK_MONOTONIC, &timeV);
	timeNow = timeV.tv_sec * 1000 + timeV.tv_nsec / 1000000;
	double executionTime = (double)(timeNow-startTime)/ 1000 - 1; //in seconds
	
	//print to the console for the user 
    cout << 
    	"" << "[Current Time]" << "  " << "[Fuel Consumption]" << "  " << "[Engine Speed]" << "  " << "[Engine Coolant Temperature]" << "  " << "[Current Gear]" << "  " << "[Vehicle Speed]" << 
    	"\n   " << executionTime << " s" << "\t\t" << fuelConsumption << "\t\t  " << engineSpeed << "\t\t\t" << engineCoolantTemperature << "\t\t\t" << currentGear << "\t\t" << vehicleSpeed << 
		"\n***********************************************************************************************************************\n";
	
}

//EDF schedule that gets highest prioirty task and puts its on ready queue from the thread
void EDFSchedule() {
    while (true) {
        if (!readyQueue.empty()) {
			
			//get the highest priority task among the ready queue
            PeriodicTask* executingTask = getHighPriority();
			
			//perform the right read
            if (executingTask->getTask().compare("fuelConsumptionRowData") == 0) {
                fuelConsumptionRowData();
            }
            else if (executingTask->getTask().compare("engineSpeedRowData") == 0) {
                engineSpeedRowData();
            }
            else if (executingTask->getTask().compare("engineCoolantTemperatureRowData") == 0) {
                engineCoolantTemperatureRowData();
            }
            else if (executingTask->getTask().compare("currentGearRowData") == 0) {
                currentGearRowData();
            }
            else if (executingTask->getTask().compare("vehicleSpeedRowData") == 0) {
                vehicleSpeedRowData();
            }
            else if (executingTask->getTask().compare("consoleOutput") == 0) {
                consoleOutput();
            }
        }
    }
}

//Method that creates threads for all the varibles periods
void execute() {
	//Read and put dataset in a vector
	FileReader freader = FileReader();
	vars = freader.read_file();

	//User input for the periods of the variables
	cout << "------------------------------" << endl;
	cout << "Enter the periods for the variables of interest (in milliseconds)" << endl;
	cout << "-->Period for Fuel Consumption: ";
	cin >> fuelConsumptionPeriod;
	cout << "-->Period for Engine Speed: ";
	cin >> engineSpeedPeriod;
	cout << "-->Period for Engine Coolant Temperature: ";
	cin >> engineCoolantPeriod;
	cout << "-->Period for Current Gear: ";
	cin >> currentGearPeriod;
	cout << "-->Period for Vehicle Speed: ";
	cin >> vehicleSpeedPeriod;
	cout << "------------------------------" << endl;

	//Creates the threads and timers for the task in queue with the period frequency
   	pthread_create(NULL,NULL, mutexForFuelConsumption,(void *)fuelConsumptionPeriod);
    pthread_create(NULL,NULL, mutexForEngineSpeed,(void *)engineSpeedPeriod);
    pthread_create(NULL,NULL, mutexForEngineCoolantTemperature,(void *)engineCoolantPeriod); 
    pthread_create(NULL,NULL, mutexForCurrentGear,(void *)currentGearPeriod); 
    pthread_create(NULL,NULL, mutexForVehicleSpeed,(void *)vehicleSpeedPeriod); 
    
    //we manually set the period/deadline for the console output to every 100 ms
    pthread_create(NULL,NULL, mutexForConsoleOutput,(void *)100);
    
	//Starting the clock time
    clock_gettime(CLOCK_MONOTONIC, &timeV);
    //Time in ms
    startTime = timeV.tv_sec * 1000 + timeV.tv_nsec / 1000000;
	//Start scheduler for EDF
	EDFSchedule();
}

