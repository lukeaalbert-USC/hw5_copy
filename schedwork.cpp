#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include <limits.h>
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper (
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, map<Worker_T, size_t> workerToDaysWorked,
    size_t currDay,
    size_t currWorker,
    size_t workersScheduled,
    size_t workerLoopHelp);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    if (avail[0].size() < dailyNeed) //if the number of k possible workers is less than the d daily needed, no way to create a valid schedule
    {
        return false;
    }

    map<Worker_T, size_t> workerToDaysWorked; //mapping worker to the number of the days theyve worked
    for (unsigned long int i = 0; i < avail[0].size(); i++) //for all k workers, add the workers' id and set their days worked to 0. 
    {
        workerToDaysWorked[i] = 0; //"worker id" days worked = 0
    }

    for (unsigned long int i = 0; i < avail.size(); i++) //initialize sched
    {
        std::vector<Worker_T> day;
        sched.push_back(day);
        for (size_t j = 0; j < dailyNeed; j++)
        {
            sched[i].push_back(INT_MAX); //all vals will be INT_MAX
        }
    }
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, workerToDaysWorked, 0, 0, 0, 0);
}

bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, map<Worker_T, size_t> workerToDaysWorked, size_t row, size_t col, size_t workersScheduled, size_t workerLoopHelp) {
    if (row == avail.size() && col == 0) //if we're on the last day and the last worker
    {
        return true;
    }
    for (int worker = workerLoopHelp; worker < avail[0].size(); worker++) //for all workers
    {
        sched[row][col] = worker;
        workerToDaysWorked[worker]++;
        workersScheduled++;
        if (avail[row][worker] == true && workerToDaysWorked[worker] <= maxShifts) //if the worker can work (is valid)
        {
            if (workersScheduled == dailyNeed)
            { 
                if (scheduleHelper(avail, dailyNeed, maxShifts, sched, workerToDaysWorked, row + 1, 0, 0, 0))
                {
                    return true;
                }
            }
            else
            {
                if (scheduleHelper(avail, dailyNeed, maxShifts, sched, workerToDaysWorked, row, col + 1, workersScheduled, worker + 1))
                {
                    return true;
                }
            }
        }
        workerToDaysWorked[worker]--;
        workersScheduled--;
    }
    return false;
}