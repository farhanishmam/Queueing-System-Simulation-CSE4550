#ifndef SORUCE_CODE_SERVICEFACILITY_H
#define SORUCE_CODE_SERVICEFACILITY_H

#include "server.h"
#include <bits/stdc++.h>

class ServiceFacility: public Server {
private:
    int serviceFacilityId_;
    Queue* q;
    Server* s1;
    Server* s2;
    Server* s3;
    Server* s4;
    ServiceFacility* deptServiceFac_;
    vector<ServiceFacility*> nextFacility; //next facility vector for job-1,2,3
    Server* serverInitialize(int id, double arrivalMean, double departureMean);
public:
    ServiceFacility(int serviceFacilityId, int serverCount, double arrivalMean, double departureMean);

    void serviceFacilityArrival(int jobId);
    void addNextFacility(ServiceFacility *s1, ServiceFacility *s2, ServiceFacility *s3);
    void setDeptServiceFac(ServiceFacility* server);
    void generateReport();
};


#endif //SORUCE_CODE_SERVICEFACILITY_H
