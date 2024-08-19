//
// Created by Farhan Ishmam on 21-Aug-21.
//

#include "simEntity.h"

SimEntity::SimEntity(int simId){
    id = simId;
}
int SimEntity::getID(){
    return id;
}
void SimEntity::setNext(SimEntity *nextServer){
    next_ = nextServer;
}

SimEntity* SimEntity::getNext(){
    return next_;
}
void SimEntity::setPrev(SimEntity *prevServer){
    prev_ = prevServer;
}
SimEntity* SimEntity:: getPrev(){
    return prev_;
}

void SimEntity::sendItem(Item* sentItem)
{
    this->next_->receiveItem(sentItem);
};
void SimEntity::receiveItem(Item* receivedItem)
{
    this->updateStat();
    this->arrivalHandler(receivedItem);
};