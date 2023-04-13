#include "serviceFacility.h"

ServiceFacility::ServiceFacility(double arrivalMean, double departMean1, double departMean2) {
    s1 = new Server(1);
    s2 = new Server(2);

    s1->createTraceFile ();
    s2->createTraceFile ();

    s1->arrivalMean () = arrivalMean;
    s2->arrivalMean () = arrivalMean;

    s1->departureMean () = departMean1;
    s2->departureMean () = departMean2;

    s1->setNext(s2);
    s2->setNext(s1);

    s1->initialize ();
    s2->initialize ();

    s1->startArrival();
}

void ServiceFacility::generateReport() {
    s1->report();
    s2->report();

}
