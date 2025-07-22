//
// Created by gionimbus on 7/20/25.
//

#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"

class Subject {
public:
    virtual ~Subject() = default;

    virtual void notify() = 0;

    virtual void subscribe(Observer* o) = 0;
    virtual void unsubscribe(Observer* o) = 0;
};

#endif //SUBJECT_H
