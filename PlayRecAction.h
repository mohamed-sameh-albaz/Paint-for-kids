#pragma once
#include "Actions/Action.h"
class PlayRecAction :
    public Action
{
private:
public:
    PlayRecAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();
};

