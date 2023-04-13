#ifndef MSQS_2_SERVERS_SCENARIO_1_SERVICEFACILITY_H
#define MSQS_2_SERVERS_SCENARIO_1_SERVICEFACILITY_H
#include "server.h"

class ServiceFacility {
private:
    Server* s1;
    Server* s2;
public:
    ServiceFacility(double arrivalMean, double departMean1, double departMean2);
    void generateReport();
};


#endif //MSQS_2_SERVERS_SCENARIO_1_SERVICEFACILITY_H
