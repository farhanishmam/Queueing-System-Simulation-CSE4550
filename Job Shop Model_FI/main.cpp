#include <iostream>
#include <fstream>
using namespace std;

#include "scheduler.h"
#include "serviceFacility.h"


int main ()
{
    Scheduler *sch = new Scheduler ();
    sch->initialize ();

    Server* s1 = new Server(1, 3);
    s1->createTraceFile();
    s1->arrivalMean() = 10.0;
    s1->departureMean() = 10.0;
    s1->initialize();

    Server* s2 = new Server(2, 3);
    s2->createTraceFile();
    s2->arrivalMean() = 10.0;
    s2->departureMean() = 10.0;
    s2->initialize();

    s1->initializeArrival(2);

    s1->setNext(s2, s2, s2);

    s2->setNext(nullptr, nullptr, nullptr);


    /*
    s1->addNextFacility(sf2, sf3, sf4);
    s1->setDeptServiceFac(deptServer);

    s2->addNextFacility(sf5, nullptr, sf5);
    s2->setDeptServiceFac(deptServer);

    sf3->addNextFacility(sf1, deptServer, deptServer);
    sf3->setDeptServiceFac(deptServer);

    sf4->addNextFacility(nullptr, sf1, sf3);
    sf4->setDeptServiceFac(deptServer);

    sf5->addNextFacility(deptServer, nullptr, sf1);
    sf5->setDeptServiceFac(deptServer);


    ServiceFacility* sf1 = new ServiceFacility(1,3,10.0,10.0);
    ServiceFacility* sf2 = new ServiceFacility(2,2,10.0,10.0);
    ServiceFacility* sf3 = new ServiceFacility(3,4,10.0,10.0);
    ServiceFacility* sf4 = new ServiceFacility(4,3,10.0,10.0);
    ServiceFacility* sf5 = new ServiceFacility(5,1,10.0,10.0);
    ServiceFacility* deptServer = new ServiceFacility(6,1,10.0,10.0);


    */

    sch->run ();
    s1 -> report();
    s2 -> report();
    return 0;
}
