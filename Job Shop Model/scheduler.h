//
// Created by Farhan Ishmam on 12-Nov-21.
//

#ifndef SORUCE_CODE_SCHEDULER_H
#define SORUCE_CODE_SCHEDULER_H

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



#endif //SORUCE_CODE_SCHEDULER_H
