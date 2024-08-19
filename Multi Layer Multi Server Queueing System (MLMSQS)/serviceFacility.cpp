#include "serviceFacility.h"
using namespace std;

void ServiceFacility::createFacility(){
    s1 = new Server(1);
    s2 = new Server(2);
    s1->setPrev(nullptr);
    s1->setNext(s2);
    s2->setPrev(s1);
    s2->setNext(nullptr);
}

void ServiceFacility::initializeFacility(){
    s1->initialize();
    s2->initialize();
    s1->createTraceFile ();
    s2->createTraceFile ();
}

void ServiceFacility::setMean(double arrMean, double deptMean1, double deptMean2){
    s1->arrivalMean () = arrMean;
    s1->departureMean () = deptMean1;
    s2->arrivalMean() = 0.0;
    s2->departureMean() = deptMean2;
}

void ServiceFacility::report() {
    s1->report();
    s2->report();
}
