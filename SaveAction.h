#pragma once
#include "Actions/Action.h"
class SaveAction :
    public Action
{
private:
    string fileName;
   

public:
    SaveAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();
};

