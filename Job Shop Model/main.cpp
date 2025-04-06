#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

#include "scheduler.h"
#include "serviceFacility.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <traffic_intensity>" << endl;
        return 1;
    }

    double traffic_intensity = atof(argv[1]);
    // Allow traffic intensity to equal 1.0 exactly
    if (traffic_intensity <= 0 || traffic_intensity > 1.0001) {
        cerr << "Traffic intensity must be between 0 and 1 (inclusive)" << endl;
        return 1;
    }

    // Create and initialize scheduler
    Scheduler *sch = new Scheduler();
    sch->initialize();

    // Calculate arrival and service rates based on traffic intensity
    double service_rate_ws1 = 1.0/5.0;  // 1/mean service time
    double service_rate_ws2 = 1.0/7.0;
    double arrival_rate = traffic_intensity * service_rate_ws1;

    // Initialize workstations
    Server* ws1 = new Server(1, 3);
    ws1->createTraceFile();
    ws1->arrivalMean() = 1.0/arrival_rate;
    ws1->departureMean() = 5.0;
    ws1->initialize();

    Server* ws2 = new Server(2, 2);
    ws2->createTraceFile();
    ws2->arrivalMean() = 1.0/arrival_rate;
    ws2->departureMean() = 7.0;
    ws2->initialize();

    // Set routing
    ws1->setNext(ws2, ws2, ws2);
    ws2->setNext(nullptr, nullptr, nullptr);

    // Initialize arrivals
    for (int i = 0; i < 100; i++) {  // Increased number of jobs for better statistics
        ws1->initializeArrival(1);
        ws1->initializeArrival(2);
        ws1->initializeArrival(3);
    }
    
    // Run simulation
    sch->run();
    
    // Generate reports - handle special case for traffic intensity 1.0
    string intensity_str;
    if (abs(traffic_intensity - 1.0) < 0.0001) {
        intensity_str = "1";
    } else {
        ostringstream oss;
        oss << fixed << setprecision(1) << traffic_intensity;
        intensity_str = oss.str();
    }
    
    string report_ws1 = "report_1_" + intensity_str + ".out";
    string report_ws2 = "report_2_" + intensity_str + ".out";
    
    ofstream ws1_report(report_ws1);
    ofstream ws2_report(report_ws2);
    
    if (!ws1_report || !ws2_report) {
        cerr << "Error opening report files" << endl;
        return 1;
    }
    
    // Write WS1 report
    ws1_report << "Report for Workstation 1 (Traffic Intensity: " << traffic_intensity << ")\n";
    ws1_report << "============================================\n";
    ws1_report << "Average Number of Customers in the Queue: " << ws1->areaQueue()/Scheduler::now() << "\n";
    ws1_report << "Average Server Utilization: " << ws1->areaServer()/(Scheduler::now()*3) << "\n";
    ws1_report << "Average Queueing Delay: " << ws1->totalQueueDelay()/ws1->itemArrived() << "\n";
    ws1_report << "Average System Delay: " << ws1->totalSystemDelay()/ws1->itemArrived() << "\n";
    ws1_report << "Average Number of Customers in the System: " << ws1->areaSystem()/Scheduler::now() << "\n";
    
    // Write WS2 report
    ws2_report << "Report for Workstation 2 (Traffic Intensity: " << traffic_intensity << ")\n";
    ws2_report << "============================================\n";
    ws2_report << "Average Number of Customers in the Queue: " << ws2->areaQueue()/Scheduler::now() << "\n";
    ws2_report << "Average Server Utilization: " << ws2->areaServer()/(Scheduler::now()*2) << "\n";
    ws2_report << "Average Queueing Delay: " << ws2->totalQueueDelay()/ws2->itemArrived() << "\n";
    ws2_report << "Average System Delay: " << ws2->totalSystemDelay()/ws2->itemArrived() << "\n";
    ws2_report << "Average Number of Customers in the System: " << ws2->areaSystem()/Scheduler::now() << "\n";

    // Clean up
    delete ws1;
    delete ws2;
    delete sch;
    
    return 0;
}
