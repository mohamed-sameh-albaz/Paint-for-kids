#pragma once
#include "Actions/Action.h"
#include "ApplicationManager.h"
#include "GUI/Output.h"
class DrwModAction :
    public Action
{
private:
public:
    DrwModAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();
};

