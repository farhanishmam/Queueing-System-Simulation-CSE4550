#ifndef MSQS_2_SERVERS_SCENARIO_2_SERVER_H
#define MSQS_2_SERVERS_SCENARIO_2_SERVER_H


#include "event.h"
#include "queue.h"
//#include "scheduler.h"

#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

class Server
{
public:

    Server ();
    void initialize ();
    void arrivalHandler ();
    void departureHandler ();
    void createTraceFile ();

    void updateStat();
    void report();

    inline int& status1 (){
        return (status1_);
    }
    inline int& status2 (){
        return (status2_);
    }
    inline int& itemArrived (){
        return (itemArrived_);
    }
    inline double& arrivalMean (){
        return (arrivalMean_);
    }
    inline double& departureMean (){
        return (departureMean_);
    }

    //Time Average Functions
    inline double& areaQueue(){
        return (areaQueue_);
    }
    inline double& areaSystem(){
        return (areaSystem_);
    }
    inline double& areaServer(){
        return (areaServer_);
    }
    //Job Average Functions
    inline double& totalQueueDelay(){
        return (totalQueueDelay_);
    }
    inline double& totalSystemDelay(){
        return (totalSystemDelay_);
    }

private:
    Queue* queue_;
    ArrivalEvent a_;
    DepartureEvent d_;

    int status1_; //server 1 status, 1 means busy, 0 means idle
    int status2_; //server 2 status
    int itemArrived_; // count of already arrived events
    Item* itemInService_; // holds reference to the current item (event) in service
    ofstream trace_; // used for writing to the trace file

    double arrivalMean_; // mean time for arrival events
    double departureMean_; // mean time for departure events
    double exponential (double mean);

    //Variables for Time Average
    double timeLastEvent;
    double areaQueue_;
    double areaServer_;
    double areaSystem_;


    //Variables for Job Average
    double queueDelay_;
    double systemDelay_;
    double totalQueueDelay_;
    double totalSystemDelay_;
    int totalCustomerServed;
};

#endif //MSQS_2_SERVERS_SCENARIO_2_SERVER_H
