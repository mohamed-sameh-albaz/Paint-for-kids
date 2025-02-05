#pragma once
#include "Actions/Action.h"
class voiceAction :
    public Action
{
private:

public:
    voiceAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();
};

