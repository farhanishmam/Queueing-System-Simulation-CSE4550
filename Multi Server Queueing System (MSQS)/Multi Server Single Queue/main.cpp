#include <iostream>
using namespace std;

#include "scheduler.h"
#include "server.h"
#include "serviceFacility.h"

int main ()
{
    Scheduler *sch = new Scheduler ();
    sch->initialize ();

    ServiceFacility* serviceFacility = new ServiceFacility (20.0,10.0,10.0);

    sch->run ();

    serviceFacility->generateReport();

    return 0;
}
