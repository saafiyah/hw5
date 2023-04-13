#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool helper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t worker, size_t shift, vector<size_t>& shifts);

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

    // for(int i = 0; i < avail.size(); i++)
    // {
    //     vector<Worker_T> row;
    //     sched.push_back(row); 
    // }
    sched.resize(avail.size(), vector<Worker_T>(dailyNeed, INVALID_ID));
    vector<size_t> shifts(avail[0].size(), 0);

    if(helper(avail, dailyNeed, maxShifts, sched, 0, 0, shifts))
    {
        return true;
    }
    return false; 
}

bool helper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t worker, size_t shift, vector<size_t>& shifts)
{
    if(avail.size() == worker)
    {
        return true; 
    }
    for(unsigned int i = 0; i < avail[0].size(); i++)
    {
        if(shifts[i] < maxShifts && avail[worker][i] == 1)
        {
            shifts[i] = shifts[i] + 1; 
            sched[worker][shift] = i; 
            if(helper(avail, dailyNeed, maxShifts, sched, (shift + 1)/dailyNeed + worker, (shift + 1) % dailyNeed, shifts))
            {
                return true;
            }
            shifts[i] = shifts[i] - 1; 
            sched[worker][shift] = INVALID_ID; 
        }
    }
    return false; 
}