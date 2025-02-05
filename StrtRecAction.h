#pragma once
#include "Actions/Action.h"
class StrtRecAction :
    public Action
{
private:
public:
    StrtRecAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();
};

