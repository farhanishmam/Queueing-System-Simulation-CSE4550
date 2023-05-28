//
// Created by Farhan Ishmam on 10-Nov-21.
//

#ifndef MSQS_2_SERVERS_SCENARIO_2_SCHEDULER_H
#define MSQS_2_SERVERS_SCENARIO_2_SCHEDULER_H


#include "event.h"

class Scheduler
{
public:
    Scheduler ();
    void trigger ();
    void run ();
    void initialize ();

    //protected:
    static double now ();
    static Scheduler& instance ();
    void schedule (Event *e);
    void cancel (Event *e);

private:
    void addEvent (Event *e);
    Event* removeEvent ();
    void updateClock (double t);

public:
    static double clock_;
    static Event* eventList_;
    static Scheduler* instance_;
};


#endif //MSQS_2_SERVERS_SCENARIO_2_SCHEDULER_H
