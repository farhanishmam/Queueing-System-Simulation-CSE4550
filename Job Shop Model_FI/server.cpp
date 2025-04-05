#include "server.h"
#include "scheduler.h"

#include <malloc.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

Server :: Server (int serverId, int stationCount) : a_(this), d_(this)
{
    queue_ = new Queue();
    serverId_ = serverId;
    stationCount_ = stationCount;
}

double
Server :: exponential(double mean) {

    double r = (double)rand()/(RAND_MAX + 1.0);
    double ex = -log (r)/mean;
    return ex;
}

void
Server :: initialize () {
    status_ = 0;
    itemArrived_ = 0;
    timeLastEvent = 0.0;

    areaQueue_ = 0.0;
    areaServer_ = 0.0;
    areaSystem_ = 0.0;

    totalQueueDelay_ = 0.0;
    totalSystemDelay_ = 0.0;
    totalCustomerServed = 0;
}

void Server:: initializeArrival(int jobId){
    currentJobId = jobId;
    double t = exponential (arrivalMean_);
    //trace_ << "interarrival time " << t << endl;
    a_.activate (t);
}

void Server:: initializeDeparture(){
    double t = exponential (departureMean_);
    //trace_ << "\tservice time = " << t << endl;
    d_.activate (t);
    if((!nextServer.empty()) && (nextServer[currentJobId-1] != nullptr)){
        nextServer[currentJobId-1] ->initializeArrival(currentJobId);
    }
    if ((itemArrived_ < 1000) && (serverId_ == 1)) {
        cout<<itemArrived_<<endl;
        initializeArrival(2);
    }
}

void
Server :: createTraceFile () {
    string traceName = "trace_" + to_string(serverId_) + ".out";
    trace_.open (traceName, ios::out);
    if (!trace_) {
        cout << "cannot open the trace file.\n";
    }
    trace_<< "trace file for the simulation" << endl;
    trace_ << "format of the file" << endl;
    trace_ << "<event> <time> <item id> <server status> <queue size>" << endl << endl;
}

void
Server :: arrivalHandler () {
    Item* temp;
    itemArrived_++;
    temp = (Item*) malloc (sizeof(Item));
    temp->id_ = itemArrived_;
    temp->itemArrivalTime = Scheduler::now();

    trace_ << "a\t" << Scheduler::now () << "\t" << temp->id_ << "\t" << status_ << "\t" << queue_->length() << endl;

    if (status () < stationCount_) {
        // write to the trace file

        status() += 1;
        trace_ << "s\t" << Scheduler::now () << "\t" << temp->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
        itemInService_ = temp;
        queueDelay_ = Scheduler::now() - itemInService_->itemArrivalTime;
        totalQueueDelay_ += queueDelay_;

        initializeDeparture();
    }
    else {
        queue_->enque(temp);
    }
}

void
Server :: departureHandler () {
    status() -= 1;
    // write to the trace file
    if (queue_->length() > 0) {
        trace_ << "d\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
    } else {
        trace_ << "d\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << 0 << "\t" << queue_->length() << endl;
    }
    //Update output statistics
    totalCustomerServed++;
    systemDelay_ = Scheduler::now() - itemInService_->itemArrivalTime;
    totalSystemDelay_ += systemDelay_;

    if (queue_->length() > 0) {
        itemInService_ = queue_->deque ();
        //Update output statistics
        queueDelay_ = Scheduler::now() - itemInService_->itemArrivalTime;
        totalQueueDelay_ += queueDelay_;
        // write to the trace file
        trace_ << "s\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << queue_->length() << endl;

        initializeDeparture();
    }
    else {
        status () = 0;
        itemInService_ = nullptr;
    }
}

void Server::updateStat()
{
    double durationSinceLastEvent;

    durationSinceLastEvent = Scheduler::now() - timeLastEvent;
    timeLastEvent = Scheduler::now();

    areaQueue() += durationSinceLastEvent*(queue_->length());
    areaServer() += durationSinceLastEvent*status();
    areaSystem() += durationSinceLastEvent*(queue_->length() + status());
}

void Server::report()
{
    ofstream report_;
    string reportName = "report_" + to_string(serverId_) + ".out";
    report_.open (reportName, ios::out);
    if (!report_) {
        cout << "cannot open the report file.\n";
    }
    report_<< "Report of the simulation" << endl;
    report_<<"Traffic Intensity: "<<arrivalMean()/departureMean()<<endl;
    report_<<"Average Number of Customers in the Queue : "<<(areaQueue()/(Scheduler::now()))<<endl;
    report_<<"Average Server Utilization: "<<(areaServer()/(Scheduler::now()))/stationCount_<<endl;
    report_<<"Average Number of Customers in the System: "<<(areaSystem()/(Scheduler::now()))<<endl;
    report_<<"Average Queueing Delay: "<<(totalQueueDelay()/totalCustomerServed)<<endl;
    report_<<"Average System Delay: "<<(totalSystemDelay()/totalCustomerServed)<<endl;
}

void Server::setNext(Server *server1, Server* server2, Server* server3) {
    /* There can be at best three next servers since there are three types of jobs*/
    nextServer.push_back(server1);
    nextServer.push_back(server2);
    nextServer.push_back(server3);
}
