#include "server.h"
#include "scheduler.h"

#include <malloc.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;


Server :: Server (int id) : SimEntity(id),a_(this), d_(this)
{
    queue_ = new Queue ();
}

double Server :: exponential(double mean) {

    double r = (double)rand()/(RAND_MAX + 1.0);
    double ex = -log (r)/mean;
    return ex;
}

void Server :: initialize () {
    status_ = 0;
    itemArrived_ = 0;
    timeLastEvent = 0.0;

    areaQueue_ = 0.0;
    areaServer_ = 0.0;
    areaSystem_ = 0.0;

    totalQueueDelay_ = 0.0;
    totalSystemDelay_ = 0.0;
    totalCustomerServed = 0;

    if(getPrev() == nullptr){
        double t = exponential (arrivalMean_);
        a_.activate (t);
    }
}

void Server :: createTraceFile () {
    string serverID = to_string(getID());
    string fileName = "trace" + serverID + ".out";

    trace_.open (fileName, ios::out);
    if (!trace_) {
        cout << "cannot open the trace file.\n";
    }
    trace_<< "trace file for the simulation" << endl;
    trace_ << "format of the file" << endl;
    trace_ << "<event> <time> <item id> <server status> <queue size>" << endl << endl;
}

void
Server :: arrivalHandler (Item* arrivedItem) {
    itemArrived_++;
    if(arrivedItem == nullptr){
        arrivedItem = (Item*) malloc (sizeof(Item));
        arrivedItem->id_ = itemArrived_;
    }
    arrivedItem->itemArrivalTime = Scheduler::now();

    if(getPrev() == nullptr){
        trace_ << "a\t" << Scheduler::now () << "\t" << arrivedItem->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
    }

    if (status () == 0) {
        // write to the trace file

        status() = 1;
        trace_ << "s"<<getID()<<"\t" << Scheduler::now () << "\t" << arrivedItem->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
        itemInService_ = arrivedItem;
        queueDelay_ = Scheduler::now() - itemInService_->itemArrivalTime;
        totalQueueDelay_ += queueDelay_;

        double t = exponential (departureMean_);
        //trace_ << "\tservice time = " << t << endl;
        d_.activate (t);
    } else {
        queue_->enque(arrivedItem);
    }

    if (arrivedItem->id_ < 100) {
        double t = exponential (arrivalMean_);
        //trace_ << "\tinterarrival time = " << t << endl;
        a_.activate (t);
    }
}

void
Server :: departureHandler () {
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
        trace_ << "s"<<getID()<<"\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << queue_->length() << endl;

        double t = exponential (departureMean_);
        //trace_ << "\tservice time = " << t << endl;
        d_.activate (t);
        if(this->getNext() != NULL)
        {
            sendItem(itemInService_);
        }
    }
    else {
        status () = 0;
        itemInService_ = 0;
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
    string serverID = to_string(getID());
    string reportName = "report" + serverID + ".out";
    report_.open (reportName, ios::out);
    if (!report_) {
        cout << "cannot open the report file.\n";
    }
    report_<< "Report of the simulation" << endl;
    report_<<"Traffic Intensity: "<<arrivalMean()/departureMean()<<endl;
    report_<<"Average Number of Customers in the Queue : "<<(areaQueue()/(Scheduler::now()))<<endl;
    report_<<"Average Server Utilization: "<<(areaServer()/(Scheduler::now()))<<endl;
    report_<<"Average Number of Customers in the System: "<<(areaSystem()/(Scheduler::now()))<<endl;
    report_<<"Average Queueing Delay: "<<(totalQueueDelay()/totalCustomerServed)<<endl;
    report_<<"Average System Delay: "<<(totalSystemDelay()/totalCustomerServed)<<endl;
}