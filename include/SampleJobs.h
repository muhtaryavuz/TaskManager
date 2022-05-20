#pragma once 

#include "ControllableInterface.h"

enum class Jobs{
    JOB1,
    JOB2,
};

class Job1 : public IControllable
{
    public:
        Job1(){};
        ~Job1(){};
        bool execute() override;
};

class Job2 : public IControllable
{
    public:
        Job2(){};
        ~Job2(){};
        bool execute() override;
};