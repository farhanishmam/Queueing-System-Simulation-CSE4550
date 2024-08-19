//
// Created by Farhan Ishmam on 10-Nov-21.
//

#ifndef MSQS_2_SERVERS_SCENARIO_2_QUEUE_H
#define MSQS_2_SERVERS_SCENARIO_2_QUEUE_H


typedef struct ItemType
{
    int id_;
    double itemArrivalTime;
    ItemType *next_;
} Item; // used for storing event info


class Queue
{
public:
    Queue ();
    inline int& length ()
    {
        return (length_);
    }
    void enque (Item *im);
    Item* deque ();

private:
    int length_;
    Item *head_;
    Item *tail_;
};



#endif //MSQS_2_SERVERS_SCENARIO_2_QUEUE_H
