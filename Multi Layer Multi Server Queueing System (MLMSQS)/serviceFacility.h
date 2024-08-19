#include "server.h"

class ServiceFacility{

private:
    Server* s1;
    Server* s2;
public:
    void createFacility();
    void setMean(double arrMean, double deptMean1, double deptMean2);
    void initializeFacility();
    void report();
};

