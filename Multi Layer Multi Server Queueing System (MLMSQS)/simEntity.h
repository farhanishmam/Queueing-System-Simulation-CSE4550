#include "queue.h"

class SimEntity{

private:
    SimEntity *next_;
    SimEntity *prev_;
    int id;
public:
    virtual void arrivalHandler (Item* arrivedItem) = 0;
    virtual void departureHandler () = 0;
    virtual void updateStat() = 0;
    SimEntity(int simId);

    int getID();
    void setPrev(SimEntity *prevServer);
    void setNext(SimEntity *nextServer);
    SimEntity* getPrev();
    SimEntity* getNext();

    void sendItem(Item* sentItem);
    void receiveItem(Item* receivedItem);
};

