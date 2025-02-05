#pragma once
#include "Actions/Action.h"
class ExitAction :
    public Action
{
private:
public:
    ExitAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();
};

