#include "serviceFacility.h"
/*
ServiceFacility::ServiceFacility(int serviceFacilityId, int serverCount, double arrivalMean, double departureMean):Server(1, 0, nullptr) {

    this->createTraceFile();
    this->arrivalMean() = arrivalMean;
    this->departureMean() = departureMean;
    this->initialize();
    serviceFacilityId_ = serviceFacilityId;
    q = new Queue ();
    if(serverCount >= 1){
        s1 = serverInitialize(1, arrivalMean, departureMean);
        if(serverCount>=2){
            s2 = serverInitialize(2, arrivalMean, departureMean);
            s1->setNext(s2);
            if(serverCount>=3){
                s3 = serverInitialize(3, arrivalMean, departureMean);
                s2->setNext(s3);
                if(serverCount>=4){
                    s4 = serverInitialize(4, arrivalMean, departureMean);
                    s3->setNext(s4);
                    s4->setNext(nullptr);
                }
                else{
                    s3->setNext(nullptr);
                    s4 = nullptr;
                }
            }
            else{
                s2->setNext(nullptr);
                s3 = nullptr;
                s4 = nullptr;
            }
        }
        else{
            s1->setNext(nullptr);
            s2 = nullptr;
            s3 = nullptr;
            s4 = nullptr;
        }
    }
}

void ServiceFacility::serviceFacilityArrival(int jobId){
    s1->initializeArrival();
    if(!nextFacility.empty()){
        if(nextFacility[jobId-1] == deptServiceFac_){
            //process departure i.e. update output statistics
        }
        else if(nextFacility[jobId-1] != nullptr){
            nextFacility[jobId-1]->serviceFacilityArrival(jobId);
        }
    }
};

Server* ServiceFacility::serverInitialize(int id, double arrivalMean, double departureMean) {
    Server* server = new Server(serviceFacilityId_, id, q);
    server->createTraceFile ();
    server->arrivalMean() = arrivalMean;
    server->departureMean() = departureMean;
    server->initialize();
}

void ServiceFacility::generateReport() {
    s1->report();
    if(s2 != nullptr) s2->report();
    if(s3 != nullptr) s3->report();
    if(s4 != nullptr) s4->report();
}

void ServiceFacility::addNextFacility(ServiceFacility *s1, ServiceFacility *s2, ServiceFacility *s3) {
    nextFacility.push_back(s1);
    nextFacility.push_back(s2);
    nextFacility.push_back(s3);
}

void ServiceFacility::setDeptServiceFac(ServiceFacility *server) {
    deptServiceFac_ = server;
}
*/


